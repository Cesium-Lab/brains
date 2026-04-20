
#include <string>
#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/time.h"
#include <iostream>
#include <cstdio>

// char port_name[] = "/dev/cu.usbmodem1403"; // For Nucleo f042k6/z753zi
char port_name[] = "/dev/cu.usbserial-0001"; // For ESP32


Cesium::Uart uart(115200, 0, port_name);

using namespace std;

int main() {
    uart.initialize();
    const char* message = "Hello from native PlatformIO!\n";

    while(1) {
        uart.transmit_bytes((uint8_t*)message, 30, true);

        Cesium::Time::delay(1000);
    }

    return 0;
}

