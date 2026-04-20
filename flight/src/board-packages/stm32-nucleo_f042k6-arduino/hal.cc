#include "core/isolation-layer/hal.h"

#include <board.h> // init()
#include <pins_arduino_analog.h> // PB3
#include <pins_arduino.h> // PIN_SPI

namespace Cesium {
    
void hal_init() {
    ::init(); // NEEDS this! (for the onboard timer I think)
}

// -------------------------
// Pins
// -------------------------

namespace Pin {
const uint8_t BUILTIN_LED{PB3};
const uint8_t IMU_CS{PA11}; // D10
const uint8_t SHOCK_CS{PA8}; // D9
const uint8_t MAG_CS{PF1}; // D8
}

// -------------------------
// SPI Ports
// -------------------------

// A bunch of random SPI stuff that has not completely been checked. (Can shave down later)

SpiPort Spi1 = SpiPort{
    .MISO = PB4, // D12
    .MOSI = PB5, // D11
    .SCLK = PB3 // D13
    // .SCLK = PA5 // A21
};

} // namespace Cesium