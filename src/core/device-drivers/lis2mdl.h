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

struct lis2mdl_data_t {
    float mag_x; // mGauss
    float mag_y; // mGauss
    float mag_z; // mGauss
    float temp; // deg C 
};

class Lis2Mdl {

  public:

    // Registers
    static const uint8_t REG_WHO_AM_I = 0x4F;
    static const uint8_t DEVICE_ID = 0b01000000;

    static const uint8_t REG_OUTX_L_REG = 0x32;

    static const float MAG_LSB_TO_MGAUSS = 1.5;
    static const float TEMP_DEG_C_TO_LSB = 8;

    Lis2Mdl(Spi spi, uint8_t cs_pin);
    // Adxl375(SpiPort spi_port, uint8_t cs_pin, SpiSettings settings);

    /* User functions */
    uint8_t chip_id();
    lis2mdl_data_t read(uint8_t range);

    /* Basic functions TODO: put in spi driver? */
    uint8_t _read_single(uint8_t reg);
    void _read_burst(uint8_t reg, uint8_t* buffer, uint8_t len);
    uint8_t _write_single(uint8_t reg, uint8_t val);
    void _write_burst(uint8_t reg, const uint8_t* buffer, uint8_t len);


  protected:
    Spi _spi;
    uint8_t _cs_pin;


};


} // namespace Cesium::Sensor