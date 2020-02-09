// Control application for Liftlord 2017, running on the OpenPilot Revolution
// flight controller.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "app/syrup.h"

#include <cmath>

#include "app/log.h"
#include "base/integer.h"
#include "base/range_map.h"
#include "ch.h"
#include "hal.h"
#include "os/chibios_time.h"
#include "os/time.h"

namespace {

Fructose::RangeMap kCommandMapper(1000, 2000, 20, -1000, 1000);

constexpr float CommandFromRaw(int command_raw) {
  const int command = kCommandMapper.Map(command_raw);
  return command * static_cast<float>(1.0 / 1000);
}

}  // namespace

Syrup::Syrup(const SyrupConfig* config)
    : config_(config),
      thread_main_(chThdGetSelfX()),
      drive_enabled_(false),
      commands_mutex_(_MUTEX_DATA(commands_mutex_)),
      commands_(),
      warn_thread_(nullptr) {}

void Syrup::RunStatusLed() {
  using namespace Fructose;
  TimePoint time_point = TimePoint::Now();
  while (true) {
    Gpio::Set(config_->led_stat_gpio);
    time_point = time_point.After(Duration::Milliseconds(490));
    time_point.SleepUntil();
    if (drive_enabled_) {
      Gpio::Clear(config_->led_stat_gpio);
      time_point = time_point.After(Duration::Milliseconds(10));
      time_point.SleepUntil();
    }
  }
}

void Syrup::RunWarnLed() {
  using namespace Fructose;
  while (true) {
    Gpio::Set(config_->led_warn_gpio);
    chEvtWaitOne(kWarnErrorEvent);
    Gpio::Clear(config_->led_warn_gpio);
    Duration::Milliseconds(100).Sleep();
  }
}

void Syrup::RunMain() {
  using namespace Fructose;

  while (true) {
    // Wait for next PPM pulse train.
    if (chEvtWaitOneTimeout(kMainCommandEvent, TIME_MS2I(500)) != 0) {
      uint16_t commands[kCommandChannels] = {};
      const int num_channels =
          config_->ppm_input->ReadCommands(ArraySize(commands), commands);
      if (num_channels < kCommandChannels) {
        LogWarning("Read PPM train with only %d channels.", num_channels);
        continue;
      }

      chMtxLock(&commands_mutex_);
      std::copy(commands, commands + kCommandChannels, commands_);
      drive_enabled_ = true;
      chMtxUnlock(&commands_mutex_);

      drive_enabled_ = true;
    } else {
      // Timed out.
      drive_enabled_ = false;
      DisableMotors();
      if (warn_thread_ != nullptr) {
        chEvtSignal(warn_thread_, kWarnErrorEvent);
      }
      LogDebug("timed out waiting for PPM input");
    }
  }
}

void Syrup::RunGyro() {
  using namespace Fructose;

  TimePoint time_point = TimePoint::Now();
  const Duration loop_time = Duration::Milliseconds(kGyroLoopTimeMs);
  while (true) {
    chMtxLock(&commands_mutex_);
    const bool enabled = drive_enabled_;
    const int yaw_command = commands_[kSteerChannel];
    const int throttle_command = commands_[kThrottleChannel];
    const bool correction_reversed = commands_[kFlipChannel] >= 1500;
    chMtxUnlock(&commands_mutex_);

    if (enabled) {
      const float yaw = CommandFromRaw(yaw_command);
      const float throttle = CommandFromRaw(throttle_command);
      WriteMotor(MotorChannel::kLeft, yaw + throttle);
      WriteMotor(MotorChannel::kRight, yaw - throttle);
    } else {
      DisableMotors();
    }

    time_point = time_point.After(loop_time);
    time_point.SleepUntil();
  }
}

void Syrup::Start() {
  using namespace Fructose;
  DisableMotors();

  config_->imu->ResetDevice();
  config_->imu->SetupDevice(
      Mpu6000::CONFIG__DLPF_CFG__188_HZ, Mpu6000::GYRO_CONFIG__FS_SEL__1000_DPS,
      Mpu6000::ACCEL_CONFIG__FS_SEL__8_G, kGyroRate, nullptr);

  config_->ppm_input->SetPpmListener(this);
  config_->ppm_input->StartCapture();

  Gpio::Set(config_->led_warn_gpio);
}

void Syrup::WriteMotor(MotorChannel motor_channel, float command) {
  command = Fructose::Clamp(command, -1.f, 1.f);
  const pwmcnt_t width = static_cast<pwmcnt_t>(command * 500.f) + 1500;
  if (motor_channel == MotorChannel::kLeft) {
    pwmEnableChannel(config_->pwm_driver, config_->left_output_channel, width);
  } else {
    pwmEnableChannel(config_->pwm_driver, config_->right_output_channel, width);
  }
}

void Syrup::DisableMotors() {
  pwmDisableChannel(config_->pwm_driver, config_->left_output_channel);
  pwmDisableChannel(config_->pwm_driver, config_->right_output_channel);
}

void Syrup::HandleCommandsFromIsr(PpmInputInterface*) {
  // Wake input handling loop.
  osalSysLockFromISR();
  chEvtSignalI(thread_main_, kMainCommandEvent);
  osalSysUnlockFromISR();
}
