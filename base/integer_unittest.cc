// Various integer arithmetic utility functions.
//
// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "base/integer.h"

#include "catch2/catch.hpp"

TEST_CASE("Array sizes can be deduced", "[base][base/integer]") {
  int A[2];
  REQUIRE(2 == Fructose::ArraySize(A));
  REQUIRE(2 == Fructose::ArraySize<0>(A));
  REQUIRE(sizeof(A) / sizeof(A[0]) == Fructose::ArraySize(A));
}
