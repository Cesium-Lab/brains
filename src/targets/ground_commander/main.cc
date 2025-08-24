
#include <string>
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/time.h"
#include <iostream>
#include <cstdio>

char port_name[] = "/dev/cu.usbmodem1403"; // For Nucleo f042k6/z753zi
// char port_name[] = "/dev/cu.usbserial-0001"; // For ESP32


Cesium::Uart uart(115200, 0, port_name);

using namespace std;

int main() {
    uart.initialize();
    std::string message = "Hello from native PlatformIO!\n";
    cout << "starting" << endl;
    // printf("wow\n");
    while(1) {
        cout << "Loop: " << endl;
        for (char c : message) {
            uart.transmit(c);
            cout << ".";
        }

        cout << endl;
        

        Cesium::Time::delay_us(1000000);
    }

    return 0;
}

