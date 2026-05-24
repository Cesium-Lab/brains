#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/uart.h"
#include "core/utilities/print.h"
#include "core/isolation-layer/peripherals/gpio.h"
#include "core/isolation-layer/peripherals/spi.h"
#include "core/device-drivers/icm20948.h"
#include "core/device-drivers/adxl375.h"
#include "core/device-drivers/lis2mdl.h"
#include "core/isolation-layer/time.h"
#include "core/isolation-layer/Eigen.h"

#include "core/utilities/basic-filters.h"
#include "core/gnc/estimation/ekf.h"


// #include <cstdio>  // for snprintf

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
    // uart.initialize();
    
    // p.printk("This is the ESP32 Arduino Playground Target\n");
    // p.printk("Setup\n");

    Print p(uart);
    p.begin();

    // while(1) {
    //     p.putk("hello\n");
    //     p.emit_num(100, 10);
    //     p.printk("\nHello from Print! Number: %d, Hex: %0X, String: %s\n", 42, 255, "Test");
    //     Time::delay(1000);
    // }

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

    uint8_t icm_id = icm.chip_id();
    p.printk("ICM20948 ID: %0X\n", icm_id); // Should be 0xEA

    uint8_t adxl_id = adxl.chip_id();
    p.printk("ADXL375 ID: %0X\n", adxl_id); // Should be 0xE5

    uint8_t lis_id = lis.chip_id();
    p.printk("LIS2MDL ID: %0X\n", lis_id); // Should be 0x40


    while(1) {
        // p.printk("----- LOOP -----\n");

        // if (uart.available())
        // {
        //     Gpio::write_digital(Pin::BUILTIN_LED, true);
        //     uint8_t c = uart.read();
        //     p.printk("Received %c", c);
        //     Time::delay(25);
        //     Gpio::write_digital(Pin::BUILTIN_LED, false);
        // }

        Time::delay(25);

        //////////////////////////////////////////////////
        //              ICM20948
        //////////////////////////////////////////////////
        // p.printk("ICM20948:\n"); 

        // Sensor::icm20948_data_t data_icm = icm.read();
        // p.printk("Acceleration [m/s2]: %v3\n", &data_icm.accel_m_s2);
        // p.printk("Ang. Velocity [deg/s]: %v3\n", &data_icm.gyro_dps);
        // p.printk("Temperature [ºC]: %f\n", data_icm.temp_C);

        //////////////////////////////////////////////////
        //              ADXL375
        //////////////////////////////////////////////////
        // p.printk("ADXL375:\n");

        Sensor::adxl375_data_t data_shock = adxl.read();
        // p.printk("Acceleration [m/s2]: %vX3\n", &data_shock.accel_m_s2);
        
        uint8_t sync[2] = {0xAA, 0x55};
        uart.transmit(sync, 2);
        uart.transmit(adxl_id);
        uart.transmit((uint8_t*)&data_shock.accel_m_s2, sizeof(float) * 3);
        uart.transmit("\n");

        //////////////////////////////////////////////////
        //              LIS2MDL
        //////////////////////////////////////////////////
        // p.printk("LIS2MDL:\n");

        // Sensor::lis2mdl_data_t mag_data = lis.read();
        // p.printk("Magnetic Field [uT]: %v3\n", &mag_data.B_field_uT);

        // Time::delay(1000);
    }

    return 0;
}