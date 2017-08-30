// ChibiOS implementation of I2C master.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "bus/i2c.h"

// Forward declarations.
struct I2CDriver;

namespace Fructose {

class ChibiOsI2cMaster : public I2cMaster {
 public:
  explicit ChibiOsI2cMaster(I2CDriver *i2c_driver);
  bool Transfer(I2cAddress address,
                size_t tx_bytes, const uint8_t *tx_buffer,
                size_t rx_bytes, uint8_t *rx_buffer,
                Duration timeout) override;
  void Acquire() override;
  void Release() override;

 private:
  I2CDriver * const i2c_driver_;
};

}  // namespace Fructose
