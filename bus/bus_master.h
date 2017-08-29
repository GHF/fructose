// Interface for system buses that (each) have a single master.
//
// (C) Copyright 2017 Xo Wang <xo@geekshavefeelings.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

namespace Fructose {

// A bus master that can be taken exclusive control of. As bus masters are
// one-to-one with buses, this implies mutual exclusion of the bus, too.
class BusMaster {
 public:
  virtual ~BusMaster() {
  }
  virtual void Acquire() = 0;
  virtual void Release() = 0;
};

// Bus that has no mutual exclusion in the OS. Stub implementations are
// provided for convenience.
class SharedBusMaster : public BusMaster {
  void Acquire() override {
  }
  void Release() override {
  }
};

// RAII manager for bus mutual exclusion. Construct to acquire the bus and
// destroy (usually by leaving scope) to release.
class BusGuard final {
 public:
  explicit BusGuard(BusMaster *bus_master)
      : bus_master_(bus_master) {
    bus_master_->Acquire();
  }
  ~BusGuard() {
    bus_master_->Release();
  }

 private:
  BusGuard(const BusGuard &) = delete;
  BusGuard &operator=(const BusGuard &) = delete;
  BusMaster * const bus_master_;
};

}  // namespace Fructose
