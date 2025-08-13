#include "core/hal.h"
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/time.h"
#include <etl/array.h>
#include <etl/vector.h>

// #include <Arduino.h>

Cesium::Uart uart(115200);

int main() {
    uart.initialize();
    uart.transmit("This is the ESP32 Arduino Playground Target\n");
    uart.transmit("Setup\n");
    
    etl::array<uint8_t, 12> arr{0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x0A};
    
    // etl::vector<char> char_vec = {1};

    while(1) {
        // uart.transmit("Loop\n");

        if (uart.available())
        {
            uint8_t c = uart.read();
            uart.transmit("Received ");
            
            
            uart.transmit(char(c));
            // uart.transmit("\n");
        }
        // uart.transmit(arr);

        Cesium::Time::delay(100);
    }

    return 0;
}
