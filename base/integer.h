// Various integer arithmetic utility functions.
//
// (C) Copyright 2014 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <algorithm>
#include <type_traits>

namespace Fructose {
namespace internal {

// Recursively reduces rank of the array type until Rank = 0U, which returns
// the current dimension's bound, or the array type runs out of dimensions,
// causing the primary template's incomplete struct's instantiation failure.
template<typename ArrayT, unsigned Rank>
struct ArraySizeDeducer;
template<typename T, size_t N>
struct ArraySizeDeducer<T[N], 0U> : std::integral_constant<size_t, N> {};
template<typename T, size_t N, unsigned Rank>
struct ArraySizeDeducer<T[N], Rank> : ArraySizeDeducer<T, Rank - 1> {};

}  // namespace internal

// Gets the number of elements in any array that has a defined size. Unlike
// sizeof(array) / sizeof(array[0]), this will fail to compile if used with a
// pointer rather than an array. Unlike std::extent<decltype(array)>(), this
// will fail to compile rather than return 0 for arrays of unknown bound. For
// multi-dimensional arrays, this returns the first (leftmost) dimension.
template<typename T, size_t N>
constexpr size_t ArraySize(const T (&)[N]) {
  return N;
}

// Given a Rank template parameter, return the array type's Rankth (from the
// left) dimension bound.
template<unsigned Rank, typename T, size_t N>
constexpr size_t ArraySize(const T (&)[N]) {
  return ::Fructose::internal::ArraySizeDeducer<T[N], Rank>();
}

// Gets the sign of a value as +1, -1, or 0 (if input is zero).
template<typename T>
constexpr T SignOf(T i) {
  static_assert(std::is_integral<T>(), "SignOf is valid only for integers.");
  return (i > 0) - (i < 0);
}

// Division that rounds the quotient away from zero.
template<typename N, typename D>
constexpr auto DivideRoundUp(N numerator, D denominator) {
  static_assert(std::is_integral_v<N> && std::is_integral_v<D>,
                "Function is valid only for integers");
  static_assert(std::is_signed_v<N> == std::is_signed_v<D>,
                "Numerator and denominator signedness don't match");

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

// Multiply a value against a ratio while maintaining precision and avoiding
// unnecessary overflow. It's still possible for intermediate values of
// remainder * numerator to overflow if numerator is greater than the sqrt of
// the arithmetic type's range. Simplifying the fraction numerator /
// denominator gives the best results.
template<typename T, typename N, typename D>
constexpr std::common_type_t<T, N, D> Scale(T x, N numerator, D denominator) {
  static_assert(std::is_integral_v<T> && std::is_integral_v<N> &&
                std::is_integral_v<D>, "Function is valid only for integers");
  static_assert(std::is_signed_v<T> == std::is_signed_v<D> &&
                std::is_signed_v<T> == std::is_signed_v<D>,
                "Arguments' signedness don't match");

  if ((numerator >= denominator) && (numerator % denominator == 0U)) {
    return x * (numerator / denominator);
  }
  const auto quotient = x / denominator;
  const auto remainder = x % denominator;
  return quotient * numerator + remainder * numerator / denominator;
}

// Same as Scale, but round results up to the next denominator boundary.
template<typename T, typename N, typename D>
constexpr std::common_type_t<T, N, D> ScaleRoundUp(T x, N numerator,
                                                   D denominator) {
  static_assert(std::is_integral_v<T> && std::is_integral_v<N> &&
                std::is_integral_v<D>, "Function is valid only for integers");
  static_assert(std::is_signed_v<T> == std::is_signed_v<D> &&
                std::is_signed_v<T> == std::is_signed_v<D>,
                "Arguments' signedness don't match");

  if ((numerator >= denominator) && (numerator % denominator == 0U)) {
    return x * (numerator / denominator);
  }
  const auto quotient = x / denominator;
  const auto remainder = x % denominator;
  return quotient * numerator +
         DivideRoundUp(remainder * numerator, denominator);
}

// Takes the negation of the absolute value of an integer. Unlike abs, this is
// defined for all input values, including INT_MIN. See C99 standard
// 7.20.6.1.2 and footnote 265 for the description of abs/labs/llabs behavior
// with INT_MIN.
template<typename T>
constexpr T Nabs(T i) {
  static_assert(std::is_integral<T>() && std::is_signed<T>(),
                "Nabs is valid only for signed integers.");
  // Check if signed right shift sign extends (i.e. arithmetic right shift).
  if ((static_cast<T>(-1) >> 1) == static_cast<T>(-1)) {
    constexpr int num_bits = sizeof(T) * 8;
    // Splat sign bit into all 32 bits and complement.
    const T inverse_sign = ~(i >> (num_bits - 1));
    // If i is positive (inverse_sign = -1), this will invert i and add 1.
    // Otherwise (inverse_sign = 0) will be unchanged.
    return (i ^ inverse_sign) - inverse_sign;
  } else {
    return i < 0 ? i : -i;
  }
}

// Averages two signed integers in an overflow-safe way. The naive average
// function is erroneous when the sum of the inputs overflows integer limits;
// this average works by summing the halves of the input values and then
// rounding the sum towards zero.
template<typename T>
constexpr T Average(T a, T b) {
  static_assert(std::is_integral<T>(), "Average is valid only for integers.");
  static_assert(std::is_unsigned<T>() || (std::is_signed<T>() &&
                    ((static_cast<T>(-1) >> 1) == static_cast<T>(-1))),
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

// Clamps a value to a range. The lower bound must be less than or equal to
// the uppper bound.
template<typename T>
constexpr T Clamp(T i, T min, T max) {
  const T lower_bounded = std::max(i, min);
  const T both_bounded = std::min(lower_bounded, max);
  return both_bounded;
}

// Maps one range of values linearly to another, with deadband.
//
// Note that the product of the input range width (minus deadband) and the
// output range width must fit within the integer type chosen for computation.
//
// Arguments
// - in_low: Input range lower bound. value can not be less than this.
// - in_high: Input range upper bound. value can not exceed this. Must be
//            greater than in_low by twice deadband.
// - value: Input value to map.
// - out_low: Output range lower bound.
// - out_high: Output range upper bound. Must be greater than out_low.
// - deadband Distance from center of input range for which all input values
//            are mapped to "zero" (center of the output range).
template<typename T>
constexpr T MapRange(T in_low, T in_high, T value, T out_low, T out_high,
                     T deadband) {
  static_assert(std::is_integral<T>() && std::is_signed<T>(),
                "MapRange is valid only for signed integers.");
  // Center the input range on zero.
  const T in_center = Average(in_low, in_high);
  T centered_input = Clamp(value, in_low, in_high) - in_center;

  // Cut away the deadband from the centered input.
  if (Nabs(centered_input) > -deadband) {
    centered_input = 0;
  } else {
    centered_input -= SignOf(centered_input) * deadband;
  }

  // Compute the length of input and output ranges.
  const T in_scale = in_high - in_low - 2 * deadband;
  const T out_scale = out_high - out_low;
  const T out_center = Average(out_low, out_high);

  // Scale by output to input ratio, then shift from zero into range.
  // WARNING: this computation can easily overflow!
  const T out_value = Scale(centered_input, out_scale, in_scale) + out_center;

  // Clamp output within range.
  return Clamp(out_value, out_low, out_high);
}

}  // namespace Fructose
