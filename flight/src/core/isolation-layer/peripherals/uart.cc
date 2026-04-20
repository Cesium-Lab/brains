#include "core/isolation-layer/peripherals/uart.h"

#include <cstring> // memset
#include <cstdio> // snprintf
namespace Cesium {

constexpr uint8_t FLOAT_BUF_LEN = 50;
char float_buf[FLOAT_BUF_LEN] = {};       // buffer to hold the formatted float

////////////////////////////////////////////////////////////////////////////////////////////////////
//                              char
////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t Uart::transmitln(char data) {
    return transmit(data) + transmit("\n");
}

uint32_t Uart::transmitln(uint8_t data) {
    return transmit(data) + transmit("\n");
}

uint32_t Uart::transmitln(const char* data, uint32_t len) {
    return transmit(data, len) + transmit("\n");
}

uint32_t Uart::transmitln(const char* data) {
    return transmit(data) + transmit("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                              uint8_t
////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t Uart::transmitln(const uint8_t* data, uint32_t len) {
    return transmit(data, len) + transmit("\n");
}

uint32_t Uart::transmit_bytes(uint8_t *bytes, uint32_t len, bool end_line) {
    char hex_byte[5] = {'0', 'x', 0, 0, ' '};

    for (uint32_t i = 0; i < len; i++) {
        uint8_t lower = (bytes[i] & 0x0F) + '0';
        uint8_t upper = ((bytes[i] >> 4) & 0xF) + '0';

        // Letter for hex
        if (lower > 0x39) lower += 7;
        if (upper > 0x39) upper += 7;

        hex_byte[2] = upper;
        hex_byte[3] = lower;

        transmit(hex_byte, 5);
    }
    
    
    if (end_line) {
        transmit("\n");
    }

    return 0;
}

uint32_t Uart::transmit_byte(uint8_t byte, bool end_line)
{
    return transmit_bytes(&byte, 1, end_line);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                              float
////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t Uart::transmit(float data, uint8_t decimal_places) {

    memset(float_buf, FLOAT_BUF_LEN, 0);


    // Format float into buffer
    snprintf(float_buf, sizeof(float_buf), "%.*f", decimal_places, data); // 3 decimal places

    return transmit(float_buf, strlen(float_buf));

}
// uint32_t Uart::transmit_floats(const float* data, uint32_t len, uint8_t decimal_places) {
//     transmit(data, len);
// }

uint32_t Uart::transmitln(float data, uint8_t decimal_places) {
    return transmit(data, decimal_places) + transmit("\n");
}

uint32_t Uart::transmit_floats(const float* data, uint32_t len, 
                               bool end_line, uint8_t decimal_places) {
    
    uint32_t count = transmit("[");

    for (uint32_t i = 0; i < len; i++) {
        count += transmit(data[i]);

        if (i < len-1) {
            count += transmit(", ");
        }
    }

    if (end_line)
        count += transmit("]\n");
    else
        count += transmit("]");

    return count;
}

} // namespace Cesium
