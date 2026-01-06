#pragma once

#include <cstdint>
#include <etl/array.h>
#include "core/telemetry/network-stack/definitions.h"
// FORGOT OP CODES AAA AND TEST
namespace Cesium::Telemetry {

enum packet_codes_t {
    SUCCESS,
    VEHICLE_ID_TOO_LARGE,
    SEQ_NUM_TOO_LARGE,
    CRC_MISMATCH,
    DATA_LENGTH_MISMATCH,
    BAD_DATA_LENGTH
};

class PacketWizard {
public:
    PacketWizard();
    static packet_codes_t packetize(const packet_t& packet_in, raw_packet_t& raw_packet_out);
    static packet_codes_t depacketize(const raw_packet_t& raw_packet_in, packet_t& packet_out);
};

} // namespace Cesium::Telemetry

