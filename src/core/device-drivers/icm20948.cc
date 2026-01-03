#include "core/device-drivers/icm20948.h"
#include "core/utilities/bits.h"
#include "core/isolation-layer/peripherals/uart.h"
// #include <Arduino.h>
namespace Cesium::Sensor {

// Icm20948::Icm20948(SpiPort spi, uint8_t cs_pin) 
//     : _cs_pin{cs_pin}, _spi{spi} {
//     _spi.CS = _cs_pin;
// }

float gravity = 9.80665; // m/s2

Icm20948::Icm20948(Spi& spi, uint8_t cs_pin) 
    : _spi{spi}, _cs_pin{cs_pin}, _accel_range{-1}, _gyro_range{-1} {
    Gpio::init_digital(_cs_pin, GpioType::DIGITAL_OUT);
    Gpio::write_digital(_cs_pin, true);
}

void Icm20948::initialize() {
    _select_user_bank(0);
    _write_single(Icm20948::REG_PWR_MGMT_BANK_1, 0x01);
}


uint8_t Icm20948::chip_id() {
    _select_user_bank(0);
    return _read_single(REG_WHO_AM_I_BANK_0);
}


bool Icm20948::set_accel_range(uint8_t range)
{
    _select_user_bank(2);
    uint8_t current_value = _read_single(REG_ACCEL_CONFIG_BANK_2);

    uint8_t new_value = (current_value & 0b11111001) | ( (range & 0b11) << 1);
    _write_single(REG_ACCEL_CONFIG_BANK_2, new_value);
    
    current_value = _read_single(REG_ACCEL_CONFIG_BANK_2);

    if (new_value != current_value) {
        return false;
    }

    _accel_range = range;
    return true;
}


bool Icm20948::set_gyro_range(uint8_t range)
{
    // This is technically basically a copy of the accel one, oops
    _select_user_bank(2);
    uint8_t current_value = _read_single(REG_GYRO_CONFIG_BANK_2);

    uint8_t new_value = (current_value & 0b11111001) | ( (range & 0b11) << 1);
    _write_single(REG_GYRO_CONFIG_BANK_2, new_value);
    
    current_value = _read_single(REG_GYRO_CONFIG_BANK_2);

    if (new_value != current_value) {
        return false;
    }

    _gyro_range = range;
    return true;
}


icm20948_data_t Icm20948::read()
{

    // If accel range not known already
    if (_accel_range == -1) {
        _select_user_bank(2);
        // 0b00000110 
        _accel_range = ((_read_single(REG_ACCEL_CONFIG_BANK_2)) >> 1) & 0b11;
    }
    
    // If gyro range not known already
    if (_gyro_range == -1) {
        _select_user_bank(2);
        // 0b00000110 
        _gyro_range = ((_read_single(REG_GYRO_CONFIG_BANK_2)) >> 1) & 0b11;
    }

    _select_user_bank(0);

    icm20948_data_t result;
    uint8_t buffer[14]{};

    _read_burst(REG_ACCEL_XOUT_H_BANK_0, buffer, 14);

    // Scale
    float accel_scale_factor = ACCEL_RANGE_TO_SCALE_FACTOR.at(_accel_range);
    result.accel_m_s2[0] = bytes_to_float(buffer + 0) / accel_scale_factor * gravity;
    result.accel_m_s2[1] = bytes_to_float(buffer + 2) / accel_scale_factor * gravity;
    result.accel_m_s2[2] = bytes_to_float(buffer + 4) / accel_scale_factor * gravity;

    float gyro_scale_factor = GYRO_RANGE_TO_SCALE_FACTOR.at(_gyro_range);
    result.gyro_dps[0] = bytes_to_float(buffer + 6) / gyro_scale_factor;
    result.gyro_dps[1] = bytes_to_float(buffer + 8) / gyro_scale_factor;
    result.gyro_dps[2] = bytes_to_float(buffer + 10) / gyro_scale_factor;

    // TEMP_degC = ((TEMP_OUT – RoomTemp_Offset)/Temp_Sensitivity) + 21degC
    result.temp_C = (bytes_to_float(buffer + 12) - ROOM_TEMP_OFFSET) / TEMP_SENSITIVITY + 21; 

    return result;
}


//////////////////////////////////////////////////
//              Read
//////////////////////////////////////////////////

uint8_t Icm20948::_read_single(uint8_t reg) {

    uint8_t buf[2] = {(uint8_t)(reg | 0x80), 0x00};
    
    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();

    _spi.transfer(buf, 2); // read mas

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true);  
    
    return buf[1];
}


void Icm20948::_read_burst(uint8_t reg, uint8_t* rx_buf, uint8_t len) {

    // uint8_t buf[len + 1] = {};
    _tx[0] = reg | 0x80;
    memset(_tx + 1, 0x00, len);

    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();

    _spi.transfer(_tx, _rx, len+1); // read mask

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true);

    memcpy(rx_buf, _rx + 1, len);

}

//////////////////////////////////////////////////
//              Write
//////////////////////////////////////////////////


uint8_t Icm20948::_write_single(uint8_t reg, uint8_t val) {

    uint8_t buf[2] = {(uint8_t)(reg & 0x7F), val};

    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();
    _spi.transfer(buf, 2); // write mask
    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true);
    
    return 1;
}


// TODO: this probably doesn't work
void Icm20948::_write_burst(uint8_t reg, const uint8_t* buffer, uint8_t len) {
    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();

    _spi.transfer(reg & 0x7F); // write mask
    for (uint8_t i = 0; i < len; i++) {
        _spi.transfer(buffer[i]);
    }

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true); 
}


void Icm20948::_select_user_bank(uint8_t bank) {
    _write_single(REG_BANK_SEL, bank << 4);
}


} // namespace Cesium::Sensor