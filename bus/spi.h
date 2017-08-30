// Interface for SPI bus endpoints.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "bus/bus_master.h"

#include <cstddef>

namespace Fructose {

class SpiMaster : public BusMaster {
 public:
  virtual ~SpiMaster() {
  }
  virtual void Transfer(size_t n, const void *tx_buffer, void *rx_buffer) = 0;
};

class SpiSlave {
 public:
  virtual ~SpiSlave() {
  }
  virtual void Select() = 0;
  virtual void Deselect() = 0;
};

}  // namespace Fructose
