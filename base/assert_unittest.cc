// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "base/assert.h"

#include <optional>
#include <string>

#include "catch2/catch.hpp"

namespace Fructose {
namespace {

using namespace Catch::Matchers;

TEST_CASE("Can construct AssertData", "[base][base/assert]") {
  internal::AssertData data = {"1 == 1", "corn.cc", 51};
  CHECK(7UL == sizeof(data.condition));
  CHECK(8UL == sizeof(data.file_name));
  CHECK(51 == data.line_number);
}

TEST_CASE("Can construct AssertData with FRU_ASSERT_DATA",
          "[base][base/assert]") {
  const int kLineNumber = __LINE__ + 1;
  auto data = FRU_ASSERT_DATA("1 == 1");
  CHECK_THAT(data.condition, Equals("1 == 1"));
  CHECK_THAT(data.file_name, Equals("../../base/assert_unittest.cc"));
  CHECK(kLineNumber == data.line_number);
}

TEST_CASE("Assert on true condition does nothing", "[base][base/assert]") {
  FRU_ASSERT(1 == 1);
  FRU_DEBUG_ASSERT(1 == 1);
  FRU_ASSERT_MSG(1 == 1, "Equality isn't reflexive.");
  FRU_DEBUG_ASSERT_MSG(1 == 1, "Equality isn't reflexive.");
  FRU_ASSERT_MSG(1 == 1, "Equality isn't %s.", "reflexive");
  FRU_DEBUG_ASSERT_MSG(1 == 1, "Equality isn't %s.", "reflexive");
}

class AssertFixture {
 protected:
  AssertFixture() { Reset(); }

  template <typename AssertDataType,
            unsigned long MessageSize,
            typename... Args>
  static bool Handler(AssertDataType assert_data,
                      const char (&message)[MessageSize],
                      Args&&... args) {
    handler_calls_++;
    condition_ = assert_data.condition;
    message_ = message;
    args_count_ = sizeof...(args);

    return false;
  }

  static void Reset() {
    handler_calls_ = 0;
    condition_ = std::nullopt;
    message_ = std::nullopt;
    args_count_ = 0U;
  }

  static const auto& handler_calls() { return handler_calls_; }
  static const auto& condition() { return condition_; }
  static const auto& message() { return message_; }
  static const auto& args_count() { return args_count_; }

 private:
  inline static int handler_calls_ = 0;
  inline static std::optional<std::string> condition_;
  inline static std::optional<std::string> message_;
  inline static size_t args_count_ = 0U;
};

#undef FRU_ASSERT_FAILURE_HANDLER
#define FRU_ASSERT_FAILURE_HANDLER(assert_data, ...) \
  AssertFixture::Handler(assert_data, __VA_ARGS__)

TEST_CASE_METHOD(AssertFixture,
                 "Use custom assert handler",
                 "[base][base/assert]") {
  SECTION("Assert failure calls handler") {
    FRU_ASSERT(1 == 2);
    CHECK(1 == handler_calls());
    REQUIRE(condition().has_value());
    CHECK_THAT(*condition(), Equals("1 == 2"));
#ifndef NDEBUG
    FRU_DEBUG_ASSERT(1 == 2);
    CHECK(2 == handler_calls());
#endif  // NDEBUG
  }

  SECTION("Assert failure with message calls handler with message") {
    FRU_ASSERT_MSG(1 == 2, "This computer can compare %d to %d.", 1, 2);
    CHECK(1 == handler_calls());
    REQUIRE(message().has_value());
    CHECK_THAT(*message(), Equals("This computer can compare %d to %d."));
    CHECK(2U == args_count());
#ifndef NDEBUG
    FRU_DEBUG_ASSERT_MSG(1 == 2, "Foo");
    CHECK(2 == handler_calls());
#endif  // NDEBUG
  }
}

}  // namespace
}  // namespace Fructose
