#include "unity.h"

#include "irts.h"
#include "irts-api.h"

#include <stdint.h>

extern struct IrtsHandler irts_api_handler;

void setUp(void) {
    (void)irts_api_init();
}

void tearDown(void) {
}

void test_irts_api_init_should_return_ok_and_set_all_irts_to_zero(void) {
    float expected_temperature_left;
    float expected_temperature_right;

    irts_api_handler.left_temperature = 1;
    irts_api_handler.right_temperature = 1;

    expected_temperature_left = 0U;
    expected_temperature_right = 0U;

    enum IrtsReturnCode rc = irts_api_init();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        IRTS_RC_OK,
        rc,
        "irts_api_init() should return IRTS_RC_OK");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        expected_temperature_left,
        irts_api_handler.left_temperature,
        "irts_api_init() should return IRTS_RC_OK");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        expected_temperature_right,
        irts_api_handler.right_temperature,
        "irts_api_init() should return IRTS_RC_OK");
}

void test_irts_api_get_temperature_should_return_saved_temperature(void) {
    enum IrtsName irts = IRTS_NAME_LEFT;

    irts_api_handler.left_temperature = 1;

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        1,
        irts_api_get_temperature(irts),
        "irts_api_get_temperature() should return the saved temperature for each valid irts");
}

void test_irts_api_get_temperature_should_return_minus_one_for_invalid_irts_count(void) {
    float temperature = irts_api_get_temperature(IRTS_NAME_COUNT);

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        -1,
        temperature,
        "irts_api_get_temperature(IRTS_NAME_COUNT) should return -1");
}

void test_irts_api_set_temperature_should_update_temperature_for_valid_input(void) {
    enum IrtsName irts = IRTS_NAME_LEFT;

    enum IrtsReturnCode rc = irts_api_set_temperature(
        irts,
        1000U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        IRTS_RC_OK,
        rc,
        "feedback_api_set_state() should return FEEDBACK_RC_OK for valid input");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        1000U,
        irts_api_handler.left_temperature,
        "irts_api_set_temperature() should update the requested irts temperature");
}

void test_irts_api_set_temperature_should_return_error_and_reject_invalid_irts_count(void) {
    float expected_temperatures[IRTS_NAME_COUNT];
    float temperature = 1;

    for (enum IrtsName irts = 0; irts < IRTS_NAME_COUNT; ++irts) {
        expected_temperatures[irts] = temperature;
    }
    irts_api_handler.left_temperature = temperature;
    irts_api_handler.right_temperature = temperature;

    enum IrtsReturnCode rc = irts_api_set_temperature(
        IRTS_NAME_COUNT,
        1000U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        IRTS_RC_ERROR,
        rc,
        "irts_api_set_temperature(IRTS_NAME_COUNT, ...) should return IRTS_RC_ERROR");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        temperature,
        irts_api_handler.left_temperature,
        "Invalid irts should not modify any valid irts temperature");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        temperature,
        irts_api_handler.right_temperature,
        "Invalid irts should not modify any valid irts temperature");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_irts_api_init_should_return_ok_and_set_all_irts_to_zero);
    RUN_TEST(test_irts_api_get_temperature_should_return_saved_temperature);
    RUN_TEST(test_irts_api_get_temperature_should_return_minus_one_for_invalid_irts_count);
    RUN_TEST(test_irts_api_set_temperature_should_update_temperature_for_valid_input);
    RUN_TEST(test_irts_api_set_temperature_should_return_error_and_reject_invalid_irts_count);

    return UNITY_END();
}