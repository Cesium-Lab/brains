

#include "core/utilities/math/crc16.h"


// #include <gtest/gtest.h>
// TEST(fix, fix) {
//     EXPECT_EQ(33,23);
// };

// int main()
// {
//     ::testing::InitGoogleTest();
//     // if you plan to use GMock, replace the line above with
//     // ::testing::InitGoogleMock(&argc, argv);

//     if (RUN_ALL_TESTS())
//     ;

//     // Always return zero-code and allow PlatformIO to parse results
//     return 0;
// }


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

