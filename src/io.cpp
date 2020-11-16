
#include "BluetoothA2DPSink.h"

#include <panglos/debug.h>
#include <panglos/sprintf.h>

#include "io.h"

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
            xprintf(err_uart, "BT : %s\r\n", err_lookup(bt_state, param->conn_stat.state));
            break;
        case ESP_A2D_AUDIO_STATE_EVT:
            xprintf(err_uart, "Audio : %s\r\n", err_lookup(audio_state, param->audio_stat.state));
            break;
        case ESP_A2D_AUDIO_CFG_EVT: {
            xprintf(err_uart, "ESP_A2D_AUDIO_CFG_EVT\r\n");
            break;
        }
        default : {
            PO_ERROR("Bad Event");
            break;
        }
    }
}

void io_init(BluetoothA2DPSink *sink)
{
    ASSERT(sink);
    sink->set_a2d_callback(a2d_callback);
}

//  FIN
