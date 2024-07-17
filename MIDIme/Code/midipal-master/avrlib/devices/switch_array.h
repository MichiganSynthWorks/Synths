// Copyright 2009 Emilie Gillet.
//
// Author: Peter Kvitek (pete@kvitek.com)
//
// Based on DebouncedSwitches code by Emilie Gillet (emilie.o.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Debouncing for:
// - An array of switches connected to a parallel port.

#ifndef AVRLIB_DEVICES_SWITCH_ARRAY_H_
#define AVRLIB_DEVICES_SWITCH_ARRAY_H_

#include <string.h>

#include "avrlib/parallel_io.h"
#include "avrlib/size_to_type.h"

namespace avrlib {

template<uint8_t num_inputs, typename Port, ParallelPortMode parallel_mode, bool enable_pull_up = true>
class SwitchArray {
  typedef typename DataTypeForSize<num_inputs>::Type T;
  typedef ParallelPort<Port, parallel_mode> Register;

 public:
  SwitchArray() { }

  enum { NumInputs = num_inputs };

  static inline void Init() {
    memset(state_, 0xff, sizeof(state_));
    Register::set_mode(DIGITAL_INPUT);
    if (enable_pull_up) {
      Register::EnablePullUpResistors();
    }
  }

  static inline T ReadRegister() {
    return Register::Read();
  }

  static inline void Process(T value) {
    T mask = 1;
    for (uint8_t i = 0; i < num_inputs; ++i) {
      state_[i] <<= 1;
      if (value & mask) {
         state_[i] |= 1;
      }
      mask <<= 1;
    }
  }

  static inline void Read() {
    Process(ReadRegister());
  }

  static inline uint8_t lowered(uint8_t index) { return state_[index] == 0x80; }
  static inline uint8_t raised(uint8_t index) { return state_[index] == 0x7f; }
  static inline uint8_t high(uint8_t index) { return state_[index] == 0xff; }
  static inline uint8_t low(uint8_t index) { return state_[index] == 0x00; }
  static inline uint8_t state(uint8_t index) { return state_[index]; }
  static inline int8_t event(uint8_t index) {
    if (lowered(index)) {
      return -1;
    } else if (raised(index)) {
      return 1;
    }
    return 0;
  }

 private:
  static uint8_t state_[num_inputs];

  DISALLOW_COPY_AND_ASSIGN(SwitchArray);
};

template<uint8_t num_inputs, typename Port, ParallelPortMode parallel_mode, bool enable_pull_up>
uint8_t SwitchArray<num_inputs, Port, parallel_mode, enable_pull_up>::state_[num_inputs];

}  // namespace avrlib

#endif   // AVRLIB_DEVICES_SWITCH_ARRAY_H_
