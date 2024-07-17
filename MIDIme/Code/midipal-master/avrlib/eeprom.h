// Copyright 2020 Peter Kvitek.
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
// Templates to provide type independent function names for eeprom access.

#ifndef AVRLIB_EEPROM_H_
#define AVRLIB_EEPROM_H_

#include "avrlib/base.h"

#include <avr/eeprom.h>

namespace avrlib {

// Read value
template<typename T>
T eeprom_read_value(const T* p) {}

template<>
uint8_t eeprom_read_value(const uint8_t* p) {
  return eeprom_read_byte(p);
}

template<>
uint16_t eeprom_read_value(const uint16_t* p) {
  return eeprom_read_word(p);
}

template<>
uint32_t eeprom_read_value(const uint32_t* p) {
  return eeprom_read_dword(p);
}

template<>
float eeprom_read_value(const float* p) {
  return eeprom_read_float(p);
}

// Write value
template<typename T>
void eeprom_write_value(T* p, T value) {}

template<>
void eeprom_write_value(uint8_t* p, uint8_t value) {
  eeprom_write_byte(p, value);
}

template<>
void eeprom_write_value(uint16_t* p, uint16_t value) {
  eeprom_write_word(p, value);
}

template<>
void eeprom_write_value(uint32_t* p, uint32_t value) {
  eeprom_write_dword(p, value);
}

template<>
void eeprom_write_value(float* p, float value) {
  eeprom_write_float(p, value);
}

// Update  value
template<typename T>
void eeprom_update_value(T* p, T value) {}

template<>
void eeprom_update_value(uint8_t* p, uint8_t value) {
  eeprom_update_byte(p, value);
}

template<>
void eeprom_update_value(uint16_t* p, uint16_t value) {
  eeprom_update_word(p, value);
}

template<>
void eeprom_update_value(uint32_t* p, uint32_t value) {
  eeprom_update_dword(p, value);
}

template<>
void eeprom_update_value(float* p, float value) {
  eeprom_update_float(p, value);
}

}  // namespace avrlib

#endif  // AVRLIB_EEPROM_H_
