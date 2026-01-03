#include "core/isolation-layer/peripherals/uart.h"

#include <cstring> // memset
#include <cstdio> // snprintf
#include <Arduino.h>

namespace Cesium {

constexpr uint8_t FLOAT_BUF_LEN = 50;

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
    char hex_byte[4] = {'0', 'x', 0, 0};
    uint32_t count = 0;

    for (uint32_t i = 0; i < len; i++) {
        uint8_t lower = (bytes[i] & 0x0F) + '0';
        uint8_t upper = ((bytes[i] >> 4) & 0xF) + '0';

        // Letter for hex
        if (lower > 0x39) lower += 7;
        if (upper > 0x39) upper += 7;

        hex_byte[2] = upper;
        hex_byte[3] = lower;

        count += transmit(hex_byte, 4);

        if (i < len-1) {
            count += transmit(" ");
        }
    }
    
    
    if (end_line) {
        count += transmit("\n");
    }

    return count;
}

uint32_t Uart::transmit_byte(uint8_t byte, bool end_line)
{
    return transmit_bytes(&byte, 1, end_line);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                              float
////////////////////////////////////////////////////////////////////////////////////////////////////

// uint32_t Uart::transmit(float data, uint8_t decimal_places) {
    // char float_buf[FLOAT_BUF_LEN];
    // memset(float_buf, 0, FLOAT_BUF_LEN);


    // // Format float into buffer
    // snprintf(float_buf, FLOAT_BUF_LEN, "%.*f", decimal_places, data); // 3 decimal places

//     return transmit(float_buf, strlen(float_buf));

// }


uint32_t Uart::transmit(uint16_t data) { return transmit((uint64_t)data); }

uint32_t Uart::transmit(uint32_t data) { return transmit((uint64_t)data); }

// From Arduino
uint32_t Uart::transmit(uint64_t data)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  do {
    unsigned long m = data;
    data /= 10;
    char c = m - 10 * data;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while (data);

  return transmit(str);
}

uint32_t Uart::transmitln(uint16_t data) {
    transmit((uint64_t)data) + transmit("\n"); // Casted to 64 to prevented doubly nested calls
}
uint32_t Uart::transmitln(uint32_t data) {
    transmit((uint64_t)data) + transmit("\n"); // Casted to 64 to prevented doubly nested calls
}
uint32_t Uart::transmitln(uint64_t data) {
    transmit(data) + transmit("\n");
}

// From Arduino YAY! https://www.h-schmidt.net/FloatConverter/IEEE754.html 
uint32_t Uart::transmit(float data, uint8_t decimal_places)
{
  size_t n = 0;

  if (isnan(data)) {
    return transmit("nan");
  }
  if (isinf(data)) {
    return transmit("inf");
  }
  if (data > 4294967040.0) {
    return transmit("ovf");  // constant determined empirically
  }
  if (data < -4294967040.0) {
    return transmit("ovf");  // constant determined empirically
  }

  // Handle negative numbers
  if (data < 0.0) {
    n += transmit("-");
    data = -data;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  float rounding = 0.5;
  for (uint8_t i = 0; i < decimal_places; ++i) {
    rounding /= 10.0;
  }

  data += rounding;

  // Extract the integer part and print it
  uint32_t int_part = (unsigned long)data;
  float remainder = data - (float)int_part;
  n += transmit(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (decimal_places > 0) {
    n += transmit(".");
  }

  // Extract digits from the remainder one at a time
  while (decimal_places-- > 0) {
    remainder *= 10.0;
    uint32_t toPrint = (unsigned int)remainder;
    n += transmit(toPrint);
    remainder -= toPrint;
  }

  return n;
}

uint32_t Uart::transmitln(float data, uint8_t decimal_places) {
    return transmit(data, decimal_places) + transmit("\n");
}

uint32_t Uart::transmit_floats(const float* data, uint32_t len, 
                               bool end_line, uint8_t decimal_places) {
    
    uint32_t count = transmit("[");

    for (uint32_t i = 0; i < len; i++) {
        count += transmit(data[i], decimal_places);

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

////////////////////////////////////////////////////////////////////////////////////////////////////
//                              etl
////////////////////////////////////////////////////////////////////////////////////////////////////

void Uart::transmit(etl::span<const uint8_t> bytes) {
    transmit(bytes.data(), bytes.size());
}

void Uart::transmitln(etl::span<const uint8_t> bytes) {
    transmitln(bytes.data(), bytes.size());
}

uint32_t Uart::transmit_bytes(etl::span<const uint8_t> bytes, bool end_line) {
    uint32_t count = transmit("[");

    for (auto byte_ptr = bytes.begin(); byte_ptr != bytes.end(); byte_ptr++) {
        count += transmit_byte(*byte_ptr);
        count += transmit(" ");
    }

    if (end_line)
        count += transmit("]\n");
    else
        count += transmit("]");

    return count;
}


} // namespace Cesium
