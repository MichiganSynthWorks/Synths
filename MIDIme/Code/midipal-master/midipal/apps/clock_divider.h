// Copyright 2011 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
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
// Clock divider app.

#ifndef MIDIPAL_APPS_CLOCK_DIVIDER_H_
#define MIDIPAL_APPS_CLOCK_DIVIDER_H_

#include "midipal/app.h"

namespace midipal { namespace apps {

class ClockDivider {
 public:
  ClockDivider() { }

  static void OnInit();
  static void OnRawByte(uint8_t byte);
  
  static const prog_AppInfo app_info_;
  
 private:
  static uint8_t divider_;
  static uint8_t start_delay_;
  
  static uint8_t counter_;
  static uint8_t start_delay_counter_;
  static bool running_;
  
  DISALLOW_COPY_AND_ASSIGN(ClockDivider);
};

} }  // namespace midipal::apps

#endif // MIDIPAL_APPS_CLOCK_DIVIDER_H_
