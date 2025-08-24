#include "core/isolation-layer/peripherals/spi.h"
// #include <Arduino.h>
#include <SPI.h>

// THESE WILL CHANGE
// const uint8_t SCK{18};
// const uint8_t MOSI{23};
// const uint8_t MISO{19};
// const uint8_t CS{5};

namespace Cesium {

SpiPort SPI0 = SpiPort{
    .MISO = 19,
    .MOSI = 23,
    .SCK = 18
};
    
SPIClass _spi;
SPISettings _arduino_settings;

Spi::Spi(SpiSettings settings, SpiPort port) 
    : _settings{settings}, _port{port} {}


void Spi::initialize()
{
    _spi.begin(_port.SCK, _port.MISO, _port.MOSI);

    set_settings(_settings);
}

void Spi::set_settings(SpiSettings settings) {
    // Conversion of my SpiSettings into Arduino's
    _settings = settings;
}

void Spi::begin_transaction() {
    SPISettings arduino_settings{
        _settings._clock_hz,
        (_settings._bit_order == SpiBitOrder::MSB_FIRST) ? uint8_t(SPI_MSBFIRST) : uint8_t(SPI_LSBFIRST),
        uint8_t(_settings._spi_mode) // Simple casting by numbers
    };

    _spi.beginTransaction(arduino_settings);
}

void Spi::end_transaction() {
    _spi.endTransaction();
}

uint8_t Spi::transfer(uint8_t input)
{
    uint8_t output;

    _spi.transfer(input);
    output = _spi.transfer({});

    return output;
}

void Spi::transfer(uint8_t* input, uint8_t size)
{
    _spi.transfer(input, size);
}

} // namespace Cesium