#pragma once

#include <stdint.h>
#include <etl/map.h>
#include <cstring> // memset

#include "core/isolation-layer/peripherals/spi.h"
#include "core/isolation-layer/peripherals/gpio.h"

/**
 * TODO:
 * - Interrupts
 * - FIFO
 * - Self-test
 */

namespace Cesium::Sensor {

struct icm20948_data_t {
    float accel_x; // m/s2
    float accel_y; // m/s2
    float accel_z; // m/s2
    float gyro_x; // dps
    float gyro_y; // dps
    float gyro_z; // dps
    float temp; // deg C
};

// Must call constructor AFTER SPI IS INITIALIZED
class Icm20948 {

  public:

    // Registers
    static const uint8_t REG_WHO_AM_I_BANK_0 = 0x00;
    static const uint8_t REG_ACCEL_XOUT_H_BANK_0 = 0x2D;
    
    static const uint8_t REG_PWR_MGMT_BANK_1 = 0x06;
    

    static const uint8_t REG_GYRO_CONFIG_BANK_2 = 0x01;
    static const uint8_t REG_ACCEL_CONFIG_BANK_2 = 0x14;

    static const uint8_t REG_BANK_SEL = 0x7F;

    static const uint8_t ACCEL_RANGE_2_G = 0;
    static const uint8_t ACCEL_RANGE_4_G = 1;
    static const uint8_t ACCEL_RANGE_8_G = 2;
    static const uint8_t ACCEL_RANGE_16_G = 3;

    static const uint8_t GYRO_RANGE_250_DPS = 0;
    static const uint8_t GYRO_RANGE_500_DPS = 1;
    static const uint8_t GYRO_RANGE_1000_DPS = 2;
    static const uint8_t GYRO_RANGE_2000_DPS = 3;

    static constexpr float TEMP_SENSITIVITY = 333.87;
    static constexpr float ROOM_TEMP_OFFSET = 21;

    Icm20948(Spi& spi, uint8_t cs_pin);
    void initialize();
    // Icm20948(SpiPort spi_port, uint8_t cs_pin, SpiSettings settings);

    /* User functions */
    uint8_t chip_id();
    bool set_accel_range(uint8_t range);
    bool set_gyro_range(uint8_t range);
    icm20948_data_t read();

    /* Basic functions */
    void _select_user_bank(uint8_t bank);
    uint8_t _read_single(uint8_t reg);
    void _read_burst(uint8_t reg, uint8_t* buffer, uint8_t len); // Maximum burst read of 19 (arbitrary)
    uint8_t _write_single(uint8_t reg, uint8_t val);
    void _write_burst(uint8_t reg, const uint8_t* buffer, uint8_t len); // Maximum burst read of 19 (arbitrary)


  protected:
    Spi& _spi;
    uint8_t _cs_pin;
    int8_t _accel_range;
    int8_t _gyro_range;

    uint8_t _rx[20]; // Maximum burst read of 19 (arbitrary)
    uint8_t _tx[20]; // Maximum burst read of 19 (arbitrary)

    const etl::map<uint8_t, float, 4> ACCEL_RANGE_TO_SCALE_FACTOR = {
        {ACCEL_RANGE_2_G, 16384.0},
        {ACCEL_RANGE_4_G, 8192.0},
        {ACCEL_RANGE_8_G, 4096.0},
        {ACCEL_RANGE_16_G, 2048.0},
    };

    const etl::map<uint8_t, float, 4> GYRO_RANGE_TO_SCALE_FACTOR = {
        {GYRO_RANGE_250_DPS, 131.0},
        {GYRO_RANGE_500_DPS, 65.5},
        {GYRO_RANGE_1000_DPS, 32.8},
        {GYRO_RANGE_2000_DPS, 16.4},
    };
};


} // namespace Cesium::Sensor