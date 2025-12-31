#include "icm20948.h"


namespace Cesium::Sensor {

// Icm20948::Icm20948(SpiPort spi, uint8_t cs_pin) 
//     : _cs_pin{cs_pin}, _spi{spi} {
//     _spi.CS = _cs_pin;
// }

Icm20948::Icm20948(Spi spi, uint8_t cs_pin) 
    : _spi{spi}, _cs_pin{cs_pin}, accel_range{-1}, gyro_range{-1} {
    Gpio::init_digital(_cs_pin, GpioType::DIGITAL_OUT);
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

    return true;
}


icm20948_data_t Icm20948::read(uint8_t range)
{

    // If accel range not known already
    if (accel_range == -1) {
        _select_user_bank(2);
        // 0b00000110 
        accel_range = ((_read_single(REG_ACCEL_CONFIG_BANK_2)) >> 1) & 0b11;
    }
    
    // If gyro range not known already
    if (gyro_range == -1) {
        _select_user_bank(2);
        // 0b00000110 
        gyro_range = ((_read_single(REG_GYRO_CONFIG_BANK_2)) >> 1) & 0b11;
    }

    _select_user_bank(0);

    icm20948_data_t result;

    _read_burst(REG_ACCEL_XOUT_H_BANK_0, result.bytes, 14);

    // Scale
    float accel_scale_factor = ACCEL_RANGE_TO_SCALE_FACTOR.at(accel_range);
    result.accel_x / accel_scale_factor;
    result.accel_x / accel_scale_factor;
    result.accel_x / accel_scale_factor;

    float gyro_scale_factor = GYRO_RANGE_TO_SCALE_FACTOR.at(gyro_range);
    result.gyro_x / gyro_scale_factor;
    result.gyro_x / gyro_scale_factor;
    result.gyro_x / gyro_scale_factor;

    return result;
}


//////////////////////////////////////////////////
//              Read
//////////////////////////////////////////////////

uint8_t Icm20948::_read_single(uint8_t reg) {
    
    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg | 0x80); // read mask
    uint8_t result = _spi.transfer(0x00);

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false);  
    
    return result;
}


void Icm20948::_read_burst(uint8_t reg, uint8_t* buffer, uint8_t len) {

    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg | 0x80); // read mask
    for (uint8_t i = 0; i < len; i++) {
        buffer[i] = _spi.transfer(0x00);
    }

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false);
}

//////////////////////////////////////////////////
//              Write
//////////////////////////////////////////////////


uint8_t Icm20948::_write_single(uint8_t reg, uint8_t val) {

    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg & 0x7F); // write mask
    _spi.transfer(val);

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false); 
}


void Icm20948::_write_burst(uint8_t reg, const uint8_t* buffer, uint8_t len) {

    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg & 0x7F); // write mask
    for (uint8_t i = 0; i < len; i++) {
        _spi.transfer(buffer[i]);
    }

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false); 
}


void Icm20948::_select_user_bank(uint8_t bank) {
    _write_single(REG_BANK_SEL, bank << 4);
}



// class Icm20948 {
//   public:
//     Icm20948(uint8_t cs_pin);

//     // 
//     void select_user_bank(uint8_t bank);
    
//     void read_burst(int8_t reg, uint8_t* buffer, uint8_t len);

//     void write_burst(int8_t reg, const uint8_t* buffer, uint8_t len);

//   protected:
//     SpiPort _spi;
// };


} // namespace Cesium::Sensor