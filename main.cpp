// Test program that blinks LEDs and echos data on main serial port.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "ch.h"
#include "hal.h"

#include <cstdio>
#include <version/version.h>

static const ioline_t kHeartbeatLed = LINE_LED_STAT;
static const ioline_t kWarningLed = LINE_LED_WARN;
static SerialDriver * const kMainSerial = &SD1;

static THD_WORKING_AREA(g_blink_wa, 128);
static THD_FUNCTION(Blink, arg) {
  (void) arg;

  chRegSetThreadName(__func__);
  while (true) {
    palClearLine(kHeartbeatLed);
    osalThreadSleepMilliseconds(500);
    palSetLine(kHeartbeatLed);
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
  printf("\r\nBoard \"%s\" (%s built on %s)\n", BOARD_NAME, g_build_version,
         g_build_time);
  chThdCreateStatic(g_echo_wa, sizeof(g_echo_wa), NORMALPRIO, Echo,
                    kMainSerial);

  while (true) {
    palClearLine(kWarningLed);
    osalThreadSleepMilliseconds(100);
    palSetLine(kWarningLed);
    osalThreadSleepMilliseconds(900);
  }

  return 0;
}
