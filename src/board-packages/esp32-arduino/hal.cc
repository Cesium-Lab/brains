#include <Arduino.h>
#include "core/isolation-layer/hal.h"

// Silencing the gods of Arduino linkage
int main();
void loop() {}
void setup() {main();}

namespace Cesium {
    
void hal_init() {
    ::init();
}

// Pins
const uint8_t SPI_CS = 255;

} // namespace Cesium