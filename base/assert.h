// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "macros.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-zero-length"

// Check a boolean expression |condition| and if it's false, invoke a handler
// FRU_ASSERT_FAILURE_HANDLER. A default handler is provided that prints the
// assertion data then calls std::abort().
#define FRU_ASSERT_MSG(condition, ...) \
  (!(condition) && FRU_HANDLE_ASSERT_FAILURE(condition, __VA_ARGS__))

// FRU_DEBUG_ASSERT_MSG works like FRU_ASSERT_MSG, but is disabled when the
// NDEBUG macro is defined.
#if !defined(NDEBUG)
#define FRU_DEBUG_ASSERT_MSG(condition, ...) \
  FRU_ASSERT_MSG(condition, __VA_ARGS__)
#else
#define FRU_DEBUG_ASSERT_MSG(condition, ...) \
  FRU_USED(condition&& FRU_ASSERT_MESSAGE_CHECKER(__VA_ARGS__))
#endif  // !defined(NDEBUG)

// Shorthand asserts when a message is not required.
#define FRU_ASSERT(condition) FRU_ASSERT_MSG(condition, "")
#define FRU_DEBUG_ASSERT(condition) FRU_DEBUG_ASSERT_MSG(condition, "")

// Implementation.

// Helper to construct AssertData at the current file and line. |condition|
// should be the stringified condition expression.
#define FRU_ASSERT_DATA(condition) \
  (::Fructose::internal::AssertData{condition, __FILE__, __LINE__})

// This is a macro instead of a symbol in order to preserve the string literal
// visibility of the formatting string (which allows compiler checking).
#define FRU_HANDLE_ASSERT_FAILURE(condition, ...)                          \
  (FRU_ASSERT_FAILURE_HANDLER(FRU_ASSERT_DATA(#condition), __VA_ARGS__) && \
   FRU_ASSERT_MESSAGE_CHECKER(__VA_ARGS__))

// Default handler for assertion failures that forwards the call to
// HandleAssertFailure.
//
// TODO(#6): When logging is available, log a fatal error here.
#if !defined(FRU_ASSERT_FAILURE_HANDLER)
#define FRU_ASSERT_FAILURE_HANDLER(assert_data, ...)                         \
  ::Fructose::internal::HandleAssertFailure(                                 \
      assert_data.condition, assert_data.file_name, assert_data.line_number, \
      __VA_ARGS__)
#endif  // !defined(FRU_ASSERT_FAILURE_HANDLER)

// Default handler for validating the additional arguments passed to the assert
// calls. This is never evaluated and must work through compile-time side
// effects like warnings and static_asserts.
#if !defined(FRU_ASSERT_MESSAGE_CHECKER)
#define FRU_ASSERT_MESSAGE_CHECKER(...) \
  ::Fructose::internal::CheckPrintfFormat(__VA_ARGS__)
#endif  // !defined(FRU_ASSERT_MESSAGE_CHECKER)

namespace Fructose {
namespace internal {

// Information about the site of an assertion.
template <unsigned long ConditionSize, unsigned long FileNameSize>
struct AssertData {
  const char (&condition)[ConditionSize];
  const char (&file_name)[FileNameSize];
  int line_number;
};

// Template deduction guide to capture the sizes of the strings literal
// (assertion expression and file name) as part of AssertData's type so that
// they're available at compile time.
template <typename ConditionType, typename FileNameType>
AssertData(const ConditionType& condition,
           const FileNameType& file_name,
           int line_number)
    ->AssertData<sizeof(condition), sizeof(file_name)>;

// Prints a message with the failing expression, source location. If |message|
// has more than one character, it and subsequent arguments will be formatted
// and written using std::fprintf to stderr.
[[noreturn]] bool HandleAssertFailure(const char* condition,
                                      const char* file_name,
                                      int line_number,
                                      const char* message,
                                      ...);

// Uses the compiler printf checker to analyze the arguments.
bool CheckPrintfFormat(const char* format, ...) FRU_PRINTF(1, 2);

inline bool CheckPrintfFormat(const char*, ...) {
  // This should never actually be called.
  return false;
}

}  // namespace internal
}  // namespace Fructose

#pragma GCC diagnostic pop
