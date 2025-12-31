#pragma once

#include <stdint.h>

#include "core/isolation-layer/peripherals/spi.h"
#include "core/isolation-layer/peripherals/gpio.h"

/**
 * TODO:
 * - Interrupts
 * - FIFO
 * - Self-test
 */

namespace Cesium::Sensor {

struct adxl375_data_t {
    float accel_x; // m/s2
    float accel_y; // m/s2
    float accel_z; // m/s2
};

class Adxl375 {

  public:

    // Registers
    static const uint8_t REG_WHO_AM_I = 0x00;
    static const uint8_t DEVICE_ID = 0b11100101;

    static const uint8_t REG_DATAX0 = 0x32;
    static const uint8_t REG_BW_RATE = 0x2C;

    Adxl375(Spi spi, uint8_t cs_pin);
    // Adxl375(SpiPort spi_port, uint8_t cs_pin, SpiSettings settings);

    /* User functions */
    uint8_t chip_id();
    adxl375_data_t read(uint8_t range);

    /* Basic functions */
    uint8_t _read_single(uint8_t reg);
    void _read_burst(uint8_t reg, uint8_t* buffer, uint8_t len);
    uint8_t _write_single(uint8_t reg, uint8_t val);
    void _write_burst(uint8_t reg, const uint8_t* buffer, uint8_t len);


  protected:
    Spi _spi;
    uint8_t _cs_pin;
};


} // namespace Cesium::Sensor