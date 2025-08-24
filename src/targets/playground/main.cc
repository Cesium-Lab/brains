#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/peripherals/gpio.h"
#include "core/isolation-layer/time.h"

using namespace Cesium;
Uart uart(115200);

int main() {
    hal_init();

    Gpio::init_digital(Pin::BUILTIN_LED, GpioType::DIGITAL_OUT);
    
    uart.initialize();
    uart.transmit("This is the ESP32 Arduino Playground Target\n");
    uart.transmit("Setup\n");

    while(1) {

        if (uart.available())
        {
            Gpio::write_digital(Pin::BUILTIN_LED, true);
            uint8_t c = uart.read();
            uart.transmit("Received ");
            
            uart.transmit(c);
            uart.transmit("\n");
            Time::delay(25);
            Gpio::write_digital(Pin::BUILTIN_LED, false);

            Time::delay(1000);

            Gpio::write_digital(Pin::BUILTIN_LED, true);

            Time::delay(1000);

            Gpio::write_digital(Pin::BUILTIN_LED, false);
        }

        Time::delay(25);
    }

    return 0;
}
