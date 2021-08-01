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

constexpr Fructose::RangeMap kCommandMapper(1000, 2000, 20, -1000, 1000);

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
      decltype(commands_) commands = {};
      const int num_channels =
          config_->ppm_input->ReadCommands(commands.size(), commands.data());
      if (num_channels < int{commands.size()}) {
        LogWarning("Read PPM train with only %d channels.", num_channels);
        continue;
      }

      chMtxLock(&commands_mutex_);
      std::copy(commands.cbegin(), commands.cend(), commands_.begin());
      drive_enabled_ = true;
      chMtxUnlock(&commands_mutex_);

      const auto weapon_command = command_for_channel(CommandChannel::kWeapon);
      WriteMotor(MotorChannel::kWeaponOneshot42, weapon_command);
      WriteMotor(MotorChannel::kWeapon, weapon_command);
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
    float gyro_rates[3] = {};
    config_->imu->Read(&gyro_rates, nullptr, nullptr);
    const float& z_rate = gyro_rates[2];
    constexpr float kZRange = 9.f;  // in rad/sec

    chMtxLock(&commands_mutex_);
    const bool enabled = drive_enabled_;
    const int yaw_command = command_for_channel(CommandChannel::kYaw);
    const int surge_command = command_for_channel(CommandChannel::kSurge);
    const bool flipped = command_for_channel(CommandChannel::kFlip) >= 1500;
    chMtxUnlock(&commands_mutex_);

    if (enabled) {
      const float yaw = CommandFromRaw(yaw_command);
      const float surge = flipped ? -CommandFromRaw(surge_command)
                                  : CommandFromRaw(surge_command);
      const float error = z_rate - yaw * kZRange;
      const float kP = 0.1f * (flipped ? -1.f : 1.f);
      const float corrected_yaw = error * kP;
      WriteMotor(MotorChannel::kLeft, command_from_normalized(surge));
      WriteMotor(MotorChannel::kRight, command_from_normalized(corrected_yaw));
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

void Syrup::WriteMotor(MotorChannel motor_channel, uint32_t pwm_command) {
  const ServoOutput servo_out = servo_output_for_channel(motor_channel);
  PWMDriver* const pwm_driver = pwm_for_servo_output(servo_out);
  // Regular servo output.
  if (pwm_driver == config_->pwm_1_2_driver) {
    pwm_command =
        Fructose::Scale<std::ratio<STM32_TIMCLK1, 24'000'000>>(pwm_command);
  } else {
    pwm_command =
        Fructose::Scale<std::ratio<STM32_TIMCLK1 / 4, 1'000'000>>(pwm_command);
  }
  pwmEnableChannel(pwm_driver, channel_for_servo_output(servo_out),
                   pwm_command);
}

void Syrup::DisableMotors() {
  constexpr ServoOutput servo_outputs[] = {ServoOutput::k1, ServoOutput::k2,
                                           ServoOutput::k3, ServoOutput::k4,
                                           ServoOutput::k5, ServoOutput::k6};
  for (const auto servo_out : servo_outputs) {
    pwmDisableChannel(pwm_for_servo_output(servo_out),
                      channel_for_servo_output(servo_out));
  }
}

void Syrup::HandleCommandsFromIsr(PpmInputInterface*) {
  // Wake input handling loop.
  osalSysLockFromISR();
  chEvtSignalI(thread_main_, kMainCommandEvent);
  osalSysUnlockFromISR();
}
