
typedef struct {
    BluetoothA2DPSink *sink;
    panglos::GPIO *green;
    panglos::GPIO *blue;
}   IoConfig;

void io_init(IoConfig *io);
void io_poll();

//  FIN
