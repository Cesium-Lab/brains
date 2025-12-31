#pragma once

#include <stdint.h>

#include "core/isolation-layer/peripherals/spi.h"
#include "core/isolation-layer/peripherals/gpio.h"


namespace Cesium::Sensor {




class Icm20948 {

    // Registers
    static const uint8_t REG_WHO_AM_I_BANK_1 = 0x7F;
    static const uint8_t REG_BANK_SEL = 0x7F;
    
  public:
    Icm20948(Spi spi, uint8_t cs_pin);
    // Icm20948(SpiPort spi_port, uint8_t cs_pin, SpiSettings settings);

    /* User functions */
    uint8_t chip_id();

    /* Basic functions */
    void _select_user_bank(uint8_t bank);
    uint8_t _read_single(uint8_t reg);
    void _read_burst(uint8_t reg, uint8_t* buffer, uint8_t len);
    uint8_t _write_single(uint8_t reg, uint8_t val);
    void _write_burst(uint8_t reg, const uint8_t* buffer, uint8_t len);

  protected:
    Spi _spi;
    uint8_t _cs_pin;
};


} // namespace Cesium::Sensor