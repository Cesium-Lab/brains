#include "core/isolation-layer/peripherals/spi.h"
#include "core/isolation-layer/peripherals/gpio.h"
// #include <Arduino.h>
#include <SPI.h>

// THESE WILL CHANGE
// const uint8_t SCLK{18};
// const uint8_t MOSI{23};
// const uint8_t MISO{19};
// const uint8_t CS{5};

namespace Cesium {


    
SPIClass _spi;
SPISettings _arduino_settings;

Spi::Spi(SpiSettings settings, SpiPort port) 
    : _settings{settings}, _port{port} {}


void Spi::initialize()
{
    _spi.begin();
    Gpio::init_digital(_port.MISO, GpioType::DIGITAL_OUT);
    Gpio::init_digital(_port.MOSI, GpioType::DIGITAL_OUT);
    Gpio::init_digital(_port.SCLK, GpioType::DIGITAL_OUT);
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