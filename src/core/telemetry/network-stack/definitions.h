#pragma once 

#include <cstdint>

// Arbitrary
const uint16_t MAX_DATA_LENGTH = 255; 

// Raw data: MAX_PACKET_LENGTH + timestamp (4) + VID/SEQ (1) + length (2) + CRC (2)
const uint16_t MAX_RAW_PACKET_LENGTH = MAX_DATA_LENGTH + 9;

// Held in 2 bytes
enum SEQ {
    SINGLE = 0,
    START = 1,
    MIDDLE = 2,
    END = 3
};

// Decoded output from PacketWizard to TelemetryServer
struct __attribute__((packed)) packet_t {
    
    // Original data
    etl::array<uint8_t, MAX_DATA_LENGTH> data;
    uint16_t length;
    
    uint32_t timestamp_ms; // Decoded millisecond timestamp
    uint8_t vehicle_id; // Where message came from
    SEQ seq; // 6-bit counter: 0-64 (0x3F)
};

// Raw packet bytes
struct __attribute__((packed)) raw_packet_t {
    etl::array<uint8_t, MAX_RAW_PACKET_LENGTH> data;
    uint32_t length;
};

// TODO: later?
// struct __attribute__((packed)) cobs_encoded_data_t {
//     // Accounts for maximum COBS overhead of ceil(length/254)
//     // https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing
//     etl::array<uint8_t, MAX_RAW_PACKET_LENGTH + MAX_RAW_PACKET_LENGTH/254 + 1> data;
//     uint32_t length;
// };
