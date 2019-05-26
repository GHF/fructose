// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <array>
#include <numeric>
#include <type_traits>

#include "base/integer.h"

namespace Fructose {

// Maps one range of integer values linearly to another, with deadband.
template <typename InT, typename OutT>
class RangeMap final {
 public:
  // Construct a mapping for an input range spanning from |in_min| to |in_max|
  // into an output range spanning from |out_a| to |out_b| (both ranges are
  // inclusive).
  //
  // The input range must span strictly more than twice |deadband| and the
  // limits must be correctly ordered. |deadband| must be non-negative.
  //
  // The output range limits may be decreasing in order. Regardless, |in_min|
  // will map to |out_a| and |in_max| will map to |out_b|.
  //
  // Care must be taken to choose ranges and integer types that scale without
  // overflow.
  constexpr RangeMap(InT in_min,
                     InT in_max,
                     InT deadband,
                     OutT out_a,
                     OutT out_b)
      : in_min_(in_min),
        in_max_(in_max),
        deadband_(deadband),
        in_midpoint_(Average(in_min_, in_max_)),
        out_range_(std::minmax(out_a, out_b)),
        out_midpoint_(Average(out_a, out_b)),
        in_to_out_ratio_(
            ComputeRatio(in_min_, in_max_, deadband_, out_a, out_b)) {
    // TODO(GHF/fructose#2): Assert that in_min_ < in_max_.
    // TODO(GHF/fructose#2): Assert that deadband >= 0.
    // TODO(GHF/fructose#2): Assert that ratio[0] * ratio[1] does not overflow.
  }

  // Linearly map |value| from the input range to output range. Values that are
  // within |deadband| distance to the midpoint of the input range will be
  // mapped to the midpoint of the output range. If |value| is outside of the
  // input range, it will be clamped to the nearest input range limit.
  [[nodiscard]] constexpr OutT Map(InT value) const {
    // Center the input range on zero.
    InT centered_input = Clamp(value, in_min_, in_max_) - in_midpoint_;

    // Cut away the deadband from the centered input.
    if (Nabs(centered_input) > -deadband_) {
      centered_input = 0;
    } else {
      centered_input -= SignOf(centered_input) * deadband_;
    }

    // Scale by output to input ratio, then shift from zero into range.
    // WARNING: this computation can easily overflow!
    const OutT centered_output =
        ScaleRoundUp(centered_input, in_to_out_ratio_[0], in_to_out_ratio_[1]);
    const OutT out_value = centered_output + out_midpoint_;

    // Clamp output within range.
    return Clamp(out_value, out_range_.first, out_range_.second);
  }

 private:
  // Type used for computation.
  using T = std::common_type_t<InT, OutT>;
  static_assert(std::is_integral_v<T> && std::is_signed_v<T>,
                "Only valid for signed integers.");

  static constexpr std::array<T, 2> ComputeRatio(InT in_min,
                                                 InT in_max,
                                                 InT deadband,
                                                 OutT out_a,
                                                 OutT out_b) {
    // TODO(GHF/fructose#2): Assert that this is positive.
    const InT in_width = in_max - in_min - 2 * deadband;
    const OutT out_width = out_b - out_a;
    const T gcd = std::gcd(in_width, out_width);
    return {out_width / gcd, in_width / gcd};
  }

  const InT in_min_;
  const InT in_max_;
  const InT deadband_;

  const InT in_midpoint_;
  const std::pair<OutT, OutT> out_range_;  // Sorted output limits.
  const OutT out_midpoint_;
  const std::array<T, 2> in_to_out_ratio_;
};

}  // namespace Fructose
