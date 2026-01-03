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
    //etl::array<uint8_t, MAX_DATA_LENGTH> data, 
                    //    uint16_t length, uint32_t timestamp_ms, uint8_t seq = SEQ::SINGLE
    raw_packet_t packetize(const packet_t& packet);
    static raw_packet_t encode(packet_t packet);
    static bool decode(const raw_packet_t& raw_packet, packet_t& packet);
    
    inline uint8_t get_vehicle_id() { return _vehicle_id; }

private:
    uint8_t _vehicle_id;
};

} // namespace Cesium::Telemetry

