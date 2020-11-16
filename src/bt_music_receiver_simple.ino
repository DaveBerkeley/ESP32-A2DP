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
#include "BluetoothA2DPSink.h"

#include <panglos/debug.h>
#include <panglos/sprintf.h>

class Output : public panglos::Output
{
    virtual int _putc(char c) {
        Serial.print(c);
        return 1;
    }
};

Output out;

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

panglos::Output *err_uart = & out;

BluetoothA2DPSink a2dp_sink;

static char bt_name[] = "xNAD-3020";

void a2d_callback(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param) {

    switch (event) {
        case ESP_A2D_CONNECTION_STATE_EVT:
            PO_ERROR("%s ESP_A2D_CONNECTION_STATE_EVT", __func__);
            break;
        case ESP_A2D_AUDIO_STATE_EVT:
            PO_ERROR("%s ESP_A2D_AUDIO_STATE_EVT", __func__);
            break;
        case ESP_A2D_AUDIO_CFG_EVT: {
            PO_ERROR("%s ESP_A2D_AUDIO_CFG_EVT", __func__);
            break;
        }
        default : {
            PO_ERROR("%s Bad Event", __func__);
            break;
        }
    }
}

void setup() {
    a2dp_sink.set_a2d_callback(a2d_callback);
    a2dp_sink.start(bt_name);  

    Serial.begin(115200);
}


void loop() {
#if 0
    static int i = 0;
    Serial.print("hello world! ");
    Serial.print(i++);
    Serial.println("");
    delay(1000);
#endif
}


