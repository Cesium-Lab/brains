#pragma once

#include <stdint.h>

namespace Cesium {

enum class GpioType {
    DIGITAL_IN,
    DIGITAL_OUT,
    ANALOG_IN,
    ANALOG_OUT
};

class Gpio {
  public:
    static void init_digital(uint8_t pin, GpioType type);
    // static void init_analog(uint8_t pin);

    static void write_digital(uint8_t pin, bool value);
    static bool read_digital(uint8_t pin);

    // static void write_analog(uint8_t pin);
    // static uint16_t read_analog(uint8_t pin);
};


} // namespace Cesium