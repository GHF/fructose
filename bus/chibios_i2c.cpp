// Thinly wraps the ChibiOS HAL's high level I2C interface that seems to only
// support fully-managed transactions.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "bus/chibios_i2c.h"
#include "os/chibios_time.h"

#include "hal.h"

namespace Fructose {

ChibiOsI2cMaster::ChibiOsI2cMaster(I2CDriver *i2c_driver)
    : i2c_driver_(i2c_driver) {
}

bool ChibiOsI2cMaster::Transfer(I2cAddress address,
                                size_t tx_bytes, const uint8_t *tx_buffer,
                                size_t rx_bytes, uint8_t *rx_buffer,
                                Duration timeout) {
  osalDbgCheck((tx_bytes > 0 || rx_bytes > 0) &&
               (tx_bytes == 0 || (tx_bytes > 0U && tx_buffer != NULL)));

  const i2caddr_t address_driver = address;
  const systime_t timeout_ticks = TicksFromDuration(timeout);
  if (tx_bytes == 0) {
    const msg_t status =
        i2cMasterReceiveTimeout(i2c_driver_, address_driver, rx_buffer,
                                rx_bytes, timeout_ticks);
    return status == MSG_OK;
  }
  const msg_t status =
      i2cMasterTransmitTimeout(i2c_driver_, address_driver, tx_buffer,
                               tx_bytes, rx_buffer, rx_bytes, timeout_ticks);
  return status == MSG_OK;
}

void ChibiOsI2cMaster::Acquire() {
#if I2C_USE_MUTUAL_EXCLUSION
  i2cAcquireBus(i2c_driver_);
#endif  // I2C_USE_MUTUAL_EXCLUSION
}

void ChibiOsI2cMaster::Release() {
#if I2C_USE_MUTUAL_EXCLUSION
  i2cReleaseBus(i2c_driver_);
#endif  // I2C_USE_MUTUAL_EXCLUSION
}

}  // namespace Fructose
