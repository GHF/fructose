// Test program that blinks LEDs and echos data on main serial port.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include <cstdio>

#include "app/log.h"
#include "app/syrup.h"
#include "bus/chibios_i2c.h"
#include "bus/chibios_spi.h"
#include "ch.h"
#include "driver/mcp4725.h"
#include "driver/mpu6000.h"
#include "gpio/gpio.h"
#include "hal.h"
#include "os/time.h"
#include "version/version.h"

using namespace Fructose;

static SerialDriver* const kDebugSerial = &SD4;
static SPIDriver* const kMpuSpi = &SPID1;
static const GpioLine kMpuSpiCs = LINE_MPU_CS;
static constexpr SPIConfig kMpuSpiConfig = {
    /*circular=*/false,
    /*end_cb=*/nullptr,
#if (SPI_SELECT_MODE == SPI_SELECT_MODE_LINE)
    /*ssline=*/0,
#endif  // SPI_SELECT_MODE
#if (SPI_SELECT_MODE == SPI_SELECT_MODE_PORT)
    /*ssport=*/0,
    /*ssmask=*/0,
#endif  // SPI_SELECT_MODE
#if (SPI_SELECT_MODE == SPI_SELECT_MODE_PAD)
    /*ssport=*/0,
    /*sspad=*/0,
#endif  // SPI_SELECT_MODE
        // APB1/prescaler = 84 MHz / 128 = 656.25 kHz.
    /*cr1=*/SPI_CR1_BR_2 | SPI_CR1_BR_1,
    /*cr2=*/0};
static ICUDriver* const kPpmIcu = &ICUD8;
static const GpioLine kLedStatus = LINE_LED_STAT;
static const GpioLine kLedWarning = LINE_LED_WARN;
static PWMDriver* const kRcOut3456Pwm = &PWMD2;
static constexpr PWMConfig kRcOut3456PwmConfig = {
    /*frequency=*/STM32_TIMCLK1 / 4,
    /*period=*/Fructose::Scale<std::ratio<STM32_TIMCLK1 / 4, 1'000'000>>(18000),
    /*callback=*/nullptr,
    /*channels=*/
    {{/*mode=*/PWM_OUTPUT_ACTIVE_HIGH, /*callback=*/nullptr},
     {/*mode=*/PWM_OUTPUT_ACTIVE_HIGH, /*callback=*/nullptr},
     {/*mode=*/PWM_OUTPUT_ACTIVE_HIGH, /*callback=*/nullptr},
     {/*mode=*/PWM_OUTPUT_ACTIVE_HIGH, /*callback=*/nullptr}},
    /*cr2=*/0,
#if STM32_PWM_USE_ADVANCED
    /*bdtr=*/0,
#endif  // STM32_PWM_USE_ADVANCED
    /*dier=*/0};
static PWMDriver* const kRcOut12Pwm = &PWMD3;
static constexpr PWMConfig kRcOut12PwmConfig = {
    /*frequency=*/STM32_TIMCLK1,
    /*period=*/Fructose::Scale<std::ratio<STM32_TIMCLK1, 24'000'000>>(18000),
    /*callback=*/nullptr,
    /*channels=*/
    {{/*mode=*/PWM_OUTPUT_DISABLED, /*callback=*/nullptr},
     {/*mode=*/PWM_OUTPUT_DISABLED, /*callback=*/nullptr},
     {/*mode=*/PWM_OUTPUT_ACTIVE_HIGH, /*callback=*/nullptr},
     {/*mode=*/PWM_OUTPUT_ACTIVE_HIGH, /*callback=*/nullptr}},
    /*cr2=*/0,
#if STM32_PWM_USE_ADVANCED
    /*bdtr=*/0,
#endif  // STM32_PWM_USE_ADVANCED
    /*dier=*/0};
static const GpioLine kDebugUartTxGpio = LINE_SERVO_OUT_6;
static const GpioLine kDebugUartRxGpio = LINE_SERVO_OUT_5;

static THD_WORKING_AREA(g_status_led_working_area, 128);
static THD_FUNCTION(StatusLed, arg) {
  chRegSetThreadName(__func__);
  Syrup* const syrup = static_cast<Syrup*>(arg);
  syrup->RunStatusLed();
}

static THD_WORKING_AREA(g_warn_led_working_area, 128);
static THD_FUNCTION(WarnLed, arg) {
  chRegSetThreadName(__func__);
  Syrup* const syrup = static_cast<Syrup*>(arg);
  syrup->RunWarnLed();
}

static THD_WORKING_AREA(g_gyro_working_area, 1024);
static THD_FUNCTION(Gyro, arg) {
  chRegSetThreadName(__func__);
  Syrup* const syrup = static_cast<Syrup*>(arg);
  syrup->RunGyro();
}

static THD_WORKING_AREA(g_reset_watch_working_area, 128);
// Resets the system if two ^C characters are received in quick succession.
// Also performs reception echo.
static THD_FUNCTION(WatchForReset, arg) {
  SerialDriver* const serial = static_cast<SerialDriver*>(arg);

  chRegSetThreadName(__func__);
  bool etx_received = false;
  while (true) {
    const msg_t msg = chnGetTimeout(serial, TIME_MS2I(500));
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
  // Uncomment to enable debug UART rx input instead of servo output 5.
  //  Gpio::SetMode(kDebugUartRxGpio,
  //                PAL_MODE_ALTERNATE(8) | PAL_STM32_PUPDR_PULLUP);
  sdStart(kDebugSerial, nullptr);
  puts("\r");
  LogInfo("Board \"%s\" (%s built on %s)", BOARD_NAME, g_build_version,
          g_build_time);
  chThdCreateStatic(g_reset_watch_working_area,
                    sizeof(g_reset_watch_working_area), HIGHPRIO, WatchForReset,
                    kDebugSerial);

  spiStart(kMpuSpi, &kMpuSpiConfig);
  ChibiOsSpiMaster mpu_spi_master(kMpuSpi);
  ChibiOsSpiDevice mpu_spi_device(kMpuSpiCs);
  Mpu6000 mpu(&mpu_spi_master, &mpu_spi_device);
  LogDebug("MPU-6000 detected: %s", mpu.Detect() ? "yes" : "no");

  PpmInput ppm_input(kPpmIcu);
  ppm_input.Start();

  pwmStart(kRcOut12Pwm, &kRcOut12PwmConfig);
  LogDebug("Started RC PWM 1,2 at %lu Hz counting to %lu",
           kRcOut12PwmConfig.frequency, kRcOut12PwmConfig.period);
  pwmStart(kRcOut3456Pwm, &kRcOut3456PwmConfig);
  LogDebug("Started RC PWM 3,4,5,6 at %lu Hz counting to %lu",
           kRcOut3456PwmConfig.frequency, kRcOut3456PwmConfig.period);

  static const SyrupConfig syrup_config = {
      /*imu=*/&mpu,
      /*ppm_input=*/&ppm_input,
      /*led_stat_gpio=*/kLedStatus,
      /*led_warn_gpio=*/kLedWarning,
      /*pwm_1_2_driver=*/kRcOut12Pwm,
      /*pwm_3_4_5_6_driver=*/kRcOut3456Pwm,
  };
  Syrup syrup(&syrup_config);
  chThdCreateStatic(g_status_led_working_area,
                    sizeof(g_status_led_working_area), LOWPRIO, StatusLed,
                    &syrup);
  syrup.set_warn_thread(chThdCreateStatic(g_warn_led_working_area,
                                          sizeof(g_warn_led_working_area),
                                          LOWPRIO, WarnLed, &syrup));
  syrup.Start();
  chThdCreateStatic(g_gyro_working_area, sizeof(g_gyro_working_area),
                    HIGHPRIO - 1, Gyro, &syrup);
  syrup.RunMain();

  return 0;
}
