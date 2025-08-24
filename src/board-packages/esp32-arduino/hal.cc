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

namespace Pin {
const uint8_t BUILTIN_LED{2}; // Should be LED_BUILTIN from Arduino but not sure which header
const uint8_t IMU_CS{5}; // Should be LED_BUILTIN from Arduino but not sure which header

const uint8_t SPI_SCK{18};
const uint8_t SPI_MOSI{23};
const uint8_t SPI_MISO{19};
}

} // namespace Cesium