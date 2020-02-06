/*
 * Copyright (C) 2014 Xo Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name(s) of the above copyright
 * holders shall not be used in advertising or otherwise to promote the sale,
 * use or other dealings in this Software without prior written authorization.
 */

#include "log.h"

#include <stdarg.h>

#include "base/compiler.h"

#if LOGGING_USE_CHPRINTF
#include "ch.h"
#include "chprintf.h"
#include "hal.h"

/* Default file descriptor to log to. */
#ifndef LOGGING_FILE
#define LOGGING_FILE ((BaseSequentialStream*)&DEBUG_SERIAL)
#endif
#define LOG_FPRINTF(file, ...) chprintf(file, __VA_ARGS__)
#define LOG_VFPRINTF(file, format, va_list) chvprintf(file, format, va_list)
#else
#include <stdio.h>

/* Default file descriptor to log to. */
#ifndef LOGGING_FILE
#define LOGGING_FILE stderr
#endif
#define LOG_FPRINTF(file, ...) fprintf(file, __VA_ARGS__)
#define LOG_VFPRINTF(file, format, va_list) vfprintf(file, format, va_list)
#endif /* #if LOGGING_USE_CHPRINTF */

#ifndef STATIC_LOGGING_LEVEL
static LoggingLevel g_logging_level = LOGGING_DEFAULT_LEVEL;

LoggingLevel GetLoggingLevel(void) {
  return g_logging_level;
}

void SetLoggingLevel(LoggingLevel level) {
  if (level > LOGGING_NUM_LEVELS)
    g_logging_level = LOGGING_NUM_LEVELS;
  else
    g_logging_level = level;
}
#endif /* STATIC_LOGGING_LEVEL */

/* ANSI color codes. */
#define ANSI_RESET "\x1b[0m"
#define ANSI_BOLD "\x1b[1m"
#define ANSI_UNDERLINE "\x1b[4m"
#define ANSI_REVERSE "\x1b[7m"
#define ANSI_BOLD_OFF "\x1b[22m"
#define ANSI_UNDERLINE_OFF "\x1b[24m"
#define ANSI_REVERSE_OFF "\x1b[27m"
#define ANSI_COLOR_BLACK "\x1b[30m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_WHITE "\x1b[37m"
#define ANSI_COLOR_OFF "\x1b[39m"
#define ANSI_BGCOL_BLACK "\x1b[40m"
#define ANSI_BGCOL_RED "\x1b[41m"
#define ANSI_BGCOL_GREEN "\x1b[42m"
#define ANSI_BGCOL_YELLOW "\x1b[43m"
#define ANSI_BGCOL_BLUE "\x1b[44m"
#define ANSI_BGCOL_MAGENTA "\x1b[45m"
#define ANSI_BGCOL_CYAN "\x1b[46m"
#define ANSI_BGCOL_WHITE "\x1b[47m"
#define ANSI_BGCOL_OFF "\x1b[49m"

void vLogAtLevel(LoggingLevel level,
                 const char* func,
                 const char* format,
                 va_list args) {
  const char* const level_prefixes[] = {"",
                                        ANSI_BOLD,
                                        ANSI_BOLD ANSI_COLOR_YELLOW,
                                        ANSI_BOLD ANSI_COLOR_RED,
                                        ANSI_BOLD ANSI_BGCOL_RED,
                                        ANSI_REVERSE};

  const char* const level_names[] = {"DEBUG", "INFO",     "WARNING",
                                     "ERROR", "CRITICAL", "INVALID_LEVEL"};

  const char* const level_suffixes[] = {"",
                                        ANSI_BOLD_OFF,
                                        ANSI_COLOR_OFF ANSI_BOLD_OFF,
                                        ANSI_COLOR_OFF ANSI_BOLD_OFF,
                                        ANSI_BGCOL_OFF ANSI_BOLD_OFF,
                                        ANSI_REVERSE_OFF};

  if (level < GetLoggingLevel())
    return;

  if (level > LOGGING_NUM_LEVELS)
    level = LOGGING_NUM_LEVELS;

  LOG_FPRINTF(LOGGING_FILE, "%s%s%s:%s:", level_prefixes[level],
              level_names[level], level_suffixes[level], func);

  LOG_VFPRINTF(LOGGING_FILE, format, args);
  LOG_FPRINTF(LOGGING_FILE, "\r\n");
}

void LogAtLevel(LoggingLevel level, const char* func, const char* format, ...) {
  va_list args;
  va_start(args, format);
  vLogAtLevel(level, func, format, args);
  va_end(args);
}
