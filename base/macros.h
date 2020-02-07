// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

// Suppresses unused variable warnings without evaluating |expression|.
#define FRU_USED(expression) (void(true ? false : (expression)))

#ifdef __GNUC__
#define FRU_PRINTF(format_index, first_arg) \
  __attribute__((__format__(printf, format_index, first_arg)))
#else
#define FRU_PRINTF(format_index, first_arg)
#endif
