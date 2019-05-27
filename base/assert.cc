// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#include "assert.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

namespace Fructose {
namespace internal {

bool HandleAssertFailure(const char* condition,
                         const char* file_name,
                         int line_number,
                         const char* message,
                         ...) {
  FILE* const kOutput = stderr;
  std::fprintf(kOutput, "ASSERT \"%s\" FAILED at %s:%d\n", condition, file_name,
               line_number);
  if (message[0] != '\0') {
    std::fputs("  with message \"", kOutput);
    va_list args;
    va_start(args, message);
    vfprintf(kOutput, message, args);
    va_end(args);
    std::fputs("\"\n", kOutput);
  }
  std::abort();
}

}  // namespace internal
}  // namespace Fructose
