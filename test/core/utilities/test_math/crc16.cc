

#include "core/utilities/math/crc16.h"



#include <unity.h>
void simple_test(void)
{
    TEST_ASSERT_EQUAL(33, 33);
}

void run_example_tests() {
    
    RUN_TEST(simple_test);
}

int main (){

    // delay(2000);
    
    UNITY_BEGIN();

    run_example_tests();

    UNITY_END();
}

