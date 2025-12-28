#include "core/telemetry/network-stack/PacketWizard.h"
#include <cstring>
#include "core/isolation-layer/time.h"
#include "core/utilities/cobs.h"
#include "core/utilities/math/crc16.h"

namespace Cesium::Telemetry {

PacketWizard::PacketWizard(uint8_t vehicle_id)
    : _current_sequence_number{0}, _vehicle_id{vehicle_id}
{}

packet_t PacketWizard::packetize(etl::array<uint8_t, MAX_PACKET_LENGTH> data, uint16_t length)
{
    uint32_t time = Cesium::Time::get_unix_microseconds();

    packet_t packet;
    packet.data = data;
    packet.length = length;
    packet.timestamp_us = Cesium::Time::get_unix_microseconds();
    packet.vehicle_id = _vehicle_id;
    packet.sequence_number = _current_sequence_number;

    // Increment sequence number
    _current_sequence_number = (_current_sequence_number == 0x3F 
        ?  0
        : _current_sequence_number + 1);

    return packet;
}

raw_packet_t PacketWizard::encode(packet_t packet)
{
    raw_packet_t raw_packet;
    raw_packet.length = 7 + packet.length + 2; // Header (7), length, CRC (2)

    // Timestamp (index 0)
    raw_packet.data[0] = (packet.timestamp_us >> 24) & 0xFF;
    raw_packet.data[1] = (packet.timestamp_us >> 16) & 0xFF;
    raw_packet.data[2] = (packet.timestamp_us >> 8) & 0xFF;
    raw_packet.data[3] = (packet.timestamp_us) & 0xFF;

    // Vehicle ID (2 bits) and Sequence number (6 bits)
    raw_packet.data[4] = (packet.vehicle_id << 6) | (packet.sequence_number & 0x3F);

    // Length (2)
    raw_packet.data[5] = (packet.length >> 8) & 0xFF;
    raw_packet.data[6] = (packet.length) & 0xFF;

    // Data
    etl::copy(packet.data.begin(), packet.data.begin() + packet.length, raw_packet.data.begin() + 7);

    // CRC
    raw_packet.crc = crc16xmodem(packet.data.begin(), packet.length);

    raw_packet.data[7 + packet.length] = (raw_packet.crc >> 8) & 0xFF;
    raw_packet.data[8 + packet.length] = (raw_packet.crc) & 0xFF;

    return raw_packet;
}

// Returns false if CRC did not match
bool PacketWizard::decode(etl::array<uint8_t, MAX_PACKET_LENGTH> data, packet_t& packet)
{
    packet.timestamp_us = (
        (data[0] << 24) |
        (data[1] << 16) |
        (data[2] << 8) |
        (data[3])
    );

    packet.vehicle_id = (
        (data[4] >> 6) & 0b11
    );
    
    packet.sequence_number = (
        data[4] & 0x3F
    );

    packet.length = (
        (data[5] << 8) |
        (data[6])
    );

    uint16_t decoded_crc = (
        (data[7 + packet.length] << 8) |
        (data[8 + packet.length])
    );

    uint16_t crc = crc16xmodem(data.begin(), packet.length);
    if (crc != decoded_crc)
    {
        return false;
    }

    etl::copy(data.begin() + 7, data.begin() + packet.length, packet.data.begin());

    return true;
}

// cobs_encoded_data_t PacketWizard::add_cobs(packet_t packet)
// {
//     cobs_encoded_data_t result;
// }

} // namespace Cesium::Telemetry