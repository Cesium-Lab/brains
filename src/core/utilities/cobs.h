///
/// \file 				CobsTranscoder.hpp
/// \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
/// \edited             Colin Skinner <colin.skinner@g.ucla.edu>
/// \created			2017-06-20
/// \last-modified		
/// \brief 				Contains the CobsTranscoder class.
/// \details

#pragma once

// System includes
#include <vector>
// #include <Arduino.h>
#include <cstdint>
// Local includes

namespace Cesium {
class CobsTranscoder {

public:

    enum class DecodeStatus {
        SUCCESS,
        ERROR_ZERO_BYTE_NOT_EXPECTED
    };

    /// \details    The encoding process cannot fail.
    static bool Encode(
            const std::vector<uint8_t> &rawData,
            std::vector<uint8_t> &encodedData);

    /// \brief      Decode data using "Consistent Overhead Byte Stuffing" (COBS).
    /// \details    Provided encodedData is expected to be a single, valid COBS encoded packet. If not, method
    ///             will return #DecodeStatus::ERROR_ZERO_BYTE_NOT_EXPECTED.
    ///             #decodedData is emptied of any pre-existing data. If the decode fails, decodedData is left empty.
    static bool Decode(const std::vector<uint8_t> &encodedData, std::vector<uint8_t> &decodedData);

};

} // namespace Cesium