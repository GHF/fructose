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
  enum MpuRegister : uint8_t {
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
  // A set MSb in the first byte to device indicates a register read.
  static constexpr uint8_t kRegisterReadMask = 0x80U;

  Mpu6000(SpiMaster *spi_master, SpiSlave *spi_slave);
  void WriteRegister(uint8_t address, uint8_t data);
  void ReadRegister(uint8_t address, size_t n, uint8_t *rx_buffer);
  uint8_t ReadRegister(uint8_t address);

 private:
  SpiMaster * const spi_master_;
  SpiSlave * const spi_slave_;
};

}  // namespace Fructose
