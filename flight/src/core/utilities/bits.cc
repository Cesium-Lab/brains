#include <stdint.h>

// Turns two  `uint8_t` (MSB-first) into a `uint16_t`. Must make sure there are 2 bytes in the buffer
uint16_t bytes_to_u16(uint8_t* buf) {
    return (static_cast<uint16_t>(buf[0]) << 8) | static_cast<uint16_t>(buf[1]);
}

// Turns two `uint8_t` into a `uint16_t`.
uint16_t bytes_to_u16(uint8_t upper, uint8_t lower) {
    return (static_cast<uint16_t>(upper) << 8) | static_cast<uint16_t>(lower);
}

// Turns two `uint8_t` (MSB-first) into a signed `int16_t`. Must make sure there are 2 bytes in the buffer
int16_t bytes_to_16(uint8_t* buf) {
    return (static_cast<int16_t>(buf[0]) << 8) | static_cast<int16_t>(buf[1]);
}

// Turns two `uint8_t` into a signed `int16_t`.
int16_t bytes_to_16(uint8_t upper, uint8_t lower) {
    return (static_cast<int16_t>(upper) << 8) | static_cast<int16_t>(lower);
}

// Turns two `uint8_t` (MSB-first) into a `float`. Must make sure there are 2 bytes in the buffer
float bytes_to_float(uint8_t* buf) {
    return static_cast<float>(bytes_to_16(buf));
}

// Turns two `uint8_t` into a `float`.
float bytes_to_float(uint8_t upper, uint8_t lower) {
    return static_cast<float>(bytes_to_16(upper, lower));
}