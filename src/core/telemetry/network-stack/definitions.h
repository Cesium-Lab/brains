#pragma once 

#include <cstdint>

// Arbitrary
const uint16_t MAX_PACKET_LENGTH = 255; 

// Raw data: MAX_PACKET_LENGTH + timestamp (4) + VID/SEQ (1) + length (2) + CRC (2)
const uint16_t MAX_RAW_PACKET_LENGTH = MAX_PACKET_LENGTH + 9;

// Interface between upper and lower network layers
struct __attribute__((packed)) packet_t {
    
    // Original data
    uint16_t length;
    etl::array<uint8_t, MAX_PACKET_LENGTH> data;
    
    // Added by packet.h (session layer)
    uint32_t timestamp_us;
    uint8_t vehicle_id;
    uint8_t sequence_number; // 6-bit counter (0-0x3F)
};

struct __attribute__((packed)) raw_packet_t {
    etl::array<uint8_t, MAX_RAW_PACKET_LENGTH> data;
    uint32_t length;

    uint16_t crc;
};

struct __attribute__((packed)) cobs_encoded_data_t {
    // Accounts for maximum COBS overhead of floor(length/254)
    // https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing
    etl::array<uint8_t, MAX_RAW_PACKET_LENGTH + MAX_RAW_PACKET_LENGTH/254 + 1> data;
    uint32_t length;
};
