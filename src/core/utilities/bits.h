#pragma once 

#include <stdint.h>

// Turns two  `uint8_t` (MSB-first) into a `uint16_t`. Must make sure there are 2 bytes in the buffer
uint16_t bytes_to_u16(uint8_t* buf);

// Turns two `uint8_t` into a `uint16_t`.
uint16_t bytes_to_u16(uint8_t upper, uint8_t lower);

// Turns two `uint8_t` (MSB-first) into a signed `int16_t`. Must make sure there are 2 bytes in the buffer
int16_t bytes_to_16(uint8_t* buf);

// Turns two `uint8_t` into a signed `int16_t`.
int16_t bytes_to_16(uint8_t upper, uint8_t lower);

// Turns two `uint8_t` (MSB-first) into a `float`. Must make sure there are 2 bytes in the buffer
float bytes_to_float(uint8_t* buf);

// Turns two `uint8_t` into a `float`.
float bytes_to_float(uint8_t upper, uint8_t lower);