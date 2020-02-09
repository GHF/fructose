// Control application for Liftlord 2017, running on the OpenPilot Revolution
// flight controller.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cmath>

#include "app/ppm_input.h"
#include "driver/mcp4725.h"
#include "driver/mpu6000.h"
#include "gpio/gpio.h"

// TODO: ugh.
#include "ch.h"
#include "hal.h"

struct SyrupConfig {
  Fructose::Mpu6000* imu;
  PpmInputInterface* ppm_input;
  Fructose::GpioLine led_stat_gpio;
  Fructose::GpioLine led_warn_gpio;
  PWMDriver* pwm_1_2_driver;
  PWMDriver* pwm_3_4_5_6_driver;
};

class Syrup : public PpmListener {
 public:
  // Servo output pins available on flight controller boards.
  enum class ServoOutput {
    k1 = 1,
    k2 = 2,
    k3 = 3,
    k4 = 4,
    k5 = 5,
    k6 = 6,
  };

  // Input command channels per incoming pulse trains. Not enum class for ease
  // of use as constants.
  enum class CommandChannel {
    kWeapon,
    kYaw,
    kSurge,
    kRudder,
    kFlip,
    kChannels
  };

  // Available motors to control.
  enum class MotorChannel { kWeapon, kWeaponOneshot42, kLeft, kRight };

  Syrup(const SyrupConfig* config);

  constexpr ServoOutput servo_output_for_channel(
      MotorChannel motor_channel) const {
    switch (motor_channel) {
      case MotorChannel::kWeaponOneshot42:
        return ServoOutput::k1;
      case MotorChannel::kWeapon:
        return ServoOutput::k5;
      case MotorChannel::kLeft:
        return ServoOutput::k3;
      case MotorChannel::kRight:
        return ServoOutput::k4;
    }
    return ServoOutput::k6;
  }

  auto command_for_channel(CommandChannel command_channel) const {
    return commands_[static_cast<std::underlying_type_t<CommandChannel>>(
        command_channel)];
  }

  void set_warn_thread(thread_t* warn_thread) { warn_thread_ = warn_thread; }

  void Start();
  [[noreturn]] void RunStatusLed();
  [[noreturn]] void RunWarnLed();
  [[noreturn]] void RunMain();
  [[noreturn]] void RunGyro();

 private:
  static constexpr int kGyroLoopTimeMs = 10;
  static constexpr float kGyroRate = 1000.0 / kGyroLoopTimeMs;
  static constexpr eventmask_t kMainCommandEvent = 0b1U;
  static constexpr eventmask_t kWarnErrorEvent = 0b1U;

  // |pwm_command| should be from 1000–2000.
  void WriteMotor(MotorChannel motor_channel, uint32_t pwm_command);
  void DisableMotors();
  void HandleCommandsFromIsr(PpmInputInterface*) override;

  // Convert a [-1,+1] command to [1000,2000].
  constexpr uint32_t command_from_normalized(float command) const {
    command = Fructose::Clamp(command, -1.f, 1.f);
    return std::lroundf(command * 500.f) + 1500;
  }

  // TODO(xo): Make this not specific to Revo board.
  PWMDriver* pwm_for_servo_output(ServoOutput servo_output) const {
    switch (servo_output) {
      case ServoOutput::k1:
        [[fallthrough]];
      case ServoOutput::k2:
        return config_->pwm_1_2_driver;
      case ServoOutput::k3:
        [[fallthrough]];
      case ServoOutput::k4:
        [[fallthrough]];
      case ServoOutput::k5:
        [[fallthrough]];
      case ServoOutput::k6:
        return config_->pwm_3_4_5_6_driver;
    }
    return nullptr;
  }

  // TODO(xo): Make this not specific to Revo board.
  constexpr pwmchannel_t channel_for_servo_output(
      ServoOutput servo_output) const {
    switch (servo_output) {
      case ServoOutput::k1:
        return 2;
      case ServoOutput::k2:
        return 3;
      case ServoOutput::k3:
        return 3;
      case ServoOutput::k4:
        return 2;
      case ServoOutput::k5:
        return 1;
      case ServoOutput::k6:
        return 0;
    }
    return -1;
  }

  const SyrupConfig* const config_;
  thread_t* const thread_main_;
  bool drive_enabled_;
  mutex_t commands_mutex_;
  std::array<uint16_t, static_cast<size_t>(CommandChannel::kChannels)>
      commands_;
  thread_t* warn_thread_;
};
