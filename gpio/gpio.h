// Generic general purpose input/output (GPIO) interface. This is not any kind
// of polymorphic since GPIOs are global and can be accessed only one way.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>

namespace Fructose {
namespace Gpio {

// This must be large enough to fit the implementation's GPIO types.
using Line = uint32_t;
// Mode is implementation-dependent.
using Mode = uint32_t;

bool Read(Line gpio);
void Write(Line gpio, bool bit);
void Set(Line gpio);
void Clear(Line gpio);
void Toggle(Line gpio);
void SetMode(Line gpio, Mode mode);

}  // namespace Gpio

// Convenience type in Fructose, to avoid having to write Gpio::Line.
using GpioLine = Gpio::Line;

}  // namespace Fructose
