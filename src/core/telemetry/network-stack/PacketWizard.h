#pragma once

#include <cstdint>
#include <etl/array.h>
#include "core/telemetry/network-stack/definitions.h"
// FORGOT OP CODES AAA AND TEST
namespace Cesium::Telemetry {

class PacketWizard {

public:
    PacketWizard(uint8_t vehicle_id);
    raw_packet_t packetize(const packet_t& packet);
    static bool depacketize(const raw_packet_t& raw_packet, packet_t& packet);
    
    inline uint8_t get_vehicle_id() { return _vehicle_id; }

private:
    uint8_t _vehicle_id;
};

} // namespace Cesium::Telemetry

