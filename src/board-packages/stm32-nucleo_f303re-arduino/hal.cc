#include "core/isolation-layer/hal.h"

#include <board.h> // init()
#include <pins_arduino_analog.h> // PA5

namespace Cesium {
    
void hal_init() {
    ::init(); // NEEDS this! (for the onboard timer I think)
}

// -------------------------
// Pins
// -------------------------


namespace Pin {
const uint8_t BUILTIN_LED{PA5};
const uint8_t IMU_CS{PB6}; // D10
}

// -------------------------
// SPI Ports
// -------------------------

// A bunch of random SPI stuff that has not completely been checked. (Can shave down later)

SpiPort Spi1 = SpiPort{ // Works
    .MISO = PA6, // D12
    .MOSI = PA7, // D11/D22
    .SCLK = PA5 // D23
};

SpiPort Spi2 = SpiPort{ // Works
    .MISO = PA10, // D2 
    .MOSI = PA11, // D12 to right
    .SCLK =  PB13 // D4 to right
};

} // namespace Cesium