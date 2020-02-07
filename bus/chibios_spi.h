// ChibiOS implementation of SPI bus masters and slave devices.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "bus/spi.h"
#include "gpio/gpio.h"

// Forward declarations.
typedef struct hal_spi_driver SPIDriver;

namespace Fructose {

class ChibiOsSpiMaster : public SpiMaster {
 public:
  // spi_driver must be already started and configured when constructed.
  explicit ChibiOsSpiMaster(SPIDriver* spi_driver);
  void Transfer(size_t n, const void* tx_buffer, void* rx_buffer) override;
  void Acquire() override;
  void Release() override;

 private:
  SPIDriver* const spi_driver_;
};

class ChibiOsSpiDevice : public SpiDevice {
 public:
  explicit ChibiOsSpiDevice(GpioLine select);
  void Select() override;
  void Deselect() override;

 private:
  const GpioLine select_;
};

}  // namespace Fructose
