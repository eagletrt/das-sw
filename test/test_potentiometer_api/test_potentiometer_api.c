#include "unity.h"

#include "potentiometer.h"
#include "potentiometer-api.h"

#include <stdint.h>

extern struct PotentiometerHandler potentiometer_api_handler;

void setUp(void) {
    (void)potentiometer_api_init();
}

void tearDown(void) {
}

void test_potentiometer_api_init_should_return_ok_and_set_all_potentiometers_to_zero(void) {
    uint16_t expected_values[POTENTIOMETER_NAME_COUNT];

    for (uint8_t i = 0U; i < (uint8_t)POTENTIOMETER_NAME_COUNT; i++) {
        potentiometer_api_handler.potentiometer_value[i] = 1;
        expected_values[i] = 0U;
    }

    enum PotentiometerReturnCode rc = potentiometer_api_init();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_OK,
        rc,
        "potentiometer_api_init() should return POTENTIOMETER_RC_OK");

    TEST_ASSERT_EQUAL_UINT16_ARRAY_MESSAGE(
        expected_values,
        potentiometer_api_handler.potentiometer_value,
        POTENTIOMETER_NAME_COUNT,
        "Each potentiometer value should be initialized to 0");
}

void test_potentiometer_api_get_value_should_return_saved_value(void) {
    enum PotentiometerName potentiometer = POTENTIOMETER_NAME_LEFT;
    
    potentiometer_api_handler.potentiometer_value[potentiometer] = 1;

    TEST_ASSERT_EQUAL_INT16_MESSAGE(
        1,
        potentiometer_api_get_value(potentiometer),
        "potentiometer_api_get_value() should return the saved value for each valid potentiometer");
}

void test_potentiometer_api_get_value_should_return_minus_one_for_invalid_potentiometer_count(void) {
    int16_t value = potentiometer_api_get_value(POTENTIOMETER_NAME_COUNT);

    TEST_ASSERT_EQUAL_INT16_MESSAGE(
        -1,
        value,
        "potentiometer_api_get_value(POTENTIOMETER_NAME_COUNT) should return -1");
}

void test_potentiometer_api_set_value_should_update_value_for_valid_input(void) {
    enum PotentiometerName potentiometer = 0U;

    enum PotentiometerReturnCode rc = potentiometer_api_set_value(
        potentiometer,
        1000U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_OK,
        rc,
        "feedback_api_set_state() should return FEEDBACK_RC_OK for valid input");

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        1000U,
        potentiometer_api_handler.potentiometer_value[potentiometer],
        "potentiometer_api_set_value() should update the requested potentiometer value");
}

void test_potentiometer_api_set_value_should_return_error_and_reject_invalid_adc_value(void) {
    enum PotentiometerName potentiometer = POTENTIOMETER_NAME_LEFT;

    potentiometer_api_handler.potentiometer_value[potentiometer] = 1234U;

    enum PotentiometerReturnCode rc = potentiometer_api_set_value(
        potentiometer,
        4096U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_ERROR,
        rc,
        "potentiometer_api_set_value(..., 4096) should return POTENTIOMETER_RC_ERROR");

    TEST_ASSERT_EQUAL_UINT16_MESSAGE(
        1234U,
        potentiometer_api_handler.potentiometer_value[potentiometer],
        "Invalid ADC value should not change the previous potentiometer value");
}

void test_potentiometer_api_set_value_should_return_error_and_reject_invalid_potentiometer_count(void) {
    uint16_t expected_values[POTENTIOMETER_NAME_COUNT];

    for (enum PotentiometerName potentiometer = 0; potentiometer < POTENTIOMETER_NAME_COUNT; ++potentiometer) {
        uint16_t value = 1;

        potentiometer_api_handler.potentiometer_value[potentiometer] = value;
        expected_values[potentiometer] = value;
    }

    enum PotentiometerReturnCode rc = potentiometer_api_set_value(
        POTENTIOMETER_NAME_COUNT,
        1000U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_ERROR,
        rc,
        "potentiometer_api_set_value(POTENTIOMETER_NAME_COUNT, ...) should return POTENTIOMETER_RC_ERROR");

    TEST_ASSERT_EQUAL_UINT16_ARRAY_MESSAGE(
        expected_values,
        potentiometer_api_handler.potentiometer_value,
        POTENTIOMETER_NAME_COUNT,
        "Invalid potentiometer should not modify any valid potentiometer value");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_potentiometer_api_init_should_return_ok_and_set_all_potentiometers_to_zero);
    RUN_TEST(test_potentiometer_api_get_value_should_return_saved_value);
    RUN_TEST(test_potentiometer_api_get_value_should_return_minus_one_for_invalid_potentiometer_count);
    RUN_TEST(test_potentiometer_api_set_value_should_update_value_for_valid_input);
    RUN_TEST(test_potentiometer_api_set_value_should_return_error_and_reject_invalid_adc_value);
    RUN_TEST(test_potentiometer_api_set_value_should_return_error_and_reject_invalid_potentiometer_count);

    return UNITY_END();
}