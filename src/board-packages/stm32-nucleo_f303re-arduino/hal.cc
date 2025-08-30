#include "core/isolation-layer/hal.h"

#include <board.h> // init()
#include <pins_arduino_analog.h> // PA5

namespace Cesium {
    
void hal_init() {
    ::init(); // NEEDS this! (for the onboard timer I think)
}

namespace Pin {

const uint8_t BUILTIN_LED{PA5};
const uint8_t IMU_CS{PB6}; // D10

const uint8_t SPI_SCK{PA5}; // D13
const uint8_t SPI_MOSI{PA7}; // D11
const uint8_t SPI_MISO{PA6}; // D12
}

} // namespace Cesium