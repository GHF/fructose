// Interface for I2C bus master control.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "bus/bus_master.h"
#include "os/time.h"
#include <cstddef>

namespace Fructose {

using I2cAddress = uint8_t;

class I2cMaster : public BusMaster {
 public:
  virtual ~I2cMaster() {
  }
  // Perform a transfer transaction to slave. Address must be 7-bit and right-
  // aligned address. Either transmit or receive can be zero-length to omit
  // that action. If both transmit and receive are specified, transmit will
  // occur first.
  virtual bool Transfer(I2cAddress address, size_t tx_bytes,
                        const uint8_t *tx_buffer, size_t rx_bytes,
                        uint8_t *rx_buffer, Duration timeout) = 0;
};

}  // namespace Fructose
