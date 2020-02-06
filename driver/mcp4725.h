// Controls the Microchip MCP4725 digital-to-analog converter (DAC) over I2C.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "bus/i2c.h"

namespace Fructose {

class Mcp4725 {
 public:
  enum Address : I2cAddress {
    kAddressA0Clear = 0x60,
    kAddressA0Set = 0x61,
  };
  enum Command : uint8_t {
    kWriteFastMode = 0x00,
    kWriteDac = 0x40,
    kWriteDacAndEeprom = 0x50,
  };
  // The input range is is 0--0x0FFF, which outputs 0--(Vdd - 1 LSb). The
  // scaling factor for raw data is (Vdd / 4096) per LSb.
  static constexpr uint16_t kFullScaleRange = 0x1000U;

  explicit Mcp4725(I2cMaster* i2c_master, Address address);
  // Data should be right-aligned. Range: 0--(kFullScaleRange - 1).
  bool WriteRaw(uint16_t data, Duration timeout = Duration::Infinite());
  // Input range of 0--((kFullScaleRange - 1) / kFullScaleRange). Normal
  // values outside of this range will be clamped to a valid DAC range.
  bool Write(float value, Duration timeout = Duration::Infinite());

 private:
  I2cMaster* const i2c_master_;
  const Address address_;
};

}  // namespace Fructose
