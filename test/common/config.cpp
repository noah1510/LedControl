#include "config.hpp"

static void check_valid_configs() {
    TEST_ASSERT(get_conf().isValid());
    TEST_ASSERT(get_conf_SPI().isValid());
    TEST_ASSERT(get_multi_conf().isValid());
    TEST_ASSERT(get_multi_conf_SPI().isValid());
}

static void check_invalid_configs() {

    sakurajin::controller_configuration<1,2> c1;
    TEST_ASSERT_FALSE_MESSAGE(c1.isValid(),"p1");

    c1.useHardwareSpi = true;
    c1.virtual_multi_row = false;
    TEST_ASSERT_FALSE_MESSAGE(c1.isValid(),"p2");

    c1.row_SPI_CS[0] = 1;
    TEST_ASSERT_FALSE_MESSAGE(c1.isValid(),"p3");

    c1.row_SPI_CS[1] = 1;
    TEST_ASSERT_FALSE_MESSAGE(c1.isValid(),"p4");

    c1.row_SPI_CS[1] = 2;
    TEST_ASSERT_TRUE_MESSAGE(c1.isValid(),"p5");

}

void run_config_tests() {
    RUN_TEST(check_valid_configs);
    RUN_TEST(check_invalid_configs);
}