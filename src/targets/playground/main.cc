#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/peripherals/gpio.h"
#include "core/isolation-layer/peripherals/spi.h"
#include "core/isolation-layer/time.h"
// #include <Arduino.h>
// #include <SPI.h>

using namespace Cesium;
Uart uart(115200);

SpiSettings spi_settings{};

Spi spi{spi_settings, Spi1};


int main() {
    hal_init();

    // UART
    uart.initialize();
    uart.transmit("This is the ESP32 Arduino Playground Target\n");
    uart.transmit("Setup\n");
    
    // SPI initialization
    spi.initialize();
    Gpio::init_digital(Pin::BUILTIN_LED, GpioType::DIGITAL_OUT);
    Gpio::init_digital(Pin::IMU_CS, GpioType::DIGITAL_OUT);
    Gpio::write_digital(Pin::IMU_CS, true);

    while(1) {
        uart.transmit("Loop\n");

        if (uart.available())
        {
            Gpio::write_digital(Pin::BUILTIN_LED, true);
            uint8_t c = uart.read();
            uart.transmit("Received ");
            uart.transmitln(c);
            Time::delay(25);
            Gpio::write_digital(Pin::BUILTIN_LED, false);
        }

        Time::delay(25);

        Gpio::write_digital(Pin::IMU_CS, false);
        spi.begin_transaction();
        uint8_t result = spi.transfer(0x80);
        spi.end_transaction();
        Gpio::write_digital(Pin::IMU_CS, true);

        uart.transmit_byte(result, true);

        Cesium::Time::delay(1000);
    }

    return 0;
}
