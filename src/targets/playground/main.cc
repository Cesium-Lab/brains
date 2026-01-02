#include "core/isolation-layer/hal.h"
#include "core/isolation-layer/peripherals/uart.h"
#include "core/isolation-layer/peripherals/gpio.h"
#include "core/isolation-layer/peripherals/spi.h"
#include "core/device-drivers/icm20948.h"
#include "core/device-drivers/adxl375.h"
#include "core/isolation-layer/time.h"
#include <Arduino.h>
// #include <SPI.h>

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
    SpiSettings spi_settings{};
    Spi spi{spi_settings, Spi1};
    Gpio::init_digital(Pin::IMU_CS, GpioType::DIGITAL_OUT);
    Gpio::write_digital(Pin::IMU_CS, true);
    spi.initialize();

    /* ICM20948 */

    Icm20948 icm(spi, Pin::IMU_CS);
    icm.initialize();
    icm.set_accel_range(Icm20948::ACCEL_RANGE_4_G);
    icm.set_gyro_range(Icm20948::GYRO_RANGE_2000_DPS);

    /* ADXL375 */
    Adxl375 adxl(spi, Pin::SHOCK_CS);
    // delay(1000);
    // Sensor init

    while(1) {
        uart.transmit("Loop\n");

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

        uint8_t id = adxl.chip_id();

        // uint8_t current_value = icm._read_single(Icm20948::REG_ACCEL_CONFIG_BANK_2);
        // uart.transmit("CurrVal: ");
        // uart.transmit_byte(current_value, true);
        // Sensor::icm20948_data_t data = icm.read();
        // uart.transmit("ID: ");
        // uart.transmit_byte(id, true);
        // Serial.println(data.accel_x);
        // Serial.println(data.accel_y);
        // Serial.println(data.accel_z);
        // Serial.println(data.gyro_x);
        // Serial.println(data.gyro_y);
        // Serial.println(data.gyro_z);
        // Serial.println(data.temp);
        // uart.transmit_bytes((uint8_t*)&data.accel_x, 4, true);

        Cesium::Time::delay(100);
    }

    return 0;
}
