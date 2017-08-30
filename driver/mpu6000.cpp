// Definitions for InvenSense MPU-6000 communications logic.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "driver/mpu6000.h"
#include "bus/spi.h"
#include "os/time.h"
#include "base/integer.h"

#include <algorithm>
#include <cmath>

namespace Fructose {

Mpu6000::Mpu6000(SpiMaster *spi_master, SpiSlave *spi_slave)
    : spi_master_(spi_master),
      spi_slave_(spi_slave),
      gyro_scale_(0.f),
      accel_scale_(0.f) {
}

bool Mpu6000::Detect() {
  BusGuard bus_guard(spi_master_);
  WriteRegister(PWR_MGMT_1, PWR_MGMT_1__DEVICE_RESET);
  for (int attempt = 5; attempt >= 0; attempt--) {
    Duration::Microseconds(500).Sleep();
    const uint8_t who_am_i = ReadRegister(WHO_AM_I);
    if (who_am_i == kWhoAmIMagic) {
      break;
    }
    if (attempt == 0) {
      return false;
    }
  }
  const uint8_t product_id = ReadRegister(PRODUCT_ID);
  switch (product_id) {
    case MPU6000ES_REV_C4:
    case MPU6000ES_REV_C5:
    case MPU6000_REV_C4:
    case MPU6000_REV_C5:
    case MPU6000ES_REV_D6:
    case MPU6000ES_REV_D7:
    case MPU6000ES_REV_D8:
    case MPU6000_REV_D6:
    case MPU6000_REV_D7:
    case MPU6000_REV_D8:
    case MPU6000_REV_D9:
    case MPU6000_REV_D10:
      return true;
  }
  return false;
}

void Mpu6000::ResetDevice() {
  BusGuard bus_guard(spi_master_);
  WriteRegister(PWR_MGMT_1, PWR_MGMT_1__DEVICE_RESET);
  Duration::Milliseconds(100).Sleep();
  WriteRegister(USER_CTRL, USER_CTRL__SIG_COND_RESET);
  Duration::Milliseconds(100).Sleep();
}

void Mpu6000::SetupDevice(GyroLpf lpf_config, GyroFullScaleRange gyro_fsr,
                          AccelFullScaleRange accel_fsr, float desired_rate,
                          float *actual_rate) {
  static const int kWriteDelayUs = 100;

  BusGuard bus_guard(spi_master_);
  // Change clock source to Z-axis gyro oscillator for stability.
  WriteRegister(PWR_MGMT_1, PWR_MGMT_1__CLKSEL__Z_GYRO);
  Duration::Microseconds(kWriteDelayUs).Sleep();

  // Disable primary (host to MPU) I2C interface.
  WriteRegister(USER_CTRL, USER_CTRL__I2C_IF_DIS);
  Duration::Microseconds(kWriteDelayUs).Sleep();

  // Set rate at which sensor data registers are updated, triggering data
  // ready interrupts.
  const uint8_t sample_rate_divider =
      ComputeDivider(lpf_config, desired_rate, actual_rate);
  WriteRegister(SMPLRT_DIV, sample_rate_divider);
  Duration::Microseconds(kWriteDelayUs).Sleep();

  // Set digital low-pass filter cutoff.
  WriteRegister(CONFIG, lpf_config);
  Duration::Microseconds(kWriteDelayUs).Sleep();

  // Set gyro full scale range.
  WriteRegister(GYRO_CONFIG, gyro_fsr);
  gyro_scale_ = ComputeGyroScale(gyro_fsr);
  Duration::Microseconds(kWriteDelayUs).Sleep();

  // Set accel full scale range.
  WriteRegister(ACCEL_CONFIG, accel_fsr);
  accel_scale_ = ComputeAccelScale(accel_fsr);
  Duration::Microseconds(kWriteDelayUs).Sleep();

  // Any register read clears the interrupt status register.
  WriteRegister(INT_PIN_CFG, INT_PIN_CFG__INT_RD_CLEAR);
  Duration::Microseconds(kWriteDelayUs).Sleep();

  // Enable pin interrupts on data ready.
  WriteRegister(INT_ENABLE, INT_ENABLE__DATA_RDY_EN);
  Duration::Microseconds(kWriteDelayUs).Sleep();
}

void Mpu6000::ReadRaw(int16_t (*gyro_raw)[3], int16_t (*accel_raw)[3],
                      int16_t *temp_raw) {
  if (gyro_raw == nullptr && accel_raw == nullptr && temp_raw == nullptr) {
    return;
  }
  BusGuard bus_guard(spi_master_);
  if (accel_raw != nullptr) {
    uint8_t data[6];
    ReadRegister(ACCEL_XOUT_H, ArraySize(data), data);
    (*accel_raw)[0] = data[0] << 8 | data[1];
    (*accel_raw)[1] = data[2] << 8 | data[3];
    (*accel_raw)[2] = data[4] << 8 | data[5];
  }
  if (temp_raw != nullptr) {
    uint8_t data[2];
    ReadRegister(TEMP_OUT_H, ArraySize(data), data);
    *temp_raw = data[0] << 8 | data[1];
  }
  if (gyro_raw != nullptr) {
    uint8_t data[6];
    ReadRegister(GYRO_XOUT_H, ArraySize(data), data);
    (*gyro_raw)[0] = data[0] << 8 | data[1];
    (*gyro_raw)[1] = data[2] << 8 | data[3];
    (*gyro_raw)[2] = data[4] << 8 | data[5];
  }
}

void Mpu6000::Read(float (*gyro)[3], float (*accel)[3], float *temp) {
  int16_t gyro_raw[3];
  int16_t accel_raw[3];
  int16_t temp_raw;
  ReadRaw(gyro != nullptr ? &gyro_raw : nullptr,
          accel != nullptr ? &accel_raw : nullptr,
          temp != nullptr ? &temp_raw : nullptr);
  if (gyro != nullptr) {
    for (size_t i = 0; i < ArraySize(*gyro); i++) {
      (*gyro)[i] = gyro_raw[i] * gyro_scale_;
    }
  }
  if (accel != nullptr) {
    for (size_t i = 0; i < ArraySize(*accel); i++) {
      (*accel)[i] = accel_raw[i] * accel_scale_;
    }
  }
  if (temp != nullptr) {
    *temp = ConvertTempFromRaw(temp_raw);
  }
}

void Mpu6000::WriteRegister(uint8_t address, uint8_t data) {
  const uint8_t address_masked = address & ~kRegisterReadMask;
  const uint8_t tx_buffer[] = { address_masked, data };
  spi_slave_->Select();
  spi_master_->Transfer(sizeof(tx_buffer), tx_buffer, nullptr);
  spi_slave_->Deselect();
}

void Mpu6000::ReadRegister(uint8_t address, size_t n, uint8_t *rx_buffer) {
  const uint8_t address_masked = address | kRegisterReadMask;
  spi_slave_->Select();
  spi_master_->Transfer(1, &address_masked, nullptr);
  spi_master_->Transfer(n, nullptr, rx_buffer);
  spi_slave_->Deselect();
}

// Convenience function to read a single register. Uses only one SPI full-
// duplex transfer.
uint8_t Mpu6000::ReadRegister(uint8_t address) {
  const uint8_t address_masked = address | kRegisterReadMask;
  const uint8_t tx_buffer[2] = { address_masked };  // Second byte is dummy.
  uint8_t rx_buffer[2];  // First byte is dummy.
  spi_slave_->Select();
  spi_master_->Transfer(2, tx_buffer, rx_buffer);
  spi_slave_->Deselect();
  return rx_buffer[1];
}

uint8_t Mpu6000::ComputeDivider(GyroLpf gyro_lpf, float desired_rate,
                                float *actual_rate) {
  const float base_rate = gyro_lpf == CONFIG__DLPF_CFG__256_HZ ||
                          gyro_lpf == CONFIG__DLPF_CFG__NONE ?
                              8000.f : 1000.f;
  long denominator;
  if (desired_rate == 0.f) {
    denominator = 256;
  } else {
    const float ratio = Clamp(base_rate / desired_rate, 1.f, 256.f);
    denominator = lroundf(ratio);
  }
  if (actual_rate != nullptr) {
    *actual_rate = base_rate / denominator;
  }
  return denominator - 1;
}

}  // namespace Fructose
