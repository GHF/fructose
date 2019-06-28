// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "ring_access.h"

#include "catch2/catch.hpp"

namespace Fructose {
namespace {

TEST_CASE("Circular buffer access primitive", "[container][container/ring_access]") {
  RingAccess<4> state;

  SECTION("ring state starts off empty") {
    CHECK(!state.Peek());
  }
  SECTION("write one element at the beginning") {
    auto cursor = state.Allocate();
    REQUIRE(cursor);
    CHECK(cursor->offset() == 0);
    SECTION("allocated element isn't visible to the reader") {
      CHECK(!state.Peek());
    }
    state.Commit(*cursor);
    SECTION("committing the allocated element makes it readable") {
      auto next = state.Peek();
      REQUIRE(next);
      CHECK(*next == 0);
    }
    state.Pop();
    SECTION("ring is empty again") {
      CHECK(!state.Peek());
    }
  }
  SECTION("fill up ring") {
    for (int i = 0; i < 4; i++) {
      auto cursor = state.Allocate();
      REQUIRE(cursor);
      CHECK(cursor->offset() == i);
      state.Commit(*cursor);
      CHECK(state.Peek());
    }
    SECTION("can't allocate when ring is full") {
      // Even if the writer already committed.
      CHECK(!state.Allocate());
    }
    state.Pop();
    SECTION("reading from the ring progresses sequentially") {
      for (int i = 0; i < 3; i++) {
        auto next = state.Peek();
        REQUIRE(next);
        CHECK(*next == i + 1);
        state.Pop();
      }
    }
    SECTION("ring should allow one more write") {
      auto cursor = state.Allocate();
      REQUIRE(cursor);
      CHECK(cursor->offset() == 0);
      // Even if the writer hasn't committed.
      CHECK(!state.Allocate());
      for (int i = 0; i < 3; i++) {
        state.Pop();
      }
      CHECK(!state.Peek());
      state.Commit(*cursor);
      REQUIRE(state.Peek());
      CHECK(*state.Peek() == 0);
    }
  }
}

}  // namespace
}  // namespace Fructose
