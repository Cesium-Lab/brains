/*
Session layer adds:
- timestamp
- Vehicle ID (VID)
- sequence number


Deals with:
- ACKs
- COBS?

*/
#pragma once

#include <cstdint>
#include <etl/array.h>
#include "core/telemetry/network-stack/definitions.h"

namespace Cesium::Telemetry {

class PacketWizard {

public:
    PacketWizard(uint8_t vehicle_id);
    packet_t packetize(etl::array<uint8_t, MAX_PACKET_LENGTH> data, uint16_t length);
    static raw_packet_t encode(packet_t packet);
    static bool decode(etl::array<uint8_t, MAX_PACKET_LENGTH> data, packet_t& packet);
    
    // static cobs_encoded_data_t add_cobs(packet_t packet);
    // static raw_packet_t remove_cobs(cobs_encoded_data_t data);

    inline uint8_t get_sequence_number() { return _current_sequence_number; }

private:
    uint8_t _current_sequence_number;
    uint8_t _vehicle_id;
};

} // namespace Cesium::Telemetry

