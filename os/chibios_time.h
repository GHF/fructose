// Adapter routines between Fructose time and ChibiOS ticks.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "base/integer.h"
#include "hal.h"
#include "os/time.h"

namespace Fructose {

// Conversion routines for ChibiOS ticks.
constexpr systime_t TicksFromTime(_TimeRepr time_point) {
  return ScaleRoundUp(time_point, static_cast<systime_t>(OSAL_ST_FREQUENCY),
                      kTimeResolution);
}
constexpr _TimeRepr TimeFromTicks(systime_t ticks) {
  return ScaleRoundUp(ticks, kTimeResolution,
                      static_cast<systime_t>(OSAL_ST_FREQUENCY));
}

// Derived class that permits access to the underlying representation.
class ChibiOsDuration : public Duration {
 public:
  // using Duration::Duration; would still have protected access.
  constexpr explicit ChibiOsDuration(_TimeRepr time) : Duration(time) {}
  using Duration::time_;
};

constexpr systime_t TicksFromDuration(const Duration& duration) {
  return TicksFromTime(static_cast<const ChibiOsDuration&>(duration).time_);
}
constexpr Duration DurationFromTicks(systime_t ticks) {
  return ChibiOsDuration(TimeFromTicks(ticks));
}

}  // namespace Fructose
