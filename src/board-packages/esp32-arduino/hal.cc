#include "core/isolation-layer/hal.h"
#include <Arduino.h>
// Silencing the gods of Arduino linkage
void loop() {}
void setup() { main(); }

namespace Cesium {
    
void hal_init() {
    ::init();
    // Just in case
}

// -------------------------
// Pins
// -------------------------

namespace Pin {
const uint8_t BUILTIN_LED{2}; // Should be LED_BUILTIN from Arduino but not sure which header
const uint8_t IMU_CS{5}; // Should be LED_BUILTIN from Arduino but not sure which header
}

// -------------------------
// SPI Ports
// -------------------------

SpiPort Spi1 = SpiPort{ // Can be any pins though
    .MISO = 19,
    .MOSI = 23,
    .SCLK = 18
};

// -------------------------
// I2C Ports
// -------------------------

i2cPort i2c1 = { // Can be any pins though
    .SDA = 21,
    .SCL = 22,
    .frequency = 100'000
};

} // namespace Cesium