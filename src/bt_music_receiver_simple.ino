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
#include <panglos/gpio.h>

#include "BluetoothA2DPSink.h"

#include "io.h"

class GPIO : public panglos::GPIO
{
    int pin;

    GPIO(int p) : pin(p) 
    {
        pinMode(pin, OUTPUT);
    }

public:
    virtual ~GPIO() { }
 
    virtual void set(bool state)
    {
        digitalWrite(pin, state ? HIGH : LOW);
    }

    virtual bool get() { return 0; }
    virtual void toggle() {}

    virtual void set_interrupt_handler(void (*fn)(void *arg), void *arg) {}
    virtual void on_interrupt() {}

    virtual bool flush() { return false; }

    static panglos::GPIO* create(int pin)
    {
        return new GPIO(pin);
    }
};

   /*
    *
    */

namespace panglos {

    void * get_task_id()
    {
        return xTaskGetCurrentTaskHandle();
    }

    timer_t timer_now()
    {
        return millis();
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

#define LED_GREEN 15
#define LED_BLUE  2

static IoConfig io;

void setup() {
    Serial.begin(115200);

    io.green = GPIO::create(LED_GREEN);
    io.blue  = GPIO::create(LED_BLUE);
    io.sink = & a2dp_sink;

    a2dp_sink.start(bt_name);  
    io_init(& io);
}

void loop() {
    io_poll();
}


