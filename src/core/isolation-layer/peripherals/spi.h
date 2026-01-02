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
    _0 = 0,
    _1 = 1,
    _2 = 2,
    _3 = 3
};

struct SpiPort {
    uint8_t MISO;
    uint8_t MOSI;
    uint8_t SCLK;
    uint8_t CS = 0;
};

struct SpiSettings
{
    uint32_t _clock_hz = 1'000'000;
    SpiBitOrder  _bit_order = SpiBitOrder::MSB_FIRST;
    SpiMode  _spi_mode = SpiMode::_0;
};

// ------------------------------ //
//             Spi Class
// ------------------------------ //

class Spi {
  public:
    Spi(SpiSettings settings, SpiPort port);

    /**
     * Puts values into registers
     */
    void initialize();

    void set_settings(SpiSettings settings);

    void begin_transaction();
    void end_transaction();

    uint8_t transfer(uint8_t input);

    /* MSB/LSB agnostic */
    void transfer(uint8_t* input, uint8_t size);

  protected:
    SpiSettings _settings;
    SpiPort _port;
};

extern SpiPort SPI0;

} // namespace Cesium