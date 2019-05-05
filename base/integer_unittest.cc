// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "base/integer.h"

#include <cstddef>
#include <limits>
#include <ratio>

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

  // Unsigned
  CHECK(0U == DivideRoundUp(0U, 1U));
  CHECK(0U == DivideRoundUp(0U, 2U));
  CHECK(1U == DivideRoundUp(1U, 1U));
  CHECK(1U == DivideRoundUp(1U, 2U));
  CHECK(2U == DivideRoundUp(2U, 1U));
  CHECK(2U == DivideRoundUp(3U, 2U));
  CHECK(2U == DivideRoundUp(5U, 3U));
}

TEST_CASE("Round negative quotients away from zero", "[base][base/integer]") {
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
}

TEST_CASE("Division doesn't suffer from overflow", "[base][base/integer]") {
  // Numerator underflow
  CHECK(-2 == DivideRoundUp(std::numeric_limits<int>::min(), 0x40000000));
  CHECK(-3 == DivideRoundUp(std::numeric_limits<int>::min(), 0x3fffffff));

  // Numerator + denominator would overflow
  CHECK(2 == DivideRoundUp(0x40000002, 0x3fffffff));
}

TEST_CASE("Divide mixed types", "[base][base/integer]") {
  // sizeof as an argument
  CHECK(2U == DivideRoundUp(sizeof(uint64_t), sizeof(uint32_t)));
  CHECK(2U == DivideRoundUp(8U, sizeof(uint32_t)));
  CHECK(3U == DivideRoundUp(sizeof(uint64_t), 3U));

  // Promotion
  CHECK(0x10000 == DivideRoundUp(0x20000, static_cast<int16_t>(2)));
  CHECK(-32769 == DivideRoundUp(-32769, static_cast<int16_t>(1)));
  CHECK(65536U == DivideRoundUp(0x20000U, static_cast<uint16_t>(2)));
}

TEST_CASE("Scale value by a ratio", "[base][base/integer]") {
  constexpr int A = 3, B = 1000;

  CHECK(0 == Scale(0, A, B));
  CHECK(0 == ScaleRoundUp(0, A, B));
  CHECK(0 == Scale(0, B, A));
  CHECK(0 == ScaleRoundUp(0, B, A));
  CHECK(0 == Scale(0, A, A));
  CHECK(0 == ScaleRoundUp(0, A, A));

  CHECK(0 == Scale(1, A, B));
  CHECK(1 == ScaleRoundUp(1, A, B));
  CHECK(333 == Scale(1, B, A));
  CHECK(334 == ScaleRoundUp(1, B, A));
  CHECK(1 == Scale(1, A, A));
  CHECK(1 == ScaleRoundUp(1, A, A));

  CHECK(0 == Scale(2, A, B));
  CHECK(1 == ScaleRoundUp(2, A, B));
  CHECK(666 == Scale(2, B, A));
  CHECK(667 == ScaleRoundUp(2, B, A));
  CHECK(2 == Scale(2, A, A));
  CHECK(2 == ScaleRoundUp(2, A, A));

  CHECK(0 == Scale(-1, A, B));
  CHECK(-1 == ScaleRoundUp(-1, A, B));
  CHECK(-333 == Scale(-1, B, A));
  CHECK(-334 == ScaleRoundUp(-1, B, A));
  CHECK(-1 == Scale(-1, A, A));
  CHECK(-1 == ScaleRoundUp(-1, A, A));

  CHECK(0 == Scale(-2, A, B));
  CHECK(-1 == ScaleRoundUp(-2, A, B));
  CHECK(-666 == Scale(-2, B, A));
  CHECK(-667 == ScaleRoundUp(-2, B, A));
  CHECK(-2 == Scale(-2, A, A));
  CHECK(-2 == ScaleRoundUp(-2, A, A));
}

TEST_CASE("Scaling doesn't overflow naively", "[base][base/integer]") {
  // 182 * 181 would overflow past std::numeric_limits<int16_t>::max()
  CHECK(4117 == Scale(static_cast<int16_t>(182), static_cast<int16_t>(181),
                      static_cast<int16_t>(8)));
  CHECK(-4117 == Scale(static_cast<int16_t>(-182), static_cast<int16_t>(181),
                       static_cast<int16_t>(8)));
  CHECK(4118 == ScaleRoundUp(static_cast<int16_t>(182),
                             static_cast<int16_t>(181),
                             static_cast<int16_t>(8)));
  CHECK(-4118 == ScaleRoundUp(static_cast<int16_t>(-182),
                              static_cast<int16_t>(181),
                              static_cast<int16_t>(8)));

  // 182 % 10000 * 300 overflows, but not if the ratio is simplified
  CHECK(5 == Scale<std::ratio<300, 10000>>(static_cast<int16_t>(182)));
  CHECK(6 == ScaleRoundUp<std::ratio<300, 10000>>(static_cast<int16_t>(182)));
}

TEST_CASE("Take negative absolute value", "[base][base/integer]") {
  CHECK(0 == Nabs(0));
  CHECK(-1 == Nabs(1));
  CHECK(-2 == Nabs(2));
  CHECK(-3 == Nabs(3));
  CHECK(-1 == Nabs(-1));
  CHECK(-2 == Nabs(-2));
  CHECK(-3 == Nabs(-3));
  CHECK(std::numeric_limits<int>::min() ==
        Nabs(std::numeric_limits<int>::min()));
  CHECK(std::numeric_limits<int>::min() + 1 ==
        Nabs(std::numeric_limits<int>::max()));
}

TEST_CASE("Average(a, b) = Average(b, a)", "[base][base/integer]") {
  CHECK(4 == Average(2, 7));
  CHECK(4 == Average(7, 2));
  CHECK(-4 == Average(-2, -7));
  CHECK(-4 == Average(-7, -2));
}

TEST_CASE("Average(a + 1, b + 1) = Average(a, b) + 1", "[base][base/integer]") {
  CHECK(3 == Average(2, 4));
  CHECK(4 == Average(3, 5));
  CHECK(-3 == Average(-2, -4));
  CHECK(-4 == Average(-3, -5));
}

TEST_CASE("Average(a, -b) = -Average(-a, b)", "[base][base/integer]") {
  CHECK(1 == Average(4, -1));
  CHECK(-1 == Average(-4, 1));
  CHECK(0 == Average(1, -2));
  CHECK(0 == Average(-1, 2));
  CHECK(1 == Average(0, 3));
  CHECK(-1 == Average(0, -3));
}

TEST_CASE("Average doesn't overflow for signed int", "[base][base/integer]") {
  // ...if a + b overflows.
  CHECK(0x5000'0001 == Average(0x5000'0000, 0x5000'0002));
  CHECK(-2'000'000'001 == Average(-2'000'000'000, -2'000'000'002));

  // ...if a - b overflows.
  CHECK(-1 == Average(2'000'000'000, -2'000'000'002));

  // ...if b - a overflows.
  CHECK(1 == Average(-2'000'000'000, 2'000'000'002));
}

TEST_CASE("Average works with unsigned int", "[base][base/integer]") {
  // ...if a + b overflows.
  CHECK(0x9000'0001U == Average(0x9000'0000U, 0x9000'0002U));

  // ...if a > b.
  CHECK(0x9000'0001U == Average(0x9000'0002U, 0x9000'0000U));
}

}  // namespace
}  // namespace Fructose
