// Input driver on ChibiOS for combined pulse position modulation (CPPM) radio
// control commands.
//
// (C) Copyright 2014-2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "app/ppm_input.h"
#include "app/log.h"
#include "base/integer.h"
#include <algorithm>

#include "hal.h"
#include "ch.h"

PpmInput::PpmInput(ICUDriver *icu_driver)
    : icu_driver_(icu_driver),
      num_overflows_(0),
      commands_(),
      channel_(0),
      last_commands_(),
      last_channels_(0),
      ppm_listener_(nullptr) {
}

void PpmInput::Start() {
  static const ICUConfig kServoIcuConfig = { ICU_INPUT_ACTIVE_HIGH,
                                             1000000,
                                             IcuWidthCallback,
                                             IcuPeriodCallback,
                                             IcuOverflowCallback,
                                             ICU_CHANNEL_1,
                                             0 };
  icu_driver_->self = this;
  LogInfo("Configuring PPM input capture at %lu kHz...\r\n",
          kServoIcuConfig.frequency / 1000U);
  icuStart(icu_driver_, &kServoIcuConfig);
  // Full sample frequency, 8 sample filter
  icu_driver_->tim->CCMR1 |= STM32_TIM_CCMR1_IC1F(3);
  icuStartCapture(icu_driver_);
}

void PpmInput::StartCapture() {
  icuEnableNotifications(icu_driver_);
  LogInfo("Started PPM input capture.");
}

int PpmInput::ReadCommands(int commands_capacity, uint16_t *commands) {
  if (last_channels_ > 0) {
    const syssts_t sys_status = chSysGetStatusAndLockX();
    const int num_channels = std::min(last_channels_, commands_capacity);
    std::copy(last_commands_, last_commands_ + num_channels, commands);
    chSysRestoreStatusX(sys_status);
    return last_channels_;
  }
  return 0;
}

void PpmInput::HandlePulse(int width, int period) {
  if (num_overflows_ == 0) {
    if (width >= kSyncMin) {
      if (channel_ > 0) {
        // Store captured channels for listener access.
        osalSysLockFromISR();
        std::copy(commands_, commands_ + channel_, last_commands_);
        last_channels_ = channel_;
        // Reset capture state to zero channels captured.
        channel_ = 0;
        osalSysUnlockFromISR();
        // Alert the listener if registered.
        if (ppm_listener_ != nullptr) {
          ppm_listener_->HandleCommandsFromIsr(this);
        }
      }
    } else if ((period >= kInputMin) && (period <= kInputMax)) {
      // Valid command captured. Store to the next channel.
      if (channel_ < kMaxChannels) {
        // TODO: Send alert for new pulse.
        osalSysLockFromISR();
        commands_[channel_] = period;
        channel_++;
        osalSysUnlockFromISR();
      }
    } else {
      // Invalid pulse; reset channels captured.
      channel_ = 0;
    }
  } else {
    // Overflowed since last positive edge; reset channels captured.
    channel_ = 0;
  }
  // Reset overflow counter for new positive edge.
  num_overflows_ = 0;
}

void PpmInput::IcuWidthCallback(ICUDriver *icu_driver) {
  PpmInput * const ppm_input = static_cast<PpmInput *>(icu_driver->self);
  // Overflowed while waiting for negative edge, but still got one.
  if (ppm_input->num_overflows_ > 0) {
    // Reset PPM parsing to initial state without alerting listener.
    ppm_input->channel_ = 0;
  }
}

void PpmInput::IcuPeriodCallback(ICUDriver *icu_driver) {
  PpmInput * const ppm_input = static_cast<PpmInput *>(icu_driver->self);
  const uint16_t pulse_width = icuGetWidthX(icu_driver);
  const uint16_t pulse_period = icuGetPeriodX(icu_driver);
  ppm_input->HandlePulse(pulse_width, pulse_period);
}

void PpmInput::IcuOverflowCallback(ICUDriver *icu_driver) {
  PpmInput * const ppm_input = static_cast<PpmInput *>(icu_driver->self);
  // Increment with saturation.
  ppm_input->num_overflows_ =
      std::max(ppm_input->num_overflows_, ppm_input->num_overflows_ + 1);
}
