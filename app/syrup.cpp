// Control application for Liftlord 2017, running on the OpenPilot Revolution
// flight controller.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "app/syrup.h"
#include "os/time.h"
#include "base/integer.h"
#include "os/chibios_time.h"
#include "app/log.h"
#include <cmath>

#include "hal.h"
#include "ch.h"

Syrup::Syrup(const SyrupConfig *config)
    : config_(config),
      dac_motors_{config->motor_left, config->motor_right},
      dir_gpios_{config->dir_left_gpio, config->dir_right_gpio},
      thread_main_(chThdGetSelfX()),
      drive_enabled_(false),
      commands_mutex_(_MUTEX_DATA(commands_mutex_)),
      commands_() {
}

void Syrup::RunLed() {
  using namespace Fructose;

  struct Blink {
    Duration on;
    Duration off;
  };
  static constexpr Blink disabled = {
      Duration::Milliseconds(500),
      Duration::Milliseconds(1000)
  };
  static constexpr Blink enabled = {
      Duration::Milliseconds(200),
      Duration::Milliseconds(100)
  };
  const Blink *pattern = &disabled;
  TimePoint time_point = TimePoint::Now();
  while (true) {
    Gpio::Clear(config_->led_stat_gpio);
    pattern = drive_enabled_ ? &enabled : &disabled;
    time_point = time_point.After(pattern->on);
    time_point.SleepUntil();

    Gpio::Set(config_->led_stat_gpio);
    pattern = drive_enabled_ ? &enabled : &disabled;
    time_point = time_point.After(pattern->off);
    time_point.SleepUntil();
  }
}

void Syrup::RunMain() {
  using namespace Fructose;

  while (true) {
    // Wait for next PPM pulse train.
    const eventmask_t events = chEvtWaitAnyTimeout(1U, MS2ST(1000));
    if (events != 0) {
      uint16_t commands[kCommandChannels] = {};
      const int num_channels = config_->ppm_input->ReadCommands(
          ArraySize(commands), commands);
      if (num_channels < kCommandChannels) {
        LogWarning("Read PPM train with only %d channels.", num_channels);
        continue;
      }

      chMtxLock(&commands_mutex_);
      std::copy(commands, commands + kCommandChannels, commands_);
      drive_enabled_ = true;
      chMtxUnlock(&commands_mutex_);

      Gpio::Set(config_->motors_enable_gpio);  // TODO remove
      pwmEnableChannel(config_->pwm_driver, config_->clamp_output_channel,
                       commands_[kClampChannel]);
      pwmEnableChannel(config_->pwm_driver, config_->lift_output_channel,
                       commands_[kLiftChannel]);
    } else {
      Gpio::Clear(config_->motors_enable_gpio);
      drive_enabled_ = false;
      pwmDisableChannel(config_->pwm_driver, config_->clamp_output_channel);
      pwmDisableChannel(config_->pwm_driver, config_->lift_output_channel);
      LogDebug("timed out waiting for PPM input");
    }
  }
}

static constexpr float CommandFromRaw(int command_raw) {
  const int kCommandMin = 1000;
  const int kCommandMax = 2000;
  const int kDeadband = 20;
  const int command = Fructose::MapRange(kCommandMin, kCommandMax,
                                         command_raw, -1000, 1000, kDeadband);
  return command * static_cast<float>(1.0 / 1000);
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
    const bool correction_reversed = commands_[kFlipChannel];
    chMtxUnlock(&commands_mutex_);

    if (enabled) {
      const float yaw = CommandFromRaw(yaw_command);
      const float throttle = CommandFromRaw(throttle_command);
      WriteMotor(kLeft, -yaw - throttle, config_->motor_write_timeout);
      WriteMotor(kRight, -yaw + throttle, config_->motor_write_timeout);
    } else {
      Gpio::Clear(config_->motors_enable_gpio);
    }

    time_point = time_point.After(loop_time);
    time_point.SleepUntil();
  }
}

void Syrup::Start() {
  using namespace Fructose;

  Gpio::Clear(config_->motors_enable_gpio);
  const Duration timeout = Duration::Milliseconds(10);
  WriteMotor(kLeft, 0.f, timeout);
  WriteMotor(kRight, 0.f, timeout);

  config_->imu->ResetDevice();
  config_->imu->SetupDevice(Mpu6000::CONFIG__DLPF_CFG__188_HZ,
                            Mpu6000::GYRO_CONFIG__FS_SEL__1000_DPS,
                            Mpu6000::ACCEL_CONFIG__FS_SEL__8_G,
                            kGyroRate, nullptr);

  config_->ppm_input->SetPpmListener(this);
  config_->ppm_input->StartCapture();

  Gpio::Set(config_->led_warn_gpio);
}

bool Syrup::WriteMotor(MotorChannel motor_channel, float command,
                       Fructose::Duration timeout) {
  const float abs_command = ::fabsf(command);
  const bool direction = std::signbit(command);
  const bool status = dac_motors_[motor_channel]->Write(abs_command, timeout);
  Fructose::Gpio::Write(dir_gpios_[motor_channel], direction);
  if (!status) {
    LogDebug("failed writing DAC %d", motor_channel);
  }
  return status;
}

void Syrup::HandleCommandsFromIsr(PpmInputInterface *) {
  // Wake input handling loop.
  osalSysLockFromISR();
  chEvtSignalI(thread_main_, 1U);
  osalSysUnlockFromISR();
}
