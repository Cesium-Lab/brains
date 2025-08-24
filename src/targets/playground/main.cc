#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/peripherals/gpio.h"
#include "core/isolation-layer/peripherals/spi.h"
#include "core/isolation-layer/time.h"
#include <Arduino.h>
using namespace Cesium;
Uart uart(115200);

SpiSettings spi_settings{ /* Defaults */};

Spi spi{spi_settings, SPI0};


int main() {
    hal_init();

    Gpio::init_digital(Pin::BUILTIN_LED, GpioType::DIGITAL_OUT);
    
    uart.initialize();
    uart.transmit("This is the ESP32 Arduino Playground Target\n");
    uart.transmit("Setup\n");

    // SPI initialization
    spi.initialize();
    Gpio::init_digital(5, GpioType::DIGITAL_OUT);
    
    // etl::vector<char> char_vec = {1};

    while(1) {
        uart.transmit("Loop\n");

        if (uart.available())
        {
            Gpio::write_digital(Pin::BUILTIN_LED, true);
            uint8_t c = uart.read();
            uart.transmit("Received ");
            
            uart.transmit(c);
            uart.transmit("\n");
            Time::delay(25);
            Gpio::write_digital(Pin::BUILTIN_LED, false);

            // Time::delay(1000);

            // Gpio::write_digital(Pin::BUILTIN_LED, true);

            // Time::delay(1000);

            // Gpio::write_digital(Pin::BUILTIN_LED, false);
        }

        // Time::delay(25);
        // Cesium::Time::delay(25);
        uart.transmit((char)'h');
        uart.transmit((char)'m');
        uart.transmit((char)'m');
        uart.transmit((char)'\n');
        Gpio::write_digital(5, false);
        
        // spi.transfer(0x80);
        spi.begin_transaction();
        uint8_t result = spi.transfer(0x80);
        spi.end_transaction();
        
        Gpio::write_digital(5, true);
        uart.transmit(result);
        Serial.println(result, HEX);
        Serial.println(result, HEX);

        uart.transmit((char)'h');
        uart.transmit((char)'m');
        uart.transmit((char)'m');
        uart.transmit((char)'\n');

        Cesium::Time::delay(1000);

        

        
    }

    return 0;
}
