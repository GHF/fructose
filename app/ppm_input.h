// Input driver on for combined pulse position modulation (CPPM) radio control
// commands. This is a legacy library with no Fructose abstraction.
//
// (C) Copyright 2014-2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>

// Forward declarations.
struct ICUDriver;
class PpmListener;

class PpmInputInterface {
 public:
  virtual ~PpmInputInterface() {}
  virtual void StartCapture() = 0;
  virtual int ReadCommands(int commands_capacity, uint16_t* commands) = 0;
  virtual void SetPpmListener(PpmListener* ppm_listener) = 0;
};

class PpmListener {
 public:
  virtual ~PpmListener() {}
  virtual void HandleCommandsFromIsr(PpmInputInterface* ppm_input) = 0;
};

/**
 * @brief Driver for reading radio PPM signals.
 */
class PpmInput : public PpmInputInterface {
 public:
  /**
   * @brief Creates a driver structure for reading and parsing RC PPM pulses.
   *
   * @param icu_driver OS driver for capturing servo input edges.
   */
  PpmInput(ICUDriver* icu_driver);
  void Start();

  /**
   * @brief Starts capturing and processing RC PPM input.
   */
  void StartCapture() override;
  int ReadCommands(int commands_capacity, uint16_t* commands) override;
  void SetPpmListener(PpmListener* ppm_listener) override {
    ppm_listener_ = ppm_listener;
  }

 protected:
  /// Lower bound of pulse width to be considered a sync pulse.
  static constexpr int kSyncMin = 5000;
  /// Lower bound of channel width.
  static constexpr int kInputMin = 970;
  /// Upper bound of channel width.
  static constexpr int kInputMax = 2030;
  /// Maximum number of channels to handle.
  static constexpr int kMaxChannels = 8;

  /**
   * @brief Handles servo pulse event.
   *
   * @param width Width of the pulse captured.
   * @param period Period of the pulse captured.
   */
  void HandlePulse(int width, int period);

  /**
   * @brief Handles servo pulse input falling edges.
   *
   * @param icu_driver Input capture OS driver that originated the callback.
   */
  static void IcuWidthCallback(ICUDriver* icu_driver);

  /**
   * @brief Handles servo pulse input rising edges.
   *
   * @param icu_driver Input capture OS driver that originated the callback.
   */
  static void IcuPeriodCallback(ICUDriver* icu_driver);

  /**
   * @brief Handles servo pulse input unit timer overflows.
   *
   * @param icu_driver Input capture OS driver that originated the callback.
   */
  static void IcuOverflowCallback(ICUDriver* icu_driver);

  ICUDriver* const icu_driver_;  ///< Timer input capture driver.
  int num_overflows_;  ///< Times the timer overflowed since last edge.
  uint16_t commands_[kMaxChannels];  ///< Storage for current channels.
  int channel_;                      ///< Index of current command to capture.
  uint16_t last_commands_[kMaxChannels];  ///< Commands to be read by user.
  int last_channels_;                     ///< Number of commands stored.
  PpmListener* ppm_listener_;
};
