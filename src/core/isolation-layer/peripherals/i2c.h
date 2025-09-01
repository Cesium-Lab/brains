/*
constructor
initialize
transmit

*/

#pragma once

#include <stdint.h>
namespace Cesium {

// ------------------------------ //
//          Definitions
// ------------------------------ //

struct i2cPort {
    uint8_t SDA;
    uint8_t SCL;
    uint32_t frequency;
};

// ------------------------------ //
//             Spi Class
// ------------------------------ //

class I2C {
  public:
    I2C(i2cPort port);

    bool initialize();

    void set_frequency(uint32_t frequency);

    bool write(uint8_t addr, uint8_t* buff, uint8_t len, bool stop = true);
    bool read(uint8_t addr, uint8_t reg, uint8_t* buff, uint8_t len);

  private:
    uint32_t _frequency;
    i2cPort _port;
};

} // namespace Cesium