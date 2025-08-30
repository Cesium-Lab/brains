#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/spi.h"
#include <board.h> // init()
#include <pins_arduino_analog.h> // Analog Pins Macros

namespace Cesium {
    
void hal_init() {
    ::init(); // NEEDS this! (for the onboard timer I think)
}


// SPI
SpiPort Spi0 = SpiPort{};

SpiPort Spi1 = SpiPort{
    .MISO = PA6, // D12
    .MOSI = PB5, // D11
    .SCLK = PA5 // D13 
};

SpiPort Spi2 = SpiPort{
    .MISO = PC2_C, // 
    .MOSI = PC3_C, // 
    .SCLK = PA9 // 
};

SpiPort Spi3 = SpiPort{};

SpiPort Spi4 = SpiPort{
    .MISO = PE5,
    .MOSI = PE6,
    .SCLK = PE12
};



namespace Pin {

const uint8_t BUILTIN_LED{PB0};
const uint8_t IMU_CS{PD14}; // D10

const uint8_t SPI_SCK{}; // D13
const uint8_t SPI_MOSI{}; // D11
const uint8_t SPI_MISO{}; // D12
}

} // namespace Cesium