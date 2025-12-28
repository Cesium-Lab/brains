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

////////////////////////////////////////////////////////////
//                      Constructor                       //
////////////////////////////////////////////////////////////

void test_constructor() {
    PacketWizard packet_wizard(0);
    // TEST_ASSERT_EQUAL(0, packet_wizard.get_sequence_number());

}



int main (){
    
    UNITY_BEGIN();

    test_constructor();

    UNITY_END();
}

