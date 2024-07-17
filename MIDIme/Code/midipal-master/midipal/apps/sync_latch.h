// Copyright 2012 Emilie Gillet.
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
// Sync counter app.

#ifndef MIDIPAL_APPS_SYNC_LATCH_H_
#define MIDIPAL_APPS_SYNC_LATCH_H_

#include "midipal/app.h"

namespace midipal { namespace apps {

enum SyncState {
  STATE_RUNNING = 1,
  STATE_ARMED = 2
};

class SyncLatch {
 public:
  SyncLatch() { }

  static void OnInit();
  static void OnRawByte(uint8_t byte);

  static void OnStart();
  static void OnStop();
  static void OnClock(uint8_t clock_mode);

  static uint8_t OnClick();
  static uint8_t OnRedraw();
  
  static const prog_AppInfo app_info_;
  
 private:
  static uint8_t num_beats_;
  static uint8_t beat_division_;
  static uint8_t beat_counter_;
  static uint8_t step_counter_;
  static uint8_t state_;
  
  DISALLOW_COPY_AND_ASSIGN(SyncLatch);
};

} }  // namespace midipal::apps

#endif // MIDIPAL_APPS_SYNC_LATCH_H_
