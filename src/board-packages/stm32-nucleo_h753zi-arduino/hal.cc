#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/spi.h"
#include <board.h> // init()
#include <pins_arduino_analog.h> // Analog Pins Macros

namespace Cesium {
    
void hal_init() {
    ::init(); // NEEDS this! (for the onboard timer I think)
}

// -------------------------
// Pins
// -------------------------

namespace Pin {
const uint8_t BUILTIN_LED{PB0};
const uint8_t IMU_CS{PD14}; // D10
const uint8_t SHOCK_CS{PD15}; // D9
const uint8_t MAG_CS{PE9}; // D7
}


// -------------------------
// SPI Ports
// -------------------------

// A bunch of random SPI stuff that has not completely been checked. (Can shave down later)

SpiPort Spi1 = SpiPort{ // Works
    .MISO = PA6, // D12
    // .MISO = PB4, //D25 (doesn't work for some reason)
    // .MISO = PG9,

    // .MOSI = PA7,
    .MOSI = PB5, // D11/D22
    // .MOSI = PD7, // D51

    .SCLK = PA5 // D13 
    // .SCLK = PB3 // D23
    // .SCLK = PG11

    // .CS = PA4 // D24
    // .CS = PA15 // D20
    // .CS = PG10
};

SpiPort Spi2 = SpiPort{
    // .MISO = PB14, 
    .MISO = PC2_C, // A4
    // .MISO = PI2, 

    // .MOSI = PB15, // D17
    // .MOSI = PC1, 
    .MOSI = PC3_C, // A2
    // .MOSI = PI3, 
    
    // .SCLK = PA9 
    // .SCLK = PA12
    // .SCLK = PB10 // D36
    .SCLK = PD3 // D55
    // .SCLK = PI1

    // .CS = PA11
    // .CS = PB4 // D25
    // .CS = PB9
    // .CS = PB12
    // .CS = PI0
};

SpiPort Spi3 = SpiPort{ // Works
    .MISO = PA6, // D12
    // .MISO = PB4,
    // .MISO = PC11,

    // .MOSI = PB2,
    .MOSI = PB5, // D11/D22
    // .MOSI = PC12,
    // .MOSI = PD6,

    // .SCLK = PA5 // D13
    // .SCLK = PB3 // D23

    // .CS = PA4 // D24
    // .CS = PA15 // D20
};

SpiPort Spi4 = SpiPort{ // Works
    .MISO = PE5, // D58
    // .MISO = PE13, // D3

    .MOSI = PE6, // D59
    // .MOSI = PE14, // D4

    // .SCLK = PE2 // D31
    .SCLK = PE12 // D39
    // .SCLK = PE12

    // CS = PE4 // D57
    // CS = PE11 // D5
};

SpiPort Spi5{
    .MISO = PF8, // D61
    // .MISO = PH7,
    // .MISO = PJ11,
    
    .MOSI = PF9, // D63
    // .MOSI = PF11,
    // .MOSI = PJ10,

    .SCLK = PF7 // D62
    // .SCLK = PH6
    // .SCLK = PK0

    // .CS = PF6 // A8
    // .CS = PH5
    // .CS = PK1
};

SpiPort Spi6{
    // .MISO = PA6, // D12
    // .MISO = PB4, // D25
    // .MISO = PG12, // D7
    
    // .MOSI = PA7,
    // .MOSI = PB5, // D11/D22
    // .MOSI = PG14, // D2

    // .SCLK = PA5 // D13
    // .SCLK = PB3 // D23
    // .SCLK = PG13

    // .CS = PA4 // D24
    // .CS = PA15 // D20
    // .CS = PG8
};



} // namespace Cesium