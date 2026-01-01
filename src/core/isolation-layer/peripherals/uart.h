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
    uint32_t transmit(char data);
    uint32_t transmit(const char* data, uint32_t len);

    uint32_t transmitln(char data);
    uint32_t transmitln(const char* data, uint32_t len);

    uint32_t transmit_byte(uint8_t byte, bool end_line = false);
    uint32_t transmit_bytes(uint8_t* bytes, uint32_t len, bool end_line = false);

    bool available();
    uint8_t read();
    
    // template<std::size_t SIZE>
    // uint32_t transmit(etl::array<uint8_t, SIZE> arr);

    // Helper
    // static uint8_t to_char(uint8_t num, bool lower_half = true) {
    //     uint8_t masked = lower_half 
    //         ? (num & 0x0F) + '0'
    //         : ( (num >> 4) & 0x0F) + '0';

    //     if (masked > '9')
    //         masked += 7; // To get to letters

    //     return masked;
    // }

  protected:
    uint32_t _baud_rate;
    int8_t _uart_instance;
    const char* _uart_name;
};

// template <std::size_t SIZE>
// inline uint32_t Uart::transmit(etl::array<uint8_t, SIZE> arr)
// {
//     uint32_t bytes = 0;
//     for (const auto& element : arr) {
//         bytes += this->transmit(element);
//     }

//     return bytes;
// }

} // namespace Cesium