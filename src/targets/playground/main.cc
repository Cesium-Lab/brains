#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/peripherals/gpio.h"
#include "core/isolation-layer/time.h"
#include <etl/array.h>
#include <etl/vector.h>

Cesium::Uart uart(115200);

const uint8_t LED_PIN = 2;

int main() {
    Cesium::hal_init();

    Cesium::Gpio::init_digital(LED_PIN, Cesium::GpioType::DIGITAL_OUT);
    
    uart.initialize();
    uart.transmit("This is the ESP32 Arduino Playground Target\n");
    uart.transmit("Setup\n");

    while(1) {
        uart.transmit("Loops\n");

        // if (uart.available())
        // {
        //     uint8_t c = uart.read();
        //     uart.transmit("Received ");
            
        //     uart.transmit(c);
        //     uart.transmit("\n");
        // }

        // Cesium::Time::delay(25);
        Cesium::Gpio::write_digital(LED_PIN, true);
        Cesium::Time::delay(500);
        Cesium::Gpio::write_digital(LED_PIN, false);
        Cesium::Time::delay(500);
    }

    return 0;
}

// #include <Arduino.h>

// const uint8_t LED_PIN{13};

// void setup() {
//     Serial.begin(115200);
//     Serial.println("This is the 'Hello World' Target!");

//     Serial.println("Setup.");
//     pinMode(LED_PIN, OUTPUT);
// }

// void loop() {
    
//     if (Serial.available()) {
//         int c = Serial.read();
//         Serial.print("Received: ");
//         Serial.println(c);
//     }
//     Serial.println("Loop");
//     digitalWrite(LED_PIN, HIGH);
//     delay(500);
//     digitalWrite(LED_PIN, LOW);
//     delay(500);
// }
