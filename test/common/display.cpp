#include "display.hpp"

static void test_setColumn() {
    auto lc = LedController<4,1>(get_conf_SPI());

    lc.setColumn(0,7,0b11111111);
    sakurajin::ByteBlock r = ByteBlock::rotate180({0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001});

    lc.setColumn(1,0,0b11111111);
    sakurajin::ByteBlock s = {0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001};

    TEST_ASSERT(lc.getSegmentData(0) == r);
    TEST_ASSERT(lc.getSegmentData(1) == s);
}

static void test_setLED(){
    auto lc = LedController<4,1>(get_conf_SPI());

    lc.setLed(0,0,0,true);
    sakurajin::ByteBlock a = ByteBlock::rotate180({0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b10000000});

    lc.setLed(1,0,4,true);
    sakurajin::ByteBlock b = ByteBlock::rotate180({0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00001000});

    lc.setLed(2,2,0,true);
    sakurajin::ByteBlock c = ByteBlock::rotate180({0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b10000000,0b00000000,0b00000000});

    TEST_ASSERT(lc.getSegmentData(0) == a);
    TEST_ASSERT(lc.getSegmentData(1) == b);
    TEST_ASSERT(lc.getSegmentData(2) == c);

}

void run_display_tests(){
    RUN_TEST(test_setColumn);
    RUN_TEST(test_setLED);
}