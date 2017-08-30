// Thinly wraps the ChibiOS HAL's blocking, non-polled SPI master API.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "bus/chibios_spi.h"

#include "hal.h"

namespace Fructose {

ChibiOsSpiMaster::ChibiOsSpiMaster(SPIDriver *spi_driver)
    : spi_driver_(spi_driver) {
}

void ChibiOsSpiMaster::Transfer(size_t n, const void *tx_buffer,
                                void *rx_buffer) {
  osalDbgCheck(tx_buffer != nullptr || rx_buffer != nullptr);

  if (tx_buffer == nullptr) {
    spiReceive(spi_driver_, n, rx_buffer);
  } else if (rx_buffer == nullptr) {
    spiSend(spi_driver_, n, tx_buffer);
  } else {
    spiExchange(spi_driver_, n, tx_buffer, rx_buffer);
  }
}

void ChibiOsSpiMaster::Acquire() {
  spiAcquireBus(spi_driver_);
}

void ChibiOsSpiMaster::Release() {
  spiReleaseBus(spi_driver_);
}

ChibiOsSpiDevice::ChibiOsSpiDevice(GpioLine select)
    : select_(select) {
}

void ChibiOsSpiDevice::Select() {
  Gpio::Clear(select_);
}

void ChibiOsSpiDevice::Deselect() {
  Gpio::Set(select_);
}

}  // namespace Fructose
