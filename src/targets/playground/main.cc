#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/peripherals/gpio.h"
#include "core/isolation-layer/peripherals/spi.h"
#include "core/device-drivers/icm20948.h"
#include "core/device-drivers/adxl375.h"
#include "core/device-drivers/lis2mdl.h"
#include "core/isolation-layer/time.h"
#include "core/isolation-layer/Eigen.h"


#include <cstdio>  // for snprintf

// #include <Arduino.h>
// #include <SPI.h>
// #include <string>

using namespace Cesium;
using namespace Cesium::Sensor;

int main() {

    

    hal_init();



    /* LED GPIO */
    Gpio::init_digital(Pin::BUILTIN_LED, GpioType::DIGITAL_OUT);

    /* UART */
    Uart uart(115200);
    uart.initialize();
    uart.transmit("This is the ESP32 Arduino Playground Target\n");
    uart.transmit("Setup\n");

    //////////////////////////////////////////////////
    //              Begin playground
    //////////////////////////////////////////////////

    Vector3f v;
    v << 1, 2, 3;

    //////////////////////////////////////////////////
    //              End playground
    //////////////////////////////////////////////////

    /* SPI */
    SpiSettings spi_settings_imu{._spi_mode=SpiMode::_0};
    SpiSettings spi_settings_shock{._spi_mode=SpiMode::_3};
    SpiSettings spi_settings_mag{};
    Spi spi_imu{spi_settings_imu, Spi1};
    Spi spi_shock{spi_settings_shock, Spi1};
    Spi spi_mag{spi_settings_mag, Spi1};

    Gpio::init_digital(Pin::IMU_CS, GpioType::DIGITAL_OUT);
    Gpio::write_digital(Pin::IMU_CS, true);
    Gpio::init_digital(Pin::SHOCK_CS, GpioType::DIGITAL_OUT);
    Gpio::write_digital(Pin::SHOCK_CS, true);
    Gpio::init_digital(Pin::MAG_CS, GpioType::DIGITAL_OUT);
    Gpio::write_digital(Pin::MAG_CS, true);

    spi_imu.initialize();
    spi_shock.initialize();
    spi_mag.initialize();

    /* ICM20948 */

    Icm20948 icm(spi_imu, Pin::IMU_CS);
    icm.initialize();
    icm.set_accel_range(Icm20948::ACCEL_RANGE_4_G);
    icm.set_gyro_range(Icm20948::GYRO_RANGE_2000_DPS);

    /* ADXL375 */
    Adxl375 adxl(spi_shock, Pin::SHOCK_CS);
    adxl.initialize();


    /* ADXL375 */
    Lis2Mdl lis(spi_mag, Pin::MAG_CS);
    lis.initialize();

    while(1) {
        uart.transmit("----- LOOP -----\n");

        if (uart.available())
        {
            Gpio::write_digital(Pin::BUILTIN_LED, true);
            uint8_t c = uart.read();
            uart.transmit("Received ");
            uart.transmit_byte(c, true);
            Time::delay(25);
            Gpio::write_digital(Pin::BUILTIN_LED, false);
        }

        Time::delay(25);

        //////////////////////////////////////////////////
        //              ICM20948
        //////////////////////////////////////////////////
        uart.transmit("ICM20948:\n");
        // uint8_t current_value = icm._read_single(Icm20948::REG_ACCEL_CONFIG_BANK_2);
        // uart.transmit("CurrVal: ");
        // uart.transmit_byte(current_value, true);

        uint8_t icm_id = icm.chip_id();
        uart.transmit("ID: ");
        uart.transmit_byte(icm_id, true);

        Sensor::icm20948_data_t data = icm.read();
        // Serial.println(data.accel_x);
        // Serial.println(data.accel_y);
        // Serial.println(data.accel_z);
        // Serial.println(data.gyro_x);
        // Serial.println(data.gyro_y);
        // Serial.println(data.gyro_z);
        // Serial.println(data.temp);
        uart.transmit_bytes((uint8_t*)&data.accel_x, 4, true);

        //////////////////////////////////////////////////
        //              ADXL375
        //////////////////////////////////////////////////
        uart.transmit("ADXL375:\n");
        uint8_t adxl_id = adxl.chip_id();
        uart.transmit("ID: ");
        uart.transmit_byte(adxl_id, true);

        Sensor::adxl375_data_t data_shock = adxl.read();
        // Serial.println(data_shock.accel_x);
        // Serial.println(data_shock.accel_y);
        // Serial.println(data_shock.accel_z);

        //////////////////////////////////////////////////
        //              LIS2MDL
        //////////////////////////////////////////////////
        uart.transmit("LIS2MDL:\n");
        
        uint8_t id = lis.chip_id();
        uart.transmit("ID: ");
        uart.transmit_byte(id, true); // Should be 0x40

        Sensor::lis2mdl_data_t mag_data = lis.read();
        // uart.transmit_bytes((uint8_t*)(&data.mag_x), 4, true);
        // uart.transmit("X: ");
        // std::string x_str = std::to_string(data.mag_x);
        // char buf[32];
        // snprintf(buf, sizeof(buf), "%f", data.mag_x); // format float into human-readable string
        // uart.transmitln(buf, strlen(buf));
        // Serial.write(buf);
        // uart.transmitln(x_str.c_str(), x_str.size());
        // uart.transmit("Y: ");
        // uart.transmitln(std::to_string(data.mag_y).c_str());
        // uart.transmit("Z: ");
        // uart.transmitln(std::to_string(data.mag_z).c_str());
        // uart.transmitln("");
        // Serial.println(mag_data.mag_x);
        // Serial.println(mag_data.mag_y);
        // Serial.println(mag_data.mag_z);
        // Serial.println(data.temp);

        Time::delay(1000);
    }

    return 0;
}