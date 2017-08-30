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
#include <algorithm>
#include <limits>
#include <cstdint>

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

// Represents an interval of time. Can not be negative. The maximum value is
// reserved to represent infinite duration (e.g. for timeout specifications).
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
    if (time_ == kInfinite) {
      return std::numeric_limits<MicrosecondsType>::max();
    }
    return ScaleRoundUp(time_, 1000000UL, kTimeResolution);
  }
  // Rounds up.
  constexpr MillisecondsType Milliseconds() const {
    if (time_ == kInfinite) {
      return std::numeric_limits<MillisecondsType>::max();
    }
    return ScaleRoundUp(time_, 1000UL, kTimeResolution);
  }
  // Rounds up.
  constexpr SecondsType Seconds() const {
    if (time_ == kInfinite) {
      return std::numeric_limits<SecondsType>::max();
    }
    return DivideRoundUp(time_, kTimeResolution);
  }

  // Construction functions.
  static constexpr Duration Microseconds(MicrosecondsType microseconds) {
    const _TimeRepr time = std::min(kMaximum,
        ScaleRoundUp(microseconds, kTimeResolution, 1000000UL));
    return Duration(time);
  }
  static constexpr Duration Milliseconds(MillisecondsType milliseconds) {
    const _TimeRepr time = std::min(kMaximum,
        ScaleRoundUp(milliseconds, kTimeResolution, 1000UL));
    return Duration(time);
  }
  static constexpr Duration Seconds(SecondsType seconds) {
    const _TimeRepr time = std::min(kMaximum, seconds * kTimeResolution);
    return Duration(time);
  }

  // Aliases for durations.
  static constexpr Duration Immediate() {
    return Duration(kImmediate);
  }
  static constexpr Duration Infinite() {
    return Duration(kInfinite);
  }
  static constexpr Duration Max() {
    return Duration(kMaximum);
  }

 private:
  static constexpr _TimeRepr kImmediate = 0;
  static constexpr _TimeRepr kInfinite =
      std::numeric_limits<_TimeRepr>::max();
  static constexpr _TimeRepr kMaximum = kInfinite - 1;

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
