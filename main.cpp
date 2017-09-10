// Test program that blinks LEDs and echos data on main serial port.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "ch.h"
#include "hal.h"

#include "app/syrup.h"
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

static SerialDriver * const kDebugSerial = &SD4;
static SPIDriver * const kMpuSpi = &SPID1;
static const GpioLine kMpuSpiCs = LINE_MPU_CS;
static constexpr SPIConfig kMpuSpiConfig = {
    // APB1/prescaler = 84 MHz / 128 = 656.25 kHz.
    nullptr, 0, 0, SPI_CR1_BR_2 | SPI_CR1_BR_1, 0
};
static I2CDriver * const kMcpI2c = &I2CD2;
static constexpr I2CConfig kMcpI2cConfig = {
    OPMODE_I2C, 400000, FAST_DUTY_CYCLE_2
};
static ICUDriver * const kPpmIcu = &ICUD8;
static const GpioLine kLedStatus = LINE_LED_STAT;
static const GpioLine kLedWarning = LINE_LED_WARN;
static PWMDriver * const kRcOutPwm = &PWMD3;
static constexpr pwmchannel_t kClampOutChannel = 3;
static constexpr pwmchannel_t kLiftOutChannel = 2;
static constexpr PWMConfig kRcOutPwmConfig = {
    1000000,
    15000,
    nullptr,
    {{PWM_OUTPUT_DISABLED, nullptr},
     {PWM_OUTPUT_DISABLED, nullptr},
     {PWM_OUTPUT_ACTIVE_HIGH, nullptr},
     {PWM_OUTPUT_ACTIVE_HIGH, nullptr}},
    0,
#if STM32_PWM_USE_ADVANCED
    0,
#endif  // STM32_PWM_USE_ADVANCED
    0
};
static const GpioLine kMotorEnGpio = LINE_SERVO_OUT_3;
static const GpioLine kDirLeftGpio = LINE_SERVO_OUT_4;
static const GpioLine kDirRightGpio = LINE_INPUT_PIN_3;
static const GpioLine kVddSourceGpio = LINE_INPUT_PIN_4;
static const GpioLine kDebugUartTxGpio = LINE_SERVO_OUT_6;
static const GpioLine kDebugUartRxGpio = LINE_SERVO_OUT_5;

static THD_WORKING_AREA(g_blink_wa, 128);
static THD_FUNCTION(Blink, arg) {
  chRegSetThreadName(__func__);
  Syrup * const syrup = static_cast<Syrup *>(arg);
  syrup->RunLed();
}

static THD_WORKING_AREA(g_gyro_wa, 1024);
static THD_FUNCTION(Gyro, arg) {
  chRegSetThreadName(__func__);
  Syrup * const syrup = static_cast<Syrup *>(arg);
  syrup->RunGyro();
}

static THD_WORKING_AREA(g_reset_watch_wa, 128);
// Resets the system if two ^C characters are received in quick succession.
// Also performs reception echo.
static THD_FUNCTION(WatchForReset, arg) {
  SerialDriver * const serial = static_cast<SerialDriver *>(arg);

  chRegSetThreadName(__func__);
  bool etx_received = false;
  while (true) {
    const msg_t msg = chnGetTimeout(serial, MS2ST(500));
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
    sdPut(serial, c);
  }
  NVIC_SystemReset();
}

int main(void) {
  halInit();
  chSysInit();

  Gpio::SetMode(kDebugUartTxGpio, PAL_MODE_ALTERNATE(8));
  Gpio::SetMode(kDebugUartRxGpio, PAL_MODE_ALTERNATE(8) |
                                  PAL_STM32_PUPDR_PULLUP);
  sdStart(kDebugSerial, nullptr);
  puts("\r");
  LogInfo("Board \"%s\" (%s built on %s)", BOARD_NAME,
          g_build_version, g_build_time);
  chThdCreateStatic(g_reset_watch_wa, sizeof(g_reset_watch_wa), HIGHPRIO,
                    WatchForReset, kDebugSerial);

  spiStart(kMpuSpi, &kMpuSpiConfig);
  ChibiOsSpiMaster mpu_spi_master(kMpuSpi);
  ChibiOsSpiDevice mpu_spi_device(kMpuSpiCs);
  Mpu6000 mpu(&mpu_spi_master, &mpu_spi_device);
  LogDebug("MPU-6000 detected: %s", mpu.Detect() ? "yes" : "no");

  i2cStart(kMcpI2c, &kMcpI2cConfig);
  ChibiOsI2cMaster mcp_i2c_master(kMcpI2c);
  Mcp4725 dac_0(&mcp_i2c_master, Mcp4725::kAddressA0Clear);
  Mcp4725 dac_1(&mcp_i2c_master, Mcp4725::kAddressA0Set);

  PpmInput ppm_input(kPpmIcu);
  ppm_input.Start();

  pwmStart(kRcOutPwm, &kRcOutPwmConfig);

  // Override board settings because they're set for timer PWM output.
  const GpioLine out_gpio_overrides[] = {
      kMotorEnGpio, kDirLeftGpio, kDirRightGpio, kVddSourceGpio
  };
  for (const GpioLine line : out_gpio_overrides) {
    Gpio::Clear(line);
    Gpio::SetMode(line, PAL_STM32_MODE_OUTPUT | PAL_STM32_OTYPE_PUSHPULL |
                        PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);
  }
  Gpio::Set(kVddSourceGpio);

  static const SyrupConfig syrup_config = {
      &dac_0,
      &dac_1,
      kMotorEnGpio,
      kDirLeftGpio,
      kDirRightGpio,
      &mpu,
      &ppm_input,
      kLedStatus,
      kLedWarning,
      kRcOutPwm,
      kClampOutChannel,
      kLiftOutChannel,
      Duration::Microseconds(1500),
  };
  Syrup syrup(&syrup_config);
  chThdCreateStatic(g_blink_wa, sizeof(g_blink_wa), LOWPRIO, Blink, &syrup);
  syrup.Start();
  chThdCreateStatic(g_gyro_wa, sizeof(g_gyro_wa), HIGHPRIO - 1, Gyro, &syrup);
  syrup.RunMain();

  return 0;
}
