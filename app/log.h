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

#ifndef BASE_LOG_H_
#define BASE_LOG_H_

#define STATIC_LOGGING_LEVEL LOGGING_DEBUG
#define LOGGING_FILE stdout
#define LOGGING_USE_CHPRINTF 0

#include "base/compiler.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Levels of logged information. */
typedef enum LoggingLevel {
  LOGGING_DEBUG,        /* Detailed information useful for debugging. */
  LOGGING_INFO,         /* Confirmation of correct system operation. */
  LOGGING_WARNING,      /* Unexpected problems that do not affect operation. */
  LOGGING_ERROR,        /* Serious problem that interrupted an operation. */
  LOGGING_CRITICAL,     /* System operation is no longer possible. */
  LOGGING_NUM_LEVELS,
  LOGGING_DEFAULT_LEVEL = LOGGING_WARNING
} LoggingLevel;

/* Public operations to log information at various levels. */
#define LogDebug(...)     Log(LOGGING_DEBUG, __VA_ARGS__)
#define LogInfo(...)      Log(LOGGING_INFO, __VA_ARGS__)
#define LogWarning(...)   Log(LOGGING_WARNING, __VA_ARGS__)
#define LogError(...)     Log(LOGGING_ERROR, __VA_ARGS__)
#define LogCritical(...)  Log(LOGGING_CRITICAL, __VA_ARGS__)

/* Helper to optimize out Log* calls with an early level check. */
#define Log(level, ...)  do {        \
  if ((level) >= GetLoggingLevel())          \
    LogAtLevel(level, __func__, __VA_ARGS__);  \
} while (0)

#ifdef STATIC_LOGGING_LEVEL
/*
 * #define STATIC_LOGGING_LEVEL as one of the above levels to set a logging
 * level which does not change at runtime.
 */
static inline LoggingLevel GetLoggingLevel(void) {
  return STATIC_LOGGING_LEVEL;
}

#define SetLoggingLevel(level) \
    static_assert(0, "SetLoggingLevel invoked under STATIC_LOGGING_LEVEL")
#else
/* Dynamic logging level functions to peek and poke the logging level. */
LoggingLevel GetLoggingLevel(void);
void SetLoggingLevel(LoggingLevel level);
#endif  /* STATIC_LOGGING_LEVEL */

/**
 * @brief Identical to @c LogAtLevel except taking a va_list instead of variadic
 *        arguments.
 */
void vLogAtLevel(LoggingLevel level, const char *, const char *, va_list);

/**
 * @brief Logs a message at some level with appropriate formatting.
 *
 * @param level See @c LoggingLevel for the different levels of messages.
 * @param func Name of function to print before the message.
 * @param format Message to print out as a printf-style format string.
 * @param ... Arguments for @p format.
 */
void LogAtLevel(LoggingLevel level, const char *, const char *, ...)
    FORMAT(__printf__, 3, 4);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif  /* BASE_LOG_H_ */
