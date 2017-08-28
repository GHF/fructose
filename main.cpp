// Test program that blinks LEDs and echos data on main serial port.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "ch.h"
#include "hal.h"

#include <cstdio>
#include "version/version.h"
#include "driver/mpu6000.h"
#include "gpio/gpio.h"
#include "bus/chibios_spi.h"

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
  while (true) {
    Gpio::Clear(kHeartbeatLed);
    osalThreadSleepMilliseconds(500);
    Gpio::Set(kHeartbeatLed);
    osalThreadSleepMilliseconds(500);
  }
}

static THD_WORKING_AREA(g_echo_wa, 256);
static THD_FUNCTION(Echo, arg) {
  SerialDriver * const serial_driver = static_cast<SerialDriver *>(arg);

  chRegSetThreadName(__func__);
  while (true) {
    const char c = sdGet(serial_driver);
    sdPut(serial_driver, c);
  }
}

int main(void) {
  halInit();
  chSysInit();

  chThdCreateStatic(g_blink_wa, sizeof(g_blink_wa), LOWPRIO, Blink, nullptr);

  sdStart(kMainSerial, nullptr);
  printf("\r\nBoard \"%s\" (%s built on %s)\r\n", BOARD_NAME, g_build_version,
         g_build_time);
  chThdCreateStatic(g_echo_wa, sizeof(g_echo_wa), NORMALPRIO, Echo,
                    kMainSerial);

  spiStart(kMpuSpi, &kMpuSpiConfig);
  ChibiOsSpiMaster mpu_spi_master(kMpuSpi);
  ChibiOsSpiSlave mpu_spi_slave(kMpuSpiCs);
  Mpu6000 mpu6000(&mpu_spi_master, &mpu_spi_slave);
  mpu_spi_master.Acquire();
  mpu6000.WriteRegister(Mpu6000::PWR_MGMT_1, 0x80U);  // Reset device.
  osalThreadSleepMilliseconds(10);
  const uint8_t who_am_i = mpu6000.ReadRegister(Mpu6000::WHO_AM_I);
  const uint8_t product_id = mpu6000.ReadRegister(Mpu6000::PRODUCT_ID);
  printf("MPU WHO_AM_I = %#x, PRODUCT_ID = %#x\r\n", who_am_i, product_id);
  mpu_spi_master.Release();

  while (true) {
    Gpio::Clear(kWarningLed);
    osalThreadSleepMilliseconds(100);
    Gpio::Set(kWarningLed);
    osalThreadSleepMilliseconds(900);
  }

  return 0;
}
