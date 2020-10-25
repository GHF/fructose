// Various integer arithmetic utility functions.
//
// (C) Copyright 2014 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <algorithm>
#include <limits>
#include <type_traits>

#include "assert.h"

namespace Fructose {
namespace internal {

// Recursively reduces rank of the array type until Rank = 0U, which returns
// the current dimension's bound, or the array type runs out of dimensions,
// causing the primary template's incomplete struct's instantiation failure.
template <typename ArrayT, unsigned Rank>
struct ArraySizeDeducer;
template <typename T, size_t N>
struct ArraySizeDeducer<T[N], 0U> : std::integral_constant<size_t, N> {};
template <typename T, size_t N, unsigned Rank>
struct ArraySizeDeducer<T[N], Rank> : ArraySizeDeducer<T, Rank - 1> {};

template <typename T>
constexpr std::enable_if_t<std::is_signed_v<T>, bool> has_arithmetic_shift_v =
    (static_cast<T>(-1) >> 1) == static_cast<T>(-1);

// Alias for intmax_t for signed integer types, uintmax_t for unsigned integer
// types, undefined otherwise.
template <typename T>
using max_int_t = std::enable_if_t<
    std::is_integral_v<T>,
    std::conditional_t<std::is_signed_v<T>, intmax_t, uintmax_t>>;

}  // namespace internal

// Gets the number of elements in any array that has a defined size. Unlike
// sizeof(array) / sizeof(array[0]), this will fail to compile if used with a
// pointer rather than an array. Unlike std::extent<decltype(array)>(), this
// will fail to compile rather than return 0 for arrays of unknown bound. For
// multi-dimensional arrays, this returns the first (leftmost) dimension.
template <typename T, size_t N>
constexpr size_t ArraySize(const T (&)[N]) {
  return N;
}

// Given a Rank template parameter, returns the array type's Rankth (from the
// left) dimension bound.
template <unsigned Rank, typename T, size_t N>
constexpr size_t ArraySize(const T (&)[N]) {
  return ::Fructose::internal::ArraySizeDeducer<T[N], Rank>();
}

// Gets the sign of a value as +1, -1, or 0 (if input is zero).
template <typename T>
constexpr T SignOf(T i) {
  static_assert(std::is_integral_v<T>, "Function is valid only for integers.");
  return (i > 0) - (i < 0);
}

// Returns true if |value| is representable using integer type |T|.
template <typename T>
constexpr bool InRange(::Fructose::internal::max_int_t<T> value) {
  return (value >= std::numeric_limits<T>::min()) &&
         (value <= std::numeric_limits<T>::max());
}

// Divides, rounding the quotient away from zero.
template <typename N, typename D>
constexpr auto DivideRoundUp(N numerator, D denominator) {
  static_assert(std::is_integral_v<N> && std::is_integral_v<D>,
                "Function is valid only for integers");
  static_assert(std::is_signed_v<N> == std::is_signed_v<D>,
                "Numerator and denominator signedness don't match");
  FRU_DEBUG_ASSERT(denominator != 0);

  using ResultT = decltype(std::declval<N>() / std::declval<D>());
  if (std::is_unsigned_v<N>) {
    if (numerator == 0) {
      return static_cast<ResultT>(0);
    }
    return static_cast<ResultT>(1) +
           ((numerator - static_cast<N>(1)) / denominator);
  }
  if (denominator < 0) {
    numerator = -numerator;
    denominator = -denominator;
  }
  return numerator / denominator + SignOf<ResultT>(numerator % denominator);
}

// Multiplies a value against a ratio while maintaining precision and avoiding
// unnecessary overflow. It's still possible for |x % denominator * numerator|
// to overflow.
template <typename T, typename N, typename D>
constexpr std::common_type_t<T, N, D> Scale(T x, N numerator, D denominator) {
  static_assert(
      std::is_integral_v<T> && std::is_integral_v<N> && std::is_integral_v<D>,
      "Function is valid only for integers");
  static_assert(std::is_signed_v<T> == std::is_signed_v<D> &&
                    std::is_signed_v<T> == std::is_signed_v<D>,
                "Arguments' signedness don't match");
  FRU_DEBUG_ASSERT(denominator != 0);
  using int_t = std::common_type_t<T, N, D>;
  using max_int_t = ::Fructose::internal::max_int_t<int_t>;
  FRU_DEBUG_ASSERT(InRange<int_t>(
      numerator * (static_cast<max_int_t>(denominator) - SignOf(denominator))));

  if ((numerator >= denominator) && (numerator % denominator == 0U)) {
    return x * (numerator / denominator);
  }
  const auto quotient = x / denominator;
  const auto remainder = x % denominator;
  return quotient * numerator + remainder * numerator / denominator;
}

// Scales a value against a std::ratio known at compile time.
template <class Ratio, typename T>
constexpr T Scale(T x) {
  static_assert(std::is_signed_v<T> || (Ratio::num >= 0),
                "Can't scale an unsigned value using a negative ratio");
  static_assert(InRange<T>(Ratio::num * (Ratio::den - SignOf(Ratio::den))),
                "Computing scaled value may overflow");
  return Scale(x, static_cast<T>(Ratio::num), static_cast<T>(Ratio::den));
}

// Same as Scale, but rounds results up to the next denominator boundary.
template <typename T, typename N, typename D>
constexpr std::common_type_t<T, N, D> ScaleRoundUp(T x,
                                                   N numerator,
                                                   D denominator) {
  static_assert(
      std::is_integral_v<T> && std::is_integral_v<N> && std::is_integral_v<D>,
      "Function is valid only for integers");
  static_assert(std::is_signed_v<T> == std::is_signed_v<D> &&
                    std::is_signed_v<T> == std::is_signed_v<D>,
                "Arguments' signedness don't match");
  FRU_DEBUG_ASSERT(denominator != 0);
  using int_t = std::common_type_t<T, N, D>;
  using max_int_t = ::Fructose::internal::max_int_t<int_t>;
  FRU_DEBUG_ASSERT(InRange<int_t>(
      numerator * (static_cast<max_int_t>(denominator) - SignOf(denominator))));

  if ((numerator >= denominator) && (numerator % denominator == 0U)) {
    return x * (numerator / denominator);
  }
  const auto quotient = x / denominator;
  const auto remainder = x % denominator;
  return quotient * numerator +
         DivideRoundUp(remainder * numerator, denominator);
}

template <class Ratio, typename T>
constexpr T ScaleRoundUp(T x) {
  static_assert(std::is_signed_v<T> || (Ratio::num >= 0),
                "Can't scale an unsigned value using a negative ratio");
  static_assert(InRange<T>(Ratio::num * (Ratio::den - SignOf(Ratio::den))),
                "Computing scaled value may overflow");
  return ScaleRoundUp(x, static_cast<T>(Ratio::num),
                      static_cast<T>(Ratio::den));
}

// Takes the negation of the absolute value of an integer. Unlike abs, this is
// defined for all input values, including INT_MIN. See C99 standard
// 7.20.6.1.2 and footnote 265 for the description of abs/labs/llabs behavior
// with INT_MIN.
template <typename T>
constexpr T Nabs(T i) {
  static_assert(std::is_integral_v<T> && std::is_signed_v<T>,
                "Function is valid only for signed integers.");
  // Check if signed right shift sign extends (i.e. arithmetic right shift).
  if constexpr (::Fructose::internal::has_arithmetic_shift_v<T>) {
    constexpr int num_bits = sizeof(T) * 8;
    // Splat sign bit into all bit positions.
    const T sign = i >> (num_bits - 1);
    // If i is positive (sign = 0), i is unchanged by xor and subtracted from 0.
    // Otherwise for a negative i (sign = -1), i is inverted and negated, which
    // increments it, so this is cancelled out by adding sign
    return sign - (i ^ sign);
  } else {
    return i <= 0 ? i : -i;
  }
}

// Averages two signed integers in an overflow-safe way. The naive average
// function is erroneous when the sum of the inputs overflows integer limits;
// this average works by summing the halves of the input values and then
// rounding the sum towards zero.
template <typename T>
constexpr T Average(T a, T b) {
  static_assert(std::is_integral_v<T>, "Function is valid only for integers.");
  if constexpr (std::is_signed_v<T>) {
    static_assert(::Fructose::internal::has_arithmetic_shift_v<T>,
                  "Arithmetic right shift is not available.");
    // Shifts divide by two, rounded towards negative infinity.
    const T sum_halves = (a >> 1) + (b >> 1);
    // This has error of magnitude one if both are odd.
    const T both_odd = (a & b) & 1;
    // Round toward zero; add one if one input is odd and sum is negative.
    const T round_to_zero = (sum_halves < 0) & (a ^ b);
    // Result is sum of halves corrected for rounding.
    return sum_halves + both_odd + round_to_zero;
  }

  // Use a more compiler-friendly form for unsigned integers, where the absolute
  // difference of a and b will always be in range.
  if (a > b) {
    std::swap(a, b);
  }
  return a + (b - a) / 2;
}

// Clamps a value to a range. The lower bound must be less than or equal to
// the uppper bound.
template <typename T>
constexpr T Clamp(T i, T min, T max) {
  FRU_DEBUG_ASSERT(min <= max);
  const T lower_bounded = std::max(i, min);
  const T both_bounded = std::min(lower_bounded, max);
  return both_bounded;
}

}  // namespace Fructose
