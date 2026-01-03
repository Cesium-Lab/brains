#pragma once

#include <stdint.h>
// #include <WString.h> // from Arduino
// #include <etl/array.h>

namespace Cesium {

class Uart { // TODO: will extend from a common base class to swap interfaces
  public:
    Uart(uint32_t baud_rate = 115200, int8_t uart_instance = 0, const char* port_name = nullptr);
    // Uart(uint32_t baud_rate = 115200, uint8_t rx_pin, uint8_t tx_pin,);

    bool initialize();
    // uint32_t transmit(String data);

    //////////////////////////////////////////////////
    //              chars
    //////////////////////////////////////////////////

    uint32_t transmit(char data);
    uint32_t transmit(const char* data, uint32_t len);
    uint32_t transmit(const char* data); // For just transmitting c strings 

    uint32_t transmitln(char data);
    uint32_t transmitln(const char* data, uint32_t len);
    uint32_t transmitln(const char* data); // For just transmitting c strings 

    //////////////////////////////////////////////////
    //              uint8_t
    //////////////////////////////////////////////////
    
    uint32_t transmit(uint8_t data);
    uint32_t transmit(const uint8_t* data, uint32_t len);

    uint32_t transmitln(uint8_t data);
    uint32_t transmitln(const uint8_t* data, uint32_t len);

    uint32_t transmit_byte(uint8_t byte, bool end_line = false); // Transmits 0xBB for the bytes
    uint32_t transmit_bytes(uint8_t* bytes, uint32_t len, bool end_line = false); // Transmits 0xBB for the bytes

    //////////////////////////////////////////////////
    //              Float
    //////////////////////////////////////////////////

    uint32_t transmit(float data, uint8_t decimal_places = 2);
    uint32_t transmitln(float data, uint8_t decimal_places = 2);

    uint32_t transmit_floats(const float* data, uint32_t len, bool end_line = false, uint8_t decimal_places = 2);


    //////////////////////////////////////////////////
    //              Extras
    //////////////////////////////////////////////////

    bool available();
    uint8_t read();
    

  protected:
    uint32_t _baud_rate;
    int8_t _uart_instance;
    const char* _uart_name;
};

} // namespace Cesium
