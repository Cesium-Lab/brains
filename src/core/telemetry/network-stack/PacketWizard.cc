#include "core/telemetry/network-stack/PacketWizard.h"
#include <cstring>
#include "core/isolation-layer/time.h"
#include "core/utilities/cobs.h"
#include "core/utilities/math/crc16.h"

// TODO: test and replace copies with views for ownership
namespace Cesium::Telemetry {

PacketWizard::PacketWizard() {}


packet_codes_t packetize(const packet_t& packet_in, raw_packet_t& raw_packet_out) {

    raw_packet_out.length = packet_in.length + 10;

    // Timestamp (index 0)
    raw_packet_out.data[0] = (packet_in.timestamp_ms >> 24) & 0xFF;
    raw_packet_out.data[1] = (packet_in.timestamp_ms >> 16) & 0xFF;
    raw_packet_out.data[2] = (packet_in.timestamp_ms >> 8) & 0xFF;
    raw_packet_out.data[3] = (packet_in.timestamp_ms) & 0xFF;

    // Vehicle ID (6 bits) and Sequence number (2 bits)
    if (packet_in.vehicle_id > MAX_VEHICLE_ID) {
        return VEHICLE_ID_TOO_LARGE;
    }

    if (packet_in.seq > MAX_SEQ_NUM) {
        return SEQ_NUM_TOO_LARGE;
    }

    raw_packet_out.data[4] = ( (packet_in.vehicle_id & 0b111111) << 2) | ((uint8_t)packet_in.seq & 0b11);

    // OP Code
    raw_packet_out.data[5] = packet_in.op_code;

    // Length (2)
    raw_packet_out.data[6] = (packet_in.length >> 8) & 0xFF;
    raw_packet_out.data[7] = (packet_in.length) & 0xFF;

    // Data
    etl::copy(packet_in.data.begin(), packet_in.data.begin() + packet_in.length, 
              raw_packet_out.data.begin() + 7);

    // CRC
    uint16_t crc = crc16xmodem(packet_in.data.begin(), packet_in.length);

    raw_packet_out.data[8 + packet_in.length] = (crc >> 8) & 0xFF;
    raw_packet_out.data[9 + packet_in.length] = (crc) & 0xFF;

}


packet_codes_t depacketize(const raw_packet_t& raw_packet_in, packet_t& packet_out) {
    const auto& data = raw_packet_in.data;

    packet_out.timestamp_ms = (
        (uint32_t(data[0]) << 24) |
        (uint32_t(data[1]) << 16) |
        (uint32_t(data[2]) << 8) |
        (uint32_t(data[3]))
    );

    packet_out.vehicle_id = (
        (data[4] >> 2) & 0b00111111
    );
    
    packet_out.seq = (SEQ)(
        data[4] & 0x00000011
    );

    packet_out.length = (
        (uint16_t(data[5]) << 8) |
        (uint16_t(data[6]))
    );

    if (packet_out.length > MAX_DATA_LENGTH || packet_out.length + 9 != raw_packet_in.length) {
        return packet_codes_t::DATA_LENGTH_MISMATCH;
    }

    if (packet_out.length + 9 != raw_packet_in.length) {
        return packet_codes_t::BAD_DATA_LENGTH;
    }

    uint16_t decoded_crc = (
        (uint16_t(data[7 + packet_out.length]) << 8) |
        (uint16_t(data[8 + packet_out.length]))
    );

    uint16_t crc = crc16xmodem(data.begin() + 7, packet_out.length);
    if (crc != decoded_crc)
    {
        return packet_codes_t::CRC_MISMATCH;
    }

    etl::copy(data.begin() + 7, data.begin() + 7 + packet_out.length, packet_out.data.begin());

    return packet_codes_t::SUCCESS;
}

} // namespace Cesium::Telemetry