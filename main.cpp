// Test program that blinks LEDs and echos data on main serial port.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "ch.h"
#include "hal.h"

#include "version/version.h"
#include "driver/mpu6000.h"
#include "gpio/gpio.h"
#include "bus/chibios_spi.h"
#include "os/time.h"
#include <cstdio>

using namespace Fructose;

static const GpioLine kHeartbeatLed = LINE_LED_STAT;
static const GpioLine kWarningLed = LINE_LED_WARN;
static SerialDriver * const kMainSerial = &SD1;
static SPIDriver * const kMpuSpi = &SPID1;
static const GpioLine kMpuSpiCs = LINE_MPU_CS;
static constexpr SPIConfig kMpuSpiConfig = { nullptr, 0, 0,
    // APB1/prescaler = 84 MHz / 128 = 656.25 kHz.
    SPI_CR1_BR_2 | SPI_CR1_BR_1, 0 };

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

int main(void) {
  halInit();
  chSysInit();

  chThdCreateStatic(g_blink_wa, sizeof(g_blink_wa), LOWPRIO, Blink, nullptr);

  sdStart(kMainSerial, nullptr);
  printf("\r\nBoard \"%s\" (%s built on %s)\r\n", BOARD_NAME, g_build_version,
         g_build_time);

  spiStart(kMpuSpi, &kMpuSpiConfig);
  ChibiOsSpiMaster mpu_spi_master(kMpuSpi);
  ChibiOsSpiSlave mpu_spi_slave(kMpuSpiCs);
  Mpu6000 mpu6000(&mpu_spi_master, &mpu_spi_slave);
  printf("MPU-6000 detect: %u\r\n", mpu6000.Detect());
  mpu6000.ResetDevice();
  mpu6000.SetupDevice(Mpu6000::CONFIG__DLPF_CFG__5_HZ,
                      Mpu6000::GYRO_CONFIG__FS_SEL__1000_DPS,
                      Mpu6000::ACCEL_CONFIG__FS_SEL__8_G,
                      100.f, nullptr);

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
