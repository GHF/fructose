// Macros for specifying compiler directives.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: <LICENSE>

#pragma once

// Compiler-specific macros.
#ifdef __GNUC__
#define FORMAT(archetype, format_index, first_arg) \
    __attribute__((__format__(archetype, format_index, first_arg)))
#define USED __attribute__((used))
#define UNREACHABLE() __builtin_unreachable()
#else
#define FORMAT(archetype, format_index, first_arg)
#define USED
#define UNREACHABLE() do { } while (0)
#endif
