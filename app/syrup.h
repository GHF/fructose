// Control application for Liftlord 2017, running on the OpenPilot Revolution
// flight controller.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "app/ppm_input.h"
#include "driver/mcp4725.h"
#include "driver/mpu6000.h"
#include "gpio/gpio.h"

// TODO: ugh.
#include "ch.h"
#include "hal.h"

struct SyrupConfig {
  Fructose::Mcp4725* motor_left;
  Fructose::Mcp4725* motor_right;
  Fructose::GpioLine motors_enable_gpio;
  Fructose::GpioLine dir_left_gpio;
  Fructose::GpioLine dir_right_gpio;
  Fructose::Mpu6000* imu;
  PpmInputInterface* ppm_input;
  Fructose::GpioLine led_stat_gpio;
  Fructose::GpioLine led_warn_gpio;
  PWMDriver* pwm_driver;
  pwmchannel_t clamp_output_channel;
  pwmchannel_t lift_output_channel;
  Fructose::Duration motor_write_timeout;
};

class Syrup : public PpmListener {
 public:
  enum CommandChannel {
    kClampChannel,
    kSteerChannel,
    kThrottleChannel,
    kLiftChannel,
    kFlipChannel,
    kCommandChannels
  };
  enum MotorChannel { kLeft, kRight, kMotorChannels };

  Syrup(const SyrupConfig* config);
  void Start();
  [[noreturn]] void RunLed();
  [[noreturn]] void RunMain();
  [[noreturn]] void RunGyro();

 private:
  static constexpr int kGyroLoopTimeMs = 10;
  static constexpr float kGyroRate = 1000.0 / kGyroLoopTimeMs;

  bool WriteMotor(MotorChannel motor_channel,
                  float command,
                  Fructose::Duration timeout);
  void HandleCommandsFromIsr(PpmInputInterface*) override;

  const SyrupConfig* const config_;
  Fructose::Mcp4725* const dac_motors_[kMotorChannels];
  const Fructose::GpioLine dir_gpios_[kMotorChannels];
  thread_t* const thread_main_;
  bool drive_enabled_;
  mutex_t commands_mutex_;
  uint16_t commands_[kCommandChannels];
};
