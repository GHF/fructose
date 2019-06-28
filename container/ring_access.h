// (C) Copyright 2019 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstddef>
#include <optional>

#include "base/assert.h"

namespace Fructose {

template <size_t Period>
class RingAccess final {
 public:
  class WriteCursor final {
   public:
    size_t offset() const {
      if (offset_ >= kPeriod) {
        return offset_ - kPeriod;
      }
      return offset_;
    }

   private:
    constexpr explicit WriteCursor(size_t offset) : offset_(offset) {}

    size_t offset_;

    friend class RingAccess;
  };

  static constexpr size_t kPeriod = Period;

  [[nodiscard]] std::optional<size_t> Peek() const {
    if (read_offset_ == commit_offset_) {
      return std::nullopt;
    }
    if (read_offset_ >= kPeriod) {
      return read_offset_ - kPeriod;
    }
    return read_offset_;
  }

  void Pop() {
    FRU_DEBUG_ASSERT(Peek());
    read_offset_ = Clamp(read_offset_ + 1);
  }

  [[nodiscard]] std::optional<WriteCursor> Allocate() {
    if (Subtract(allocate_offset_, read_offset_) == kPeriod) {
      return std::nullopt;
    }
    const auto allocated = allocate_offset_;
    allocate_offset_ = Clamp(allocate_offset_ + 1);
    FRU_DEBUG_ASSERT(Subtract(allocate_offset_, commit_offset_) <= kPeriod);
    return WriteCursor{allocated};
  }

  void Commit(WriteCursor write_cursor) {
    // TODO(xo): Use the most advance write cursor.
    commit_offset_ = Clamp(write_cursor.offset_ + 1);
  }

 private:
  static size_t Clamp(size_t offset) {
    FRU_DEBUG_ASSERT(offset < kPeriod * 3);
    if (offset >= kPeriod * 2) {
      return offset - kPeriod * 2;
    }
    return offset;
  }

  static size_t Subtract(size_t ahead, size_t behind) {
    if (ahead < behind) {
      ahead += kPeriod * 2;
    }
    FRU_DEBUG_ASSERT(ahead - behind <= kPeriod);
    return ahead - behind;
  }

  size_t read_offset_ = 0;
  size_t allocate_offset_ = 0;
  size_t commit_offset_ = 0;

  static_assert(kPeriod < (SIZE_MAX / 2 + 1), "Ring access would overflow");
};

}  // namespace Fructose
