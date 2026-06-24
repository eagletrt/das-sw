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
    double expected_value_left;
    double expected_value_right;

    irts_api_handler.left_temperature = 1;
    irts_api_handler.right_temperature = 1;

    expected_value_left = 0U;
    expected_value_right = 0U;

    enum IrtsReturnCode rc = irts_api_init();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        IRTS_RC_OK,
        rc,
        "irts_api_init() should return IRTS_RC_OK");

    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(
        expected_value_left,
        irts_api_handler.left_temperature,
        "irts_api_init() should return IRTS_RC_OK");

    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(
        expected_value_right,
        irts_api_handler.right_temperature,
        "irts_api_init() should return IRTS_RC_OK");
}

void test_irts_api_get_value_should_return_saved_value(void) {
    enum IrtsName irts = IRTS_NAME_LEFT;

    irts_api_handler.left_temperature = 1;

    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(
        1,
        irts_api_get_value(irts),
        "irts_api_get_value() should return the saved value for each valid irts");
}

void test_irts_api_get_value_should_return_minus_one_for_invalid_irts_count(void) {
    double value = irts_api_get_value(IRTS_NAME_COUNT);

    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(
        -1,
        value,
        "irts_api_get_value(IRTS_NAME_COUNT) should return -1");
}

void test_irts_api_set_value_should_update_value_for_valid_input(void) {
    enum IrtsName irts = IRTS_NAME_LEFT;

    enum IrtsReturnCode rc = irts_api_set_value(
        irts,
        1000U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        IRTS_RC_OK,
        rc,
        "feedback_api_set_state() should return FEEDBACK_RC_OK for valid input");

    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(
        1000U,
        irts_api_handler.left_temperature,
        "irts_api_set_value() should update the requested irts value");
}

void test_irts_api_set_value_should_return_error_and_reject_invalid_irts_count(void) {
    double expected_values[IRTS_NAME_COUNT];
    double value = 1;

    for (enum IrtsName irts = 0; irts < IRTS_NAME_COUNT; ++irts) {
        expected_values[irts] = value;
    }
    irts_api_handler.left_temperature = value;
    irts_api_handler.right_temperature = value;

    enum IrtsReturnCode rc = irts_api_set_value(
        IRTS_NAME_COUNT,
        1000U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        IRTS_RC_ERROR,
        rc,
        "irts_api_set_value(IRTS_NAME_COUNT, ...) should return IRTS_RC_ERROR");

    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(
        value,
        irts_api_handler.left_temperature,
        "Invalid irts should not modify any valid irts value");

    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(
        value,
        irts_api_handler.right_temperature,
        "Invalid irts should not modify any valid irts value");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_irts_api_init_should_return_ok_and_set_all_irts_to_zero);
    RUN_TEST(test_irts_api_get_value_should_return_saved_value);
    RUN_TEST(test_irts_api_get_value_should_return_minus_one_for_invalid_irts_count);
    RUN_TEST(test_irts_api_set_value_should_update_value_for_valid_input);
    RUN_TEST(test_irts_api_set_value_should_return_error_and_reject_invalid_irts_count);

    return UNITY_END();
}