// Controls and reads the InvenSense MPU-6000 accelerometer and gyro over SPI.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstddef>
#include <cstdint>

namespace Fructose {

// Forward declarations.
class SpiMaster;
class SpiSlave;

class Mpu6000 {
 public:
  enum Register : uint8_t {
    XG_OFFS_TC              = 0x00,
    YG_OFFS_TC              = 0x01,
    ZG_OFFS_TC              = 0x02,
    X_FINE_GAIN             = 0x03,
    Y_FINE_GAIN             = 0x04,
    Z_FINE_GAIN             = 0x05,
    XA_OFFS_H               = 0x06,
    XA_OFFS_L_TC            = 0x07,
    YA_OFFS_H               = 0x08,
    YA_OFFS_L_TC            = 0x09,
    ZA_OFFS_H               = 0x0A,
    ZA_OFFS_L_TC            = 0x0B,
    PRODUCT_ID              = 0x0C,
    SELF_TEST_X             = 0x0D,
    SELF_TEST_Y             = 0x0E,
    SELF_TEST_Z             = 0x0F,
    SELF_TEST_A             = 0x10,
    XG_OFFS_USRH            = 0x13,
    XG_OFFS_USRL            = 0x14,
    YG_OFFS_USRH            = 0x15,
    YG_OFFS_USRL            = 0x16,
    ZG_OFFS_USRH            = 0x17,
    ZG_OFFS_USRL            = 0x18,
    SMPLRT_DIV              = 0x19,
    CONFIG                  = 0x1A,
    GYRO_CONFIG             = 0x1B,
    ACCEL_CONFIG            = 0x1C,
    FF_THR                  = 0x1D,
    FF_DUR                  = 0x1E,
    MOT_THR                 = 0x1F,
    MOT_DUR                 = 0x20,
    ZRMOT_THR               = 0x21,
    ZRMOT_DUR               = 0x22,
    FIFO_EN                 = 0x23,
    I2C_MST_CTRL            = 0x24,
    I2C_SLV0_ADDR           = 0x25,
    I2C_SLV0_REG            = 0x26,
    I2C_SLV0_CTRL           = 0x27,
    I2C_SLV1_ADDR           = 0x28,
    I2C_SLV1_REG            = 0x29,
    I2C_SLV1_CTRL           = 0x2A,
    I2C_SLV2_ADDR           = 0x2B,
    I2C_SLV2_REG            = 0x2C,
    I2C_SLV2_CTRL           = 0x2D,
    I2C_SLV3_ADDR           = 0x2E,
    I2C_SLV3_REG            = 0x2F,
    I2C_SLV3_CTRL           = 0x30,
    I2C_SLV4_ADDR           = 0x31,
    I2C_SLV4_REG            = 0x32,
    I2C_SLV4_DO             = 0x33,
    I2C_SLV4_CTRL           = 0x34,
    I2C_SLV4_DI             = 0x35,
    I2C_MST_STATUS          = 0x36,
    INT_PIN_CFG             = 0x37,
    INT_ENABLE              = 0x38,
    DMP_INT_STATUS          = 0x39,
    INT_STATUS              = 0x3A,
    ACCEL_XOUT_H            = 0x3B,
    ACCEL_XOUT_L            = 0x3C,
    ACCEL_YOUT_H            = 0x3D,
    ACCEL_YOUT_L            = 0x3E,
    ACCEL_ZOUT_H            = 0x3F,
    ACCEL_ZOUT_L            = 0x40,
    TEMP_OUT_H              = 0x41,
    TEMP_OUT_L              = 0x42,
    GYRO_XOUT_H             = 0x43,
    GYRO_XOUT_L             = 0x44,
    GYRO_YOUT_H             = 0x45,
    GYRO_YOUT_L             = 0x46,
    GYRO_ZOUT_H             = 0x47,
    GYRO_ZOUT_L             = 0x48,
    EXT_SENS_DATA_00        = 0x49,
    MOT_DETECT_STATUS       = 0x61,
    I2C_SLV0_DO             = 0x63,
    I2C_SLV1_DO             = 0x64,
    I2C_SLV2_DO             = 0x65,
    I2C_SLV3_DO             = 0x66,
    I2C_MST_DELAY_CTRL      = 0x67,
    SIGNAL_PATH_RESET       = 0x68,
    MOT_DETECT_CTRL         = 0x69,
    USER_CTRL               = 0x6A,
    PWR_MGMT_1              = 0x6B,
    PWR_MGMT_2              = 0x6C,
    BANK_SEL                = 0x6D,
    MEM_START_ADDR          = 0x6E,
    MEM_R_W                 = 0x6F,
    DMP_CFG_1               = 0x70,
    DMP_CFG_2               = 0x71,
    FIFO_COUNTH             = 0x72,
    FIFO_COUNTL             = 0x73,
    FIFO_R_W                = 0x74,
    WHO_AM_I                = 0x75,
  };
  enum RegisterField : uint8_t {
    CONFIG__DLPF_CFG                    = 0x07,
    GYRO_CONFIG__FS_SEL                 = 0x18,
    ACCEL_CONFIG__FS_SEL                = 0x18,
    INT_PIN_CFG__INT_RD_CLEAR           = 0x10,
    INT_ENABLE__DATA_RDY_EN             = 0x01,
    USER_CTRL__SIG_COND_RESET           = 0x01,
    USER_CTRL__I2C_IF_DIS               = 0x10,
    PWR_MGMT_1__CLKSEL                  = 0x07,
    PWR_MGMT_1__CLKSEL__Z_GYRO          = 0x03,
    PWR_MGMT_1__DEVICE_RESET            = 0x80,
  };
  enum ProductId : uint8_t {
    MPU6000ES_REV_C4 = 0x14,
    MPU6000ES_REV_C5 = 0x15,
    MPU6000ES_REV_D6 = 0x16,
    MPU6000ES_REV_D7 = 0x17,
    MPU6000ES_REV_D8 = 0x18,
    MPU6000_REV_C4   = 0x54,
    MPU6000_REV_C5   = 0x55,
    MPU6000_REV_D6   = 0x56,
    MPU6000_REV_D7   = 0x57,
    MPU6000_REV_D8   = 0x58,
    MPU6000_REV_D9   = 0x59,
    MPU6000_REV_D10  = 0x5A,
  };
  enum GyroLpf : uint8_t {
    CONFIG__DLPF_CFG__256_HZ = 0x00,
    CONFIG__DLPF_CFG__188_HZ = 0x01,
    CONFIG__DLPF_CFG__98_HZ  = 0x02,
    CONFIG__DLPF_CFG__42_HZ  = 0x03,
    CONFIG__DLPF_CFG__21_HZ  = 0x04,
    CONFIG__DLPF_CFG__10_HZ  = 0x05,
    CONFIG__DLPF_CFG__5_HZ   = 0x06,
    CONFIG__DLPF_CFG__NONE   = 0x07,
  };
  enum GyroFullScaleRange : uint8_t {
    GYRO_CONFIG__FS_SEL__250_DPS  = 0x00,
    GYRO_CONFIG__FS_SEL__500_DPS  = 0x08,
    GYRO_CONFIG__FS_SEL__1000_DPS = 0x10,
    GYRO_CONFIG__FS_SEL__2000_DPS = 0x18,
  };
  enum AccelFullScaleRange : uint8_t {
    ACCEL_CONFIG__FS_SEL__2_G  = 0x00,
    ACCEL_CONFIG__FS_SEL__4_G  = 0x08,
    ACCEL_CONFIG__FS_SEL__8_G  = 0x10,
    ACCEL_CONFIG__FS_SEL__16_G = 0x18,
  };
  // A set MSb in the first byte to device indicates a register read.
  static constexpr uint8_t kRegisterReadMask = 0x80U;
  static constexpr uint8_t kWhoAmIMagic = 0x68U;

  Mpu6000(SpiMaster *spi_master, SpiSlave *spi_slave);
  bool Detect();
  void ResetDevice();
  void SetupDevice(GyroLpf lpf_config, GyroFullScaleRange gyro_fsr,
                   AccelFullScaleRange accel_fsr, float desired_rate,
                   float *actual_rate);

  // Any of these can be null to be not read.
  void ReadRaw(int16_t (*gyro)[3], int16_t (*accel)[3], int16_t *temp);
  void Read(float (*gyro)[3], float (*accel)[3], float *temp);

  void WriteRegister(uint8_t address, uint8_t data);
  void ReadRegister(uint8_t address, size_t n, uint8_t *rx_buffer);
  uint8_t ReadRegister(uint8_t address);

  // Computes the 8-bit sample rate divisor for a filter configuration and
  // desired sample rate.
  static uint8_t ComputeDivider(GyroLpf gyro_lpf, float desired_rate,
                                float *actual_rate);

  // Get a scaling factor that converts raw readings to rad/s.
  static constexpr float ComputeGyroScale(GyroFullScaleRange gyro_fsr) {
    const double kFullScaleLsb = 32768.0;
    float dps_from_raw = 0.f;
    switch (gyro_fsr) {
      case GYRO_CONFIG__FS_SEL__250_DPS:
        dps_from_raw = 250.0 / kFullScaleLsb;
        break;
      case GYRO_CONFIG__FS_SEL__500_DPS:
        dps_from_raw = 500.0 / kFullScaleLsb;
        break;
      case GYRO_CONFIG__FS_SEL__1000_DPS:
        dps_from_raw = 1000.0 / kFullScaleLsb;
        break;
      case GYRO_CONFIG__FS_SEL__2000_DPS:
        dps_from_raw = 2000.0 / kFullScaleLsb;
        break;
    }
    const float rad_from_deg = 3.14159265358979323846 / 180.0;
    return rad_from_deg * dps_from_raw;
  }

  // Get a scaling factor that converts raw readings to rad/s.
  static constexpr float ComputeAccelScale(AccelFullScaleRange accel_fsr) {
    const double kFullScaleLsb = 32768.0;
    float g_from_raw = 0.f;
    switch (accel_fsr) {
      case ACCEL_CONFIG__FS_SEL__2_G:
        g_from_raw = 2.0 / kFullScaleLsb;
        break;
      case ACCEL_CONFIG__FS_SEL__4_G:
        g_from_raw = 4.0 / kFullScaleLsb;
        break;
      case ACCEL_CONFIG__FS_SEL__8_G:
        g_from_raw = 8.0 / kFullScaleLsb;
        break;
      case ACCEL_CONFIG__FS_SEL__16_G:
        g_from_raw = 16.0 / kFullScaleLsb;
        break;
    }
    const float m_s2_from_g = 9.80665;
    return m_s2_from_g * g_from_raw;
  }

  // Returns in degress Celsius.
  static constexpr float ConvertTempFromRaw(int16_t temp_raw) {
    return temp_raw * static_cast<float>(1.0 / 340.0) + 36.53f;
  }

 private:
  SpiMaster * const spi_master_;
  SpiSlave * const spi_slave_;
  float gyro_scale_;  // rad/s per raw LSb
  float accel_scale_;  // m/s^2 per raw LSb
};

}  // namespace Fructose
