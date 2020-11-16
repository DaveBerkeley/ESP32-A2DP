/*
  Streaming Music from Bluetooth
  
  Copyright (C) 2020 Phil Schatzmann
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <panglos/debug.h>

#include "BluetoothA2DPSink.h"

#include "io.h"

   /*
    *
    */

namespace panglos {

    void * get_task_id()
    {
        return 0;
    }

    timer_t timer_now()
    {
        return 0;
    }
}

extern "C" void Error_Handler(void)
{
    Serial.print("DEAD!\r\n");
    while (true)
        ;
}

class Output : public panglos::Output
{
    virtual int _putc(char c) {
        Serial.print(c);
        return 1;
    }
};

Output out;

panglos::Output *err_uart = & out;

   /*
    *
    */

BluetoothA2DPSink a2dp_sink;

static char bt_name[] = "xNAD-3020";

void setup() {
    a2dp_sink.start(bt_name);  
    io_init(& a2dp_sink);

    Serial.begin(115200);
}


void loop() {
}


