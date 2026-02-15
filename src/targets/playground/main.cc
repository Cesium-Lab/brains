#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/peripherals/gpio.h"
#include "core/isolation-layer/peripherals/spi.h"
#include "core/device-drivers/icm20948.h"
#include "core/device-drivers/adxl375.h"
#include "core/device-drivers/lis2mdl.h"
#include "core/isolation-layer/time.h"
#include "core/isolation-layer/Eigen.h"
#include <etl/array.h>

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


    //////////////////////////////////////////////////
    //              Begin playground
    //////////////////////////////////////////////////

    Vector3f v;
    v << 1, 2, 3;

    etl::array<uint8_t, 3> a = {72,72,72};

    // uart.transmitln(a);
    // uart.transmit_bytes(a, true);


    //////////////////////////////////////////////////
    //              End playground
    //////////////////////////////////////////////////

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

        uint8_t icm_id = icm.chip_id();
        uart.transmit("ID: ");
        uart.transmit_byte(icm_id, true);

        Sensor::icm20948_data_t data_icm = icm.read();
        uart.transmit("Acceleration [m/s2]: ");
        uart.transmit_floats(data_icm.accel_m_s2.data(), 3, true);
        uart.transmit("Ang. Velocity [deg/s]: ");
        uart.transmit_floats(data_icm.gyro_dps.data(), 3, true);
        uart.transmit("Temperature [ºC]: ");
        uart.transmitln(data_icm.temp_C);


        //////////////////////////////////////////////////
        //              ADXL375
        //////////////////////////////////////////////////
        uart.transmit("ADXL375:\n");

        uint8_t adxl_id = adxl.chip_id();
        uart.transmit("ID: ");
        uart.transmit_byte(adxl_id, true);

        Sensor::adxl375_data_t data_shock = adxl.read();
        uart.transmit("Acceleration [m/s2]: ");
        uart.transmit_floats(data_shock.accel_m_s2.data(), 3, true);

        //////////////////////////////////////////////////
        //              LIS2MDL
        //////////////////////////////////////////////////
        uart.transmit("LIS2MDL:\n");
        
        uint8_t id = lis.chip_id();
        uart.transmit("ID: ");
        uart.transmit_byte(id, true); // Should be 0x40

        Sensor::lis2mdl_data_t mag_data = lis.read();
        uart.transmit("Magnetic Field [uT]: ");
        uart.transmit_floats(mag_data.B_field_uT.data(), 3, true);

        Time::delay(1000);
    }

    return 0;
}