#include "core/isolation-layer/hal.h"

#include <board.h> // init()
#include <pins_arduino_analog.h> // PB3
#include <pins_arduino.h> // PIN_SPI

namespace Cesium {
    
void hal_init() {
    ::init(); // NEEDS this! (for the onboard timer I think)
}

namespace Pin {

const uint8_t BUILTIN_LED{PB3};

const uint8_t SPI_SCK{PIN_SPI_SCK}; // 13
const uint8_t SPI_MOSI{PIN_SPI_MOSI}; // 11
const uint8_t SPI_MISO{PIN_SPI_MISO}; // 12
const uint8_t IMU_CS{PIN_SPI_SS}; // 10
}



} // namespace Cesium