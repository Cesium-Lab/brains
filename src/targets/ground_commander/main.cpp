
#include <string>
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/time.h"
#include <iostream>
#include <cstdio>
Cesium::Uart uart(115200);

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
        

        Cesium::Time::delay(1000000);
    }

    return 0;
}

