// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "base/integer.h"

#include <cstddef>
#include "catch2/catch.hpp"

namespace Fructose {
namespace {

TEST_CASE("Deduce array size", "[base][base/integer]") {
  int A[2];
  CHECK(2 == ArraySize(A));
  CHECK(2 == ArraySize<0>(A));
  CHECK(sizeof(A) / sizeof(A[0]) == ArraySize(A));
}

TEST_CASE("Deduce multidimensional array sizes", "[base][base/integer]") {
  int A[3][2][1];
  CHECK(3 == ArraySize(A));
  CHECK(3 == ArraySize<0>(A));
  CHECK(2 == ArraySize<1>(A));
  CHECK(1 == ArraySize<2>(A));
}

TEST_CASE("Determine sign of integer", "[base][base/integer]") {
  CHECK(0 == SignOf(0));
  CHECK(1 == SignOf(1));
  CHECK(1 == SignOf(10));
  CHECK(1 == SignOf(std::numeric_limits<int>::max()));
  CHECK(-1 == SignOf(-1));
  CHECK(-1 == SignOf(-10));
  CHECK(-1 == SignOf(std::numeric_limits<int>::min()));
}

TEST_CASE("Determine sign of unsigned", "[base][base/integer]") {
  CHECK(0 == SignOf(0U));
  CHECK(1 == SignOf(1U));
  CHECK(1 == SignOf(10U));
  CHECK(1 == SignOf(std::numeric_limits<unsigned>::max()));
}

TEST_CASE("Compute quotient ceiling", "[base][base/integer]") {
  CHECK(0 == DivideRoundUp(0, 1));
  CHECK(0 == DivideRoundUp(0, 2));
  CHECK(1 == DivideRoundUp(1, 1));
  CHECK(1 == DivideRoundUp(1, 2));
  CHECK(2 == DivideRoundUp(2, 1));
  CHECK(2 == DivideRoundUp(3, 2));
  CHECK(2 == DivideRoundUp(5, 3));

  // Numerator + denominator would overflow
  CHECK(2 == DivideRoundUp(0x40000002, 0x3fffffff));

  // Negative quotients round away from zero
  CHECK(-1 == DivideRoundUp(-1, 1));
  CHECK(-1 == DivideRoundUp(-1, 2));
  CHECK(-2 == DivideRoundUp(-2, 1));
  CHECK(-2 == DivideRoundUp(-3, 2));
  CHECK(-2 == DivideRoundUp(-5, 3));
  CHECK(-1 == DivideRoundUp(1, -1));
  CHECK(-1 == DivideRoundUp(1, -2));
  CHECK(-2 == DivideRoundUp(2, -1));
  CHECK(-2 == DivideRoundUp(3, -2));
  CHECK(-2 == DivideRoundUp(5, -3));

  // Numerator underflow
  CHECK(-2 == DivideRoundUp(std::numeric_limits<int>::min(), 0x40000000));
  CHECK(-3 == DivideRoundUp(std::numeric_limits<int>::min(), 0x3fffffff));

  // Unsigned
  CHECK(0U == DivideRoundUp(0U, 1U));
  CHECK(0U == DivideRoundUp(0U, 2U));
  CHECK(1U == DivideRoundUp(1U, 1U));
  CHECK(1U == DivideRoundUp(1U, 2U));
  CHECK(2U == DivideRoundUp(2U, 1U));
  CHECK(2U == DivideRoundUp(3U, 2U));
  CHECK(2U == DivideRoundUp(5U, 3U));

  // sizeof as an argument
  CHECK(2U == DivideRoundUp(sizeof(uint64_t), sizeof(uint32_t)));
  CHECK(2U == DivideRoundUp(8U, sizeof(uint32_t)));
  CHECK(3U == DivideRoundUp(sizeof(uint64_t), 3U));

  // Promotion
  CHECK(0x10000 == DivideRoundUp(0x20000, static_cast<int16_t>(2)));
  CHECK(-32769 == DivideRoundUp(-32769, static_cast<int16_t>(1)));
  CHECK(65536U == DivideRoundUp(0x20000U, static_cast<uint16_t>(2)));
}

}  // namespace
}  // namespace Fructose
