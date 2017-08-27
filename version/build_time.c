// String that includes the build time for this file.
// This file is likely most useful when given as an input to the linker (i.e.,
// not incrementally compiled into an object file), so that this variable is
// updated whenever a program link occurs.
//
// (C) Copyright 2014-2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#ifdef __cplusplus
extern "C"
#endif  // __cplusplus
const char * const g_build_time = __DATE__ " " __TIME__;
