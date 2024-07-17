// Copyright 2014 Peter Kvitek
//
// Author: Peter Kvitek (pete@kvitek.com)
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
// MCP3201 12 bit ADC abstraction. This device supports clock at 1.6Mhz max, so
// it's not worth using it with hardware SPI if there are faster devices using it.

#ifndef AVRLIB_DEVICES_MCP3201_H_
#define AVRLIB_DEVICES_MCP3201_H_

#include <avr/io.h>

#include "avrlib/gpio.h"

namespace avrlib {

template<typename CsPin, typename ClkPin, typename DataPin>
struct MCP3201 {

  static inline void Init() {
    CsPin::set_mode(DIGITAL_OUTPUT);
    CsPin::High();
    ClkPin::set_mode(DIGITAL_OUTPUT);
    ClkPin::Low();
    DataPin::set_mode(DIGITAL_INPUT);
    DataPin::High();
  }

  // Takes ~10us@20MHz, clock 1.4MHz
  static inline uint16_t Read() {
    uint8_t sreg = SREG; cli();

    CsPin::Low();
    nop();

    uint8_t byte1 = 0;
    uint8_t byte2 = 0;

#define BITBANG(byte, mask) \
    ClkPin::High(); nop(); \
    byte |= DataPin::value() ? mask : 0; \
    ClkPin::Low(); nop(); nop(); nop(); nop();

    BITBANG(byte1, 0x40); 
    BITBANG(byte1, 0x20);
    BITBANG(byte1, 0x10);

    BITBANG(byte1, 0x08);
    BITBANG(byte1, 0x04);
    BITBANG(byte1, 0x02);
    BITBANG(byte1, 0x01);

    BITBANG(byte2, 0x80);
    BITBANG(byte2, 0x40);
    BITBANG(byte2, 0x20);
    BITBANG(byte2, 0x10);

    BITBANG(byte2, 0x08);
    BITBANG(byte2, 0x04);
    BITBANG(byte2, 0x02);
    BITBANG(byte2, 0x01);

    CsPin::High();

    SREG = sreg;

    return static_cast<uint16_t>(byte1 & 0xf) << 8 | static_cast<uint16_t>(byte2);
  }

  // 50ns @20MHz
  static inline void nop() { 
    __asm__ volatile (
      "nop"
      ); 
  }

};

}  // namespace avrlib

#endif   // AVRLIB_DEVICES_MCP3201_H_
