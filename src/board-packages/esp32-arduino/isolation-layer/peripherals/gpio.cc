#include "core/isolation-layer/peripherals/gpio.h"
#include "core/isolation-layer/hal.h"

#include <esp32-hal-gpio.h>

namespace Cesium {

void Gpio::init_digital(uint8_t pin, GpioType type)
{
    switch (type)
    {
        case GpioType::DIGITAL_IN:
        case GpioType::ANALOG_IN:
            pinMode(pin, INPUT);
        case GpioType::DIGITAL_OUT:
        case GpioType::ANALOG_OUT:
            pinMode(pin, OUTPUT);
    }
}

void Gpio::write_digital(uint8_t pin, bool value)
{
    // Don't like implicit casting so static casting instead
    digitalWrite(pin, static_cast<uint8_t>(value));
}

bool Gpio::read_digital(uint8_t pin)
{
    int result = digitalRead(pin);
    
    // Don't like implicit casting so static casting instead
    return static_cast<bool>(result);
}

} // namespace Cesium