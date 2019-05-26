// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "base/range_map.h"

#include <cstddef>

#include "catch2/catch.hpp"

namespace Fructose {
namespace {

constexpr int16_t kServoMin = 1000;
constexpr int16_t kServoMax = 2000;

TEST_CASE("Map value in a range to another range", "[base][base/range_map]") {
  constexpr RangeMap map(-50, 100, 0, kServoMin, kServoMax);

  CHECK(1500 == map.Map(25));
  CHECK(kServoMin == map.Map(-50));
  CHECK(kServoMax == map.Map(100));

  // Test that the input is clamped against the range limits.
  CHECK(kServoMin == map.Map(-1000000));
  CHECK(kServoMax == map.Map(1000000));

  CHECK(1333 == map.Map(0));
  CHECK(1667 == map.Map(50));
}

TEST_CASE("Inputs deadband maps to output midpoint", "[base][base/range_map]") {
  constexpr RangeMap map(-100, 100, 10, kServoMin, kServoMax);

  CHECK(1500 == map.Map(0));
  CHECK(kServoMin == map.Map(-100));
  CHECK(kServoMax == map.Map(100));

  SECTION("Deadband inputs") {
    const int i = GENERATE(range(-10, 10 + 1));
    CAPTURE(i);
    CHECK(1500 == map.Map(i));
  }

  SECTION("Leaving deadband") {
    CAPTURE(map.Map(11));

    // Leaving the deadband should move the output value.
    CHECK(1500 < map.Map(11));

    // But the output shouldn't jump to 11% of the positive output half.
    CHECK(1555 > map.Map(11));
  }
}

TEST_CASE("Map to an inverted range", "[base][base/range_map]") {
  // The output range goes high to low.
  constexpr RangeMap map(-100, 100, 0, kServoMax, kServoMin);

  CHECK(1500 == map.Map(0));
  CHECK(kServoMax == map.Map(-100));
  CHECK(kServoMin == map.Map(100));

  CHECK(1250 == map.Map(50));
  CHECK(1750 == map.Map(-50));
}

}  // namespace
}  // namespace Fructose
