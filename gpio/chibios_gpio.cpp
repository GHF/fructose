// Implementation of GPIO interface using ChibiOS's HAL's PAL API. The minor
// hit of function calls is worth not having to include all of ChibiOS and its
// HAL by headers.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "gpio/gpio.h"

#include "hal.h"

namespace Fructose {
namespace Gpio {

bool Read(Line gpio) {
  return palReadLine(static_cast<ioline_t>(gpio));
}

void Write(Line gpio, bool bit) {
  palWriteLine(static_cast<ioline_t>(gpio), bit ? 1U : 0U);
}

void Set(Line gpio) {
  palSetLine(static_cast<ioline_t>(gpio));
}

void Clear(Line gpio) {
  palClearLine(static_cast<ioline_t>(gpio));
}

void Toggle(Line gpio) {
  palToggleLine(static_cast<ioline_t>(gpio));
}

void SetMode(Line gpio, Mode mode) {
  palSetLineMode(static_cast<ioline_t>(gpio), mode);
}

}  // namespace Gpio
}  // namespace Fructose
