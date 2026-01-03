#include "core/telemetry/network-stack/PacketWizard.h"
#include <cstring>
#include "core/isolation-layer/time.h"
#include "core/utilities/cobs.h"
#include "core/utilities/math/crc16.h"

// TODO: test and replace copies with views for ownership
namespace Cesium::Telemetry {

PacketWizard::PacketWizard(uint8_t vehicle_id)
    : _vehicle_id{vehicle_id}
{}

raw_packet_t PacketWizard::packetize(const packet_t& packet)
{
    raw_packet_t raw_packet;
    raw_packet.length = packet.length + 9;

    // Timestamp (index 0)
    raw_packet.data[0] = (packet.timestamp_ms >> 24) & 0xFF;
    raw_packet.data[1] = (packet.timestamp_ms >> 16) & 0xFF;
    raw_packet.data[2] = (packet.timestamp_ms >> 8) & 0xFF;
    raw_packet.data[3] = (packet.timestamp_ms) & 0xFF;

    // Vehicle ID (6 bits) and Sequence number (2 bits)
    raw_packet.data[4] = ( (packet.vehicle_id & 0b111111) << 2) | ((uint8_t)packet.seq & 0b11);

    // Length (2)
    raw_packet.data[5] = (packet.length >> 8) & 0xFF;
    raw_packet.data[6] = (packet.length) & 0xFF;

    // Data
    etl::copy(packet.data.begin(), packet.data.begin() + packet.length, raw_packet.data.begin() + 7);

    // CRC
    uint16_t crc = crc16xmodem(packet.data.begin(), packet.length);

    raw_packet.data[7 + packet.length] = (crc >> 8) & 0xFF;
    raw_packet.data[8 + packet.length] = (crc) & 0xFF;

    return raw_packet;
}

// Returns false if CRC did not match
bool PacketWizard::depacketize(const raw_packet_t& raw_packet, packet_t& packet)
{
    const auto& data = raw_packet.data;

    packet.timestamp_ms = (
        (uint32_t(data[0]) << 24) |
        (uint32_t(data[1]) << 16) |
        (uint32_t(data[2]) << 8) |
        (uint32_t(data[3]))
    );

    packet.vehicle_id = (
        (data[4] >> 2) & 0b00111111
    );
    
    packet.seq = (SEQ)(
        data[4] & 0x00000011
    );

    packet.length = (
        (uint16_t(data[5]) << 8) |
        (uint16_t(data[6]))
    );

    if (packet.length > MAX_DATA_LENGTH || packet.length + 9 != raw_packet.length) {
        return false;
    }

    uint16_t decoded_crc = (
        (uint16_t(data[7 + packet.length]) << 8) |
        (uint16_t(data[8 + packet.length]))
    );

    uint16_t crc = crc16xmodem(data.begin() + 7, packet.length);
    if (crc != decoded_crc)
    {
        return false;
    }

    etl::copy(data.begin() + 7, data.begin() + 7 + packet.length, packet.data.begin());

    return true;
}

} // namespace Cesium::Telemetry