// ChibiOS implementation of sleeps and delays. Time is converted between
// Fructose timebase and the ChibiOS system tick.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "os/chibios_time.h"

#include "base/integer.h"
#include "ch.h"
#include "osal.h"

namespace Fructose {

// TODO: This is a requirement I set after running into scaling issues going
// from Fructose time to ChibiOS time, but it really doesn't make much sense.
// Simplying the fraction of Fructose and ChibiOS resolutions could help with
// scaling.
static_assert(kTimeResolution == OSAL_ST_FREQUENCY,
              "ChibiOS time implementation must match tick frequency");

void TimePoint::SleepUntil() {
  const systime_t ticks = TicksFromTime(time_);
  chThdSleepUntil(ticks);  // Not available in OSAL API.
}

TimePoint TimePoint::Now() {
  const systime_t ticks = osalOsGetSystemTimeX();
  const _TimeRepr time_point = TimeFromTicks(ticks);
  return TimePoint(time_point);
}

void Duration::Sleep() {
  const systime_t ticks = TicksFromTime(time_);
  osalThreadSleep(ticks);
}

}  // namespace Fructose
