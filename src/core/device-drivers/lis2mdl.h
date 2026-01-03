#pragma once

#include <stdint.h>

#include "core/isolation-layer/peripherals/spi.h"
#include "core/isolation-layer/peripherals/gpio.h"
#include "core/isolation-layer/Eigen.h"

/**
 * TODO:
 * - Interrupts
 * - FIFO
 * - Self-test
 * 
 * THIS DOESN'T WORK ON H753 RIGHT NOW??!?!?!? WHAT?!
 */

namespace Cesium::Sensor {

// struct lis2mdl_data_t {
//     float mag_x; // mGauss
//     float mag_y; // mGauss
//     float mag_z; // mGauss
//     float temp; // deg C 
// };

struct lis2mdl_data_t {
    Cesium::Vector3f B_field_uT;
    float temp; // deg C 
};

class Lis2Mdl {

  public:

    /* Registers */
    static const uint8_t REG_WHO_AM_I = 0x4F;
    static const uint8_t DEVICE_ID = 0b01000000;

    static const uint8_t CFG_REG_A = 0x60;
    static const uint8_t REG_OUTX_L_REG = 0x68;
    static const uint8_t CFG_REG_C = 0x62;

    static constexpr float MAG_LSB_TO_MGAUSS = 1.5;
    static constexpr float MGAUSS_TO_uT = 0.1;
    static constexpr float TEMP_DEG_C_TO_LSB = 8;

    // I2C
    static const uint8_t I2C_ADDR = 0x1E;

    Lis2Mdl(Spi spi, uint8_t cs_pin);
    void initialize();

    /* User functions */
    uint8_t chip_id();
    lis2mdl_data_t read();

    /* Basic functions TODO: put in spi driver? */
    uint8_t _read_single(uint8_t reg);
    void _read_burst(uint8_t reg, uint8_t* rx_buf, uint8_t len); // Maximum burst read of 19 (arbitrary)
    uint8_t _write_single(uint8_t reg, uint8_t val);
    void _write_burst(uint8_t reg, const uint8_t* tx_buf, uint8_t len); // Maximum burst write of 19 (arbitrary)


  protected:
    Spi _spi;
    uint8_t _cs_pin;

    uint8_t _rx[20]; // Maximum burst read of 19 (arbitrary)
    uint8_t _tx[20]; // Maximum burst read of 19 (arbitrary)


};


} // namespace Cesium::Sensor