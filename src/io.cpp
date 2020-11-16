
#include "BluetoothA2DPSink.h"

#include <panglos/debug.h>
#include <panglos/sprintf.h>
#include <panglos/gpio.h>

#include "io.h"

static IoConfig *io;
static bool connected = false;

   /*
    *
    */

static panglos::Code bt_state[] = {
    { ESP_A2D_CONNECTION_STATE_DISCONNECTED,    "Disconnected" },
    { ESP_A2D_CONNECTION_STATE_CONNECTING,      "Connecting" },
    { ESP_A2D_CONNECTION_STATE_CONNECTED,       "Connected" },
    { ESP_A2D_CONNECTION_STATE_DISCONNECTING,   "Disconnecting" },
    {   0, 0 },
};

static panglos::Code audio_state[] = {
    { ESP_A2D_AUDIO_STATE_REMOTE_SUSPEND,       "Suspend" },
    { ESP_A2D_AUDIO_STATE_STOPPED,              "Stopped" },
    { ESP_A2D_AUDIO_STATE_STARTED,              "Started" },
    {   0, 0 },
};

void a2d_callback(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param)
{
    switch (event) {
        case ESP_A2D_CONNECTION_STATE_EVT:
            PO_DEBUG("BT : %s", err_lookup(bt_state, param->conn_stat.state));

            switch (param->conn_stat.state) {
                case ESP_A2D_CONNECTION_STATE_CONNECTED : 
                {
                    io->green->set(1);
                    io->blue->set(0);
                    connected = true;
                    break;
                }
                case ESP_A2D_CONNECTION_STATE_DISCONNECTED :
                case ESP_A2D_CONNECTION_STATE_CONNECTING :
                case ESP_A2D_CONNECTION_STATE_DISCONNECTING :
                {
                    io->green->set(1);
                    io->blue->set(1);
                    connected = false;
                    break;
                }
                default : PO_ERROR("Bad BT State");
            }

            break;
        case ESP_A2D_AUDIO_STATE_EVT: {
            PO_DEBUG("Audio : %s", err_lookup(audio_state, param->audio_stat.state));

            switch (param->audio_stat.state) {
                case ESP_A2D_AUDIO_STATE_STARTED :
                {
                    io->green->set(connected ? 0 : 1);
                    break;
                }
                case ESP_A2D_AUDIO_STATE_REMOTE_SUSPEND :
                case ESP_A2D_AUDIO_STATE_STOPPED :
                {
                    io->green->set(1);
                    break;
                }
                default : PO_ERROR("Bad Audio State");
            }
            break;
        }
        case ESP_A2D_AUDIO_CFG_EVT: {
            PO_DEBUG("ESP_A2D_AUDIO_CFG_EVT");
            break;
        }
        default : {
            PO_ERROR("Bad Event");
            break;
        }
    }
}

    /*
     *
     */

void io_init(IoConfig *io_config)
{
    io = io_config;
    ASSERT(io);
    ASSERT(io->sink);
    io->sink->set_a2d_callback(a2d_callback);

    ASSERT(io->green);
    ASSERT(io->blue);
    io->green->set(1);
    io->blue->set(1);
}

void io_poll()
{
}

//  FIN
