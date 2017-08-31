// Test program that blinks LEDs and echos data on main serial port.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "ch.h"
#include "hal.h"

#include "app/log.h"
#include "version/version.h"
#include "driver/mcp4725.h"
#include "driver/mpu6000.h"
#include "gpio/gpio.h"
#include "bus/chibios_i2c.h"
#include "bus/chibios_spi.h"
#include "os/time.h"
#include <cstdio>

using namespace Fructose;

static const GpioLine kHeartbeatLed = LINE_LED_STAT;
static const GpioLine kWarningLed = LINE_LED_WARN;
static SerialDriver * const kMainSerial = &SD1;
static SPIDriver * const kMpuSpi = &SPID1;
static const GpioLine kMpuSpiCs = LINE_MPU_CS;
static constexpr SPIConfig kMpuSpiConfig = {nullptr, 0, 0,
    // APB1/prescaler = 84 MHz / 128 = 656.25 kHz.
    SPI_CR1_BR_2 | SPI_CR1_BR_1, 0};
static I2CDriver * const kMcpI2c = &I2CD2;
static constexpr I2CConfig kMcpI2cConfig = {
    OPMODE_I2C, 400000, FAST_DUTY_CYCLE_2
};

static THD_WORKING_AREA(g_blink_wa, 128);
static THD_FUNCTION(Blink, arg) {
  (void) arg;

  chRegSetThreadName(__func__);
  TimePoint time_point = TimePoint::Now();
  while (true) {
    Gpio::Toggle(kHeartbeatLed);
    time_point = time_point.After(Duration::Milliseconds(500));
    time_point.SleepUntil();
  }
}

static THD_WORKING_AREA(g_reset_watch_wa, 128);
// Resets the system if two ^C characters are received in quick succession.
// Also performs reception echo.
static THD_FUNCTION(WatchForReset, arg) {
  (void) arg;

  chRegSetThreadName(__func__);
  bool etx_received = false;
  while (true) {
    const msg_t msg = chnGetTimeout(kMainSerial, MS2ST(500));
    if (msg == Q_TIMEOUT || msg == Q_RESET) {
      etx_received = false;
      continue;
    }
    const uint8_t c = msg;
    if (c == '\x03') {
      if (etx_received) {
        break;
      } else {
        etx_received = true;
      }
    } else {
      etx_received = false;
    }
    // Echo character back.
    sdPut(kMainSerial, c);
  }
  NVIC_SystemReset();
}

int main(void) {
  halInit();
  chSysInit();

  chThdCreateStatic(g_blink_wa, sizeof(g_blink_wa), LOWPRIO, Blink, nullptr);

  sdStart(kMainSerial, nullptr);
  chThdCreateStatic(g_reset_watch_wa, sizeof(g_reset_watch_wa), HIGHPRIO,
                    WatchForReset, nullptr);
  puts("");
  LogInfo("Board \"%s\" (%s built on %s)", BOARD_NAME,
          g_build_version, g_build_time);

  spiStart(kMpuSpi, &kMpuSpiConfig);
  ChibiOsSpiMaster mpu_spi_master(kMpuSpi);
  ChibiOsSpiDevice mpu_spi_device(kMpuSpiCs);
  Mpu6000 mpu6000(&mpu_spi_master, &mpu_spi_device);
  LogDebug("MPU-6000 detect: %u", mpu6000.Detect());
  mpu6000.ResetDevice();
  mpu6000.SetupDevice(Mpu6000::CONFIG__DLPF_CFG__5_HZ,
                      Mpu6000::GYRO_CONFIG__FS_SEL__1000_DPS,
                      Mpu6000::ACCEL_CONFIG__FS_SEL__8_G,
                      100.f, nullptr);

  i2cStart(kMcpI2c, &kMcpI2cConfig);
  ChibiOsI2cMaster mcp_i2c_master(kMcpI2c);
  Mcp4725 mcp4725(&mcp_i2c_master, Mcp4725::kAddressA0Clear);
  mcp4725.Write(.5f, Duration::Milliseconds(250));

  while (true) {
    Gpio::Clear(kWarningLed);
    Duration::Milliseconds(100).Sleep();
    Gpio::Set(kWarningLed);
    Duration::Milliseconds(900).Sleep();
    float gyro[3];
    float temp;
    mpu6000.Read(&gyro, nullptr, &temp);
    printf("%#g, %#g, %#g (%g C)\r\n", gyro[0], gyro[1], gyro[2], temp);
  }

  return 0;
}
