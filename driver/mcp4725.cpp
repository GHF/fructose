// Controls the Microchip MCP4725 over I2C. Does not suport writes to EEPROM,
// power down mode, reads, or continuous writes.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "driver/mcp4725.h"
#include "bus/bus_master.h"
#include "base/integer.h"
#include <cmath>
#include <cstdint>

namespace Fructose {

Mcp4725::Mcp4725(I2cMaster *i2c_master, Address address)
    : i2c_master_(i2c_master),
      address_(address) {
}

bool Mcp4725::WriteRaw(uint16_t data, Duration timeout) {
  const uint8_t upper_4b = (data >> 8U) & 0x0FU;
  const uint8_t lower_8b = data;
  const uint8_t tx_buffer[2] =
      { static_cast<uint8_t>(kWriteFastMode | upper_4b), lower_8b };
  BusGuard bus_guard(i2c_master_);
  return i2c_master_->Transfer(address_, ArraySize(tx_buffer), tx_buffer, 0,
                               nullptr, timeout);
}

bool Mcp4725::Write(float value, Duration timeout) {
  const int scaled_value = ::lroundf(value * kFullScaleRange);
  const uint16_t data = Clamp<int>(scaled_value, 0, kFullScaleRange - 1);
  return WriteRaw(data, timeout);
}

}  // namespace Fructose
