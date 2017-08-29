// Definitions for InvenSense MPU-6000 communications logic.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "driver/mpu6000.h"
#include "bus/spi.h"

namespace Fructose {

Mpu6000::Mpu6000(SpiMaster *spi_master, SpiSlave *spi_slave)
    : spi_master_(spi_master),
      spi_slave_(spi_slave) {
}

void Mpu6000::WriteRegister(uint8_t address, uint8_t data) {
  const uint8_t address_masked = address & ~kRegisterReadMask;
  const uint8_t tx_buffer[] = { address_masked, data };
  spi_slave_->Select();
  spi_master_->Transfer(sizeof(tx_buffer), tx_buffer, nullptr);
  spi_slave_->Deselect();
}

void Mpu6000::ReadRegister(uint8_t address, size_t n, uint8_t *rx_buffer) {
  const uint8_t address_masked = address | kRegisterReadMask;
  spi_slave_->Select();
  spi_master_->Transfer(1, &address_masked, nullptr);
  spi_master_->Transfer(n, nullptr, rx_buffer);
  spi_slave_->Deselect();
}

// Convenience function to read a single register. Uses only one SPI full-
// duplex transfer.
uint8_t Mpu6000::ReadRegister(uint8_t address) {
  const uint8_t address_masked = address | kRegisterReadMask;
  const uint8_t tx_buffer[2] = { address_masked };  // Second byte is dummy.
  uint8_t rx_buffer[2];  // First byte is dummy.
  spi_slave_->Select();
  spi_master_->Transfer(2, tx_buffer, rx_buffer);
  spi_slave_->Deselect();
  return rx_buffer[1];
}

}  // namespace Fructose
