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

// Must call constructor AFTER SPI IS INITIALIZED
class Adxl375 {

  public:

    // Registers
    static const uint8_t REG_WHO_AM_I = 0x00;
    static const uint8_t DEVICE_ID = 0b11100101;

    static const uint8_t REG_DATAX0 = 0x32;
    static const uint8_t REG_DATA_FORMAT = 0x31;
    static const uint8_t REG_BW_RATE = 0x2C;
    static const uint8_t REG_POWER_CTL = 0x2D;

    static constexpr float LSB_TO_G = 0.049;

    Adxl375(Spi spi, uint8_t cs_pin);
    void initialize();
    // Adxl375(SpiPort spi_port, uint8_t cs_pin, SpiSettings settings);

    /* User functions */
    uint8_t chip_id();
    adxl375_data_t read();

    /* Basic functions */
    uint8_t _read_single(uint8_t reg);
    void _read_burst(uint8_t reg, uint8_t* rx_buf, uint8_t len); // Maximum burst read of 19 (arbitrary)
    uint8_t _write_single(uint8_t reg, uint8_t val);
    void _write_burst(uint8_t reg, const uint8_t* tx_buf, uint8_t len); // Maximum burst read of 19 (arbitrary)


  protected:
    Spi _spi;
    uint8_t _cs_pin;

    uint8_t _rx[20]; // Maximum burst read of 19 (arbitrary)
    uint8_t _tx[20]; // Maximum burst read of 19 (arbitrary)
};


} // namespace Cesium::Sensor