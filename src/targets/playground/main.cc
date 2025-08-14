// #include "core/isolation-layer/hal.h"
// #include "core/isolation-layer/peripherals/uart.h"
// #include "core/isolation-layer/time.h"
// #include <etl/array.h>
// #include <etl/vector.h>

// Cesium::Uart uart(115200);

// int main() {
//     Cesium::hal_init();

//     uart.initialize();
//     uart.transmit("This is the ESP32 Arduino Playground Target\n");
//     uart.transmit("Setup\n");
    
//     etl::array<uint8_t, 12> arr{0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x0A};
    
//     // etl::vector<char> char_vec = {1};

//     while(1) {
//         uart.transmit("Loop\n");

//         if (uart.available())
//         {
//             uint8_t c = uart.read();
//             uart.transmit("Received ");
            
            
//             uart.transmit(c);
//             uart.transmit("\n");
//         }

//         Cesium::Time::delay(1000);
//     }

//     return 0;
// }

#include <Arduino.h>

const uint8_t LED_PIN{13};

void setup() {
    Serial.begin(115200);
    Serial.println("This is the 'Hello World' Target!");

    Serial.println("Setup.");
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    
    if (Serial.available()) {
        int c = Serial.read();
        Serial.print("Received: ");
        Serial.println(c);
    }
    Serial.println("Loop");
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
}
