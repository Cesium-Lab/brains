#include "core/isolation-layer/peripherals/spi.h"
#include <SPI.h>

namespace Cesium {

Spi::Spi(uint8_t instance, SpiSettings settings = SpiSettings{} ) 
    : _instance{instance}, _settings{settings} {}


bool Spi::initialize()
{

}

uint8_t Spi::transfer(uint8_t input)
{

}

uint16_t Spi::transfer(uint16_t input)
{

}
uint32_t Spi::transfer(uint32_t input)
{

}

void Spi::transfer(uint8_t* input, uint8_t size)
{

}
} // namespace Cesium