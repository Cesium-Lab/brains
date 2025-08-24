#pragma once

#include <stdint.h>
namespace Cesium {

// ------------------------------ //
//          Definitions
// ------------------------------ //

enum class SpiBitOrder {
    MSB_FIRST,
    LSB_FIRST
};

enum class SpiMode {
    _0,
    _1,
    _2,
    _3
};

class SpiSettings
{
public:
    SpiSettings() :_clock_hz(1000000), _bit_order(SpiBitOrder::MSB_FIRST), _spi_mode(SpiMode::_0) {}
    SpiSettings(uint32_t clock_hz, SpiBitOrder bit_order, SpiMode spi_mode)
        : _clock_hz(clock_hz), _bit_order(bit_order), _spi_mode(spi_mode) {}
    uint32_t _clock_hz;
    SpiBitOrder  _bit_order;
    SpiMode  _spi_mode;
};

// ------------------------------ //
//             Spi Class
// ------------------------------ //

class Spi {
  public:
    Spi(uint8_t instance, SpiSettings settings = SpiSettings{} );

    /**
     * Puts values into registers
     */
    bool initialize();

    uint8_t transfer(uint8_t input);

    /* MSB/LSB agnostic */
    uint16_t transfer(uint16_t input);
    /* MSB/LSB agnostic */
    uint32_t transfer(uint32_t input);

    /* MSB/LSB agnostic */
    void transfer(uint8_t* input, uint8_t size);

  private:
    SpiSettings _settings;
    uint8_t _instance;
};

} // namespace Cesium