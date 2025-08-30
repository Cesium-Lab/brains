#include "core/isolation-layer/peripherals/spi.h"

#include <pins_arduino.h> // PIN_SPI

#include <SPI.h>

namespace Cesium {

SpiPort SPI0 = SpiPort{
    .MISO = PIN_SPI_MISO,
    .MOSI = PIN_SPI_MOSI,
    .SCLK = PIN_SPI_SCK
};

// SpiPort SPI0 = SpiPort{
//     .MISO = PinName::PA6,
//     .MOSI = PinName::PA7,
//     .SCLK = PinName::PA5
// };
    
SPIClass _spi;

Spi::Spi(SpiSettings settings, SpiPort port) 
    : _settings{settings}, _port{port} {}


void Spi::initialize()
{
    _spi.begin();
    _spi.setMISO(_port.MISO);
    _spi.setMOSI(_port.MOSI);
    _spi.setSCLK(_port.SCLK);

    set_settings(_settings);
}

void Spi::set_settings(SpiSettings settings) {
   
    _settings = settings;
}

void Spi::begin_transaction() {
     // Conversion of my SpiSettings into Arduino's
    SPISettings arduino_settings{
        _settings._clock_hz,
        (_settings._bit_order == SpiBitOrder::MSB_FIRST) ? BitOrder::MSBFIRST : BitOrder::LSBFIRST,
        SPIMode(_settings._spi_mode) // Simple casting by numbers
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
    output = _spi.transfer(0x00);

    return output;
}

void Spi::transfer(uint8_t* input, uint8_t size)
{
    _spi.transfer(input, size);
}

} // namespace Cesium