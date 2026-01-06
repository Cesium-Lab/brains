#include "core/telemetry/network-stack/PacketWizard.h"


#include <unity.h>

using namespace Cesium::Telemetry;
// void simple_test(void)
// {
//     TEST_ASSERT_EQUAL(32, 33);
// }

// void run_example_tests() {
    
//     RUN_TEST(simple_test);
// }


// Just makes sure no errors
void test_constructor() {
    PacketWizard packet_wizard;
}

////////////////////////////////////////////////////////////
//                      Bad VID
////////////////////////////////////////////////////////////

void test_bad_vid() {
    PacketWizard packet_wizard;
    
    packet_t packet();

    //     etl::array<uint8_t, MAX_DATA_LENGTH> data;
    // uint16_t length;
    
    // uint32_t timestamp_ms; // Decoded millisecond timestamp
    // uint8_t op_code;
    // uint8_t vehicle_id; // Where message came from
    // SEQ seq; // 0-3
}


int main (){
    
    UNITY_BEGIN();

    test_constructor();

    UNITY_END();
}

