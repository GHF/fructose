// Representation and interface for point in time and duration of time.
// Definition of sleeps/delays must be implemented specific to the system.
// The time types are intentionally independently implemented classes rather
// than aliases to opaque system types, because this allows construction of
// real-unit durations without having to make a system call. This necessarily
// creates a Fructose-specific time base that must be converted to system time
// to be useful, but that is (still? more?) compatible with mocks and fakes.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "base/integer.h"
#include <cstdint>
#include <limits>

namespace Fructose {

// Arithmetic type that represents both system time stamp and duration.
// Do not use directly.
using _TimeRepr = uint32_t;
// The denominator of the above type if the resulting unit is seconds.
constexpr const unsigned kTimeResolution = 10000UL;

// Forward declarations.
class Duration;

// Represents a point in time.
class TimePoint {
 public:
  // From this point, compute the point after the interval elapses.
  constexpr TimePoint After(Duration duration) const;
  void SleepUntil();

  static TimePoint Now();

 private:
  explicit constexpr TimePoint(_TimeRepr time)
      : time_(time) {
  }

  _TimeRepr time_;
  friend class Duration;
};

// Represents an interval of time. Can not be negative.
class Duration {
 public:
  using MicrosecondsType = uint32_t;
  using MillisecondsType = uint32_t;
  using SecondsType = uint32_t;

  // Create from a difference of two points time. end must be greater than
  // start to avoid overflow.
  constexpr Duration(TimePoint start, TimePoint end)
      : time_(end.time_ - start.time_) {
  }

  // Ask the system to suspend the current thread for this duration.
  void Sleep();

  // Rounds up.
  constexpr MicrosecondsType Microseconds() const {
    return ScaleRoundUp(time_, 1000000UL, kTimeResolution);
  }
  // Rounds up.
  constexpr MillisecondsType Milliseconds() const {
    return ScaleRoundUp(time_, 1000UL, kTimeResolution);
  }
  // Rounds up.
  constexpr SecondsType Seconds() const {
    return DivideRoundUp(time_, kTimeResolution);
  }

  // Construction functions.
  static constexpr Duration Microseconds(MicrosecondsType microseconds) {
    return Duration(ScaleRoundUp(microseconds, kTimeResolution, 1000000UL));
  }
  static constexpr Duration Milliseconds(MillisecondsType milliseconds) {
    return Duration(ScaleRoundUp(milliseconds, kTimeResolution, 1000UL));
  }
  static constexpr Duration Seconds(SecondsType seconds) {
    return Duration(seconds * kTimeResolution);
  }

 private:
  explicit constexpr Duration(_TimeRepr time)
      : time_(time) {
  }

  _TimeRepr time_;
  friend class TimePoint;
};

constexpr TimePoint TimePoint::After(Duration duration) const {
  return TimePoint(time_ + duration.time_);
}

}
