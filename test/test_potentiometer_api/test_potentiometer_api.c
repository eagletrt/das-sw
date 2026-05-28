#include "unity.h"

#include "potentiometer.h"
#include "potentiometer-api.h"

#include <stdint.h>

extern struct PotentiometerHandler potentiometer_api_handler;

static uint16_t valid_value_at(uint8_t index) {
    static const uint16_t values[] = {
        0U,
        1U,
        123U,
        2048U,
        4095U,
    };

    return values[index % (uint8_t)(sizeof(values) / sizeof(values[0]))];
}

void setUp(void) {
    (void)potentiometer_api_init();
}

void tearDown(void) {
}

void test_potentiometer_api_init_should_return_ok(void) {
    enum PotentiometerReturnCode rc = potentiometer_api_init();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_OK,
        rc,
        "potentiometer_api_init() should return POTENTIOMETER_RC_OK");
}

void test_potentiometer_api_init_should_set_all_potentiometers_to_zero(void) {
    uint16_t expected_values[POTENTIOMETER_NAME_COUNT];
    uint16_t actual_values[POTENTIOMETER_NAME_COUNT];

    for (uint8_t i = 0U; i < (uint8_t)POTENTIOMETER_NAME_COUNT; i++) {
        potentiometer_api_handler.potentiometer_value[i] = valid_value_at(i + 1U);
        expected_values[i] = 0U;
    }

    enum PotentiometerReturnCode rc = potentiometer_api_init();

    for (uint8_t i = 0U; i < (uint8_t)POTENTIOMETER_NAME_COUNT; i++) {
        actual_values[i] = potentiometer_api_handler.potentiometer_value[i];
    }

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_OK,
        rc,
        "potentiometer_api_init() should return POTENTIOMETER_RC_OK");

    TEST_ASSERT_EQUAL_UINT16_ARRAY_MESSAGE(
        expected_values,
        actual_values,
        POTENTIOMETER_NAME_COUNT,
        "Each potentiometer value should be initialized to 0");
}

void test_potentiometer_api_get_value_should_return_saved_value_for_each_valid_potentiometer(void) {
    int16_t expected_values[POTENTIOMETER_NAME_COUNT];
    int16_t actual_values[POTENTIOMETER_NAME_COUNT];

    for (uint8_t i = 0U; i < (uint8_t)POTENTIOMETER_NAME_COUNT; i++) {
        uint16_t expected_value = valid_value_at(i);

        potentiometer_api_handler.potentiometer_value[i] = expected_value;
        expected_values[i] = (int16_t)expected_value;

        actual_values[i] = potentiometer_api_get_value((enum PotentiometerName)i);
    }

    TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(
        expected_values,
        actual_values,
        POTENTIOMETER_NAME_COUNT,
        "potentiometer_api_get_value() should return the saved value for each valid potentiometer");
}

void test_potentiometer_api_get_value_should_return_minus_one_for_invalid_potentiometer_count(void) {
    int16_t value = potentiometer_api_get_value(POTENTIOMETER_NAME_COUNT);

    TEST_ASSERT_EQUAL_INT16_MESSAGE(
        -1,
        value,
        "potentiometer_api_get_value(POTENTIOMETER_NAME_COUNT) should return -1");
}

void test_potentiometer_api_get_value_should_return_minus_one_for_potentiometer_after_count(void) {
    int16_t value = potentiometer_api_get_value((enum PotentiometerName)(POTENTIOMETER_NAME_COUNT + 1));

    TEST_ASSERT_EQUAL_INT16_MESSAGE(
        -1,
        value,
        "potentiometer_api_get_value() should reject potentiometer values greater than POTENTIOMETER_NAME_COUNT");
}

void test_potentiometer_api_set_value_should_accept_each_valid_potentiometer_and_valid_value(void) {
    const uint16_t valid_values[] = {
        0U,
        1U,
        123U,
        2048U,
        4095U,
    };

    enum {
        valid_value_count = sizeof(valid_values) / sizeof(valid_values[0]),
        test_case_count = POTENTIOMETER_NAME_COUNT * valid_value_count,
    };

    uint8_t return_codes[test_case_count];
    uint8_t value_update_results[test_case_count];

    uint8_t test_case_index = 0U;

    for (uint8_t potentiometer_index = 0U;
         potentiometer_index < (uint8_t)POTENTIOMETER_NAME_COUNT;
         potentiometer_index++) {

        for (uint8_t value_index = 0U; value_index < (uint8_t)valid_value_count; value_index++) {
            uint16_t expected_value = valid_values[value_index];

            enum PotentiometerReturnCode rc = potentiometer_api_set_value(
                (enum PotentiometerName)potentiometer_index,
                expected_value);

            return_codes[test_case_index] = (uint8_t)rc;

            value_update_results[test_case_index] =
                (potentiometer_api_handler.potentiometer_value[potentiometer_index] == expected_value)
                    ? 1U
                    : 0U;

            test_case_index++;
        }
    }

    TEST_ASSERT_EACH_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_OK,
        return_codes,
        test_case_count,
        "potentiometer_api_set_value() should return OK for each valid potentiometer and valid value");

    TEST_ASSERT_EACH_EQUAL_UINT8_MESSAGE(
        1U,
        value_update_results,
        test_case_count,
        "potentiometer_api_set_value() should update the requested potentiometer value");
}

void test_potentiometer_api_set_value_should_accept_min_adc_value_0(void) {
    enum PotentiometerName potentiometer = POTENTIOMETER_NAME_1;

    enum PotentiometerReturnCode rc = potentiometer_api_set_value(
        potentiometer,
        0U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_OK,
        rc,
        "potentiometer_api_set_value(..., 0) should return POTENTIOMETER_RC_OK");

    TEST_ASSERT_EQUAL_UINT16_MESSAGE(
        0U,
        potentiometer_api_handler.potentiometer_value[potentiometer],
        "0 should be accepted as valid ADC value");
}

void test_potentiometer_api_set_value_should_accept_max_adc_value_4095(void) {
    enum PotentiometerName potentiometer = POTENTIOMETER_NAME_1;

    enum PotentiometerReturnCode rc = potentiometer_api_set_value(
        potentiometer,
        4095U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_OK,
        rc,
        "potentiometer_api_set_value(..., 4095) should return POTENTIOMETER_RC_OK");

    TEST_ASSERT_EQUAL_UINT16_MESSAGE(
        4095U,
        potentiometer_api_handler.potentiometer_value[potentiometer],
        "4095 should be accepted as valid ADC value");
}

void test_potentiometer_api_set_value_should_reject_adc_value_4096(void) {
    enum PotentiometerName potentiometer = POTENTIOMETER_NAME_1;

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

void test_potentiometer_api_set_value_should_reject_adc_value_greater_than_4096(void) {
    enum PotentiometerName potentiometer = POTENTIOMETER_NAME_1;

    potentiometer_api_handler.potentiometer_value[potentiometer] = 2048U;

    enum PotentiometerReturnCode rc = potentiometer_api_set_value(
        potentiometer,
        5000U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_ERROR,
        rc,
        "potentiometer_api_set_value() should reject values greater than 4095");

    TEST_ASSERT_EQUAL_UINT16_MESSAGE(
        2048U,
        potentiometer_api_handler.potentiometer_value[potentiometer],
        "Invalid ADC value should not change the previous potentiometer value");
}

void test_potentiometer_api_set_value_should_reject_invalid_potentiometer_count(void) {
    uint16_t expected_values[POTENTIOMETER_NAME_COUNT];
    uint16_t actual_values[POTENTIOMETER_NAME_COUNT];

    for (uint8_t i = 0U; i < (uint8_t)POTENTIOMETER_NAME_COUNT; i++) {
        uint16_t value = valid_value_at(i + 1U);

        potentiometer_api_handler.potentiometer_value[i] = value;
        expected_values[i] = value;
    }

    enum PotentiometerReturnCode rc = potentiometer_api_set_value(
        POTENTIOMETER_NAME_COUNT,
        1000U);

    for (uint8_t i = 0U; i < (uint8_t)POTENTIOMETER_NAME_COUNT; i++) {
        actual_values[i] = potentiometer_api_handler.potentiometer_value[i];
    }

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_ERROR,
        rc,
        "potentiometer_api_set_value(POTENTIOMETER_NAME_COUNT, ...) should return POTENTIOMETER_RC_ERROR");

    TEST_ASSERT_EQUAL_UINT16_ARRAY_MESSAGE(
        expected_values,
        actual_values,
        POTENTIOMETER_NAME_COUNT,
        "Invalid potentiometer should not modify any valid potentiometer value");
}

void test_potentiometer_api_set_value_should_reject_potentiometer_after_count(void) {
    uint16_t expected_values[POTENTIOMETER_NAME_COUNT];
    uint16_t actual_values[POTENTIOMETER_NAME_COUNT];

    for (uint8_t i = 0U; i < (uint8_t)POTENTIOMETER_NAME_COUNT; i++) {
        uint16_t value = valid_value_at(i + 1U);

        potentiometer_api_handler.potentiometer_value[i] = value;
        expected_values[i] = value;
    }

    enum PotentiometerReturnCode rc = potentiometer_api_set_value(
        (enum PotentiometerName)(POTENTIOMETER_NAME_COUNT + 1),
        1000U);

    for (uint8_t i = 0U; i < (uint8_t)POTENTIOMETER_NAME_COUNT; i++) {
        actual_values[i] = potentiometer_api_handler.potentiometer_value[i];
    }

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_ERROR,
        rc,
        "potentiometer_api_set_value() should reject potentiometer values greater than POTENTIOMETER_NAME_COUNT");

    TEST_ASSERT_EQUAL_UINT16_ARRAY_MESSAGE(
        expected_values,
        actual_values,
        POTENTIOMETER_NAME_COUNT,
        "Invalid potentiometer should not modify any valid potentiometer value");
}

void test_potentiometer_api_set_value_should_reject_invalid_potentiometer_and_invalid_value(void) {
    enum PotentiometerReturnCode rc = potentiometer_api_set_value(
        POTENTIOMETER_NAME_COUNT,
        4096U);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        POTENTIOMETER_RC_ERROR,
        rc,
        "potentiometer_api_set_value() should reject invalid potentiometer and invalid value");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_potentiometer_api_init_should_return_ok);
    RUN_TEST(test_potentiometer_api_init_should_set_all_potentiometers_to_zero);
    RUN_TEST(test_potentiometer_api_get_value_should_return_saved_value_for_each_valid_potentiometer);
    RUN_TEST(test_potentiometer_api_get_value_should_return_minus_one_for_invalid_potentiometer_count);
    RUN_TEST(test_potentiometer_api_get_value_should_return_minus_one_for_potentiometer_after_count);
    RUN_TEST(test_potentiometer_api_set_value_should_accept_each_valid_potentiometer_and_valid_value);
    RUN_TEST(test_potentiometer_api_set_value_should_accept_min_adc_value_0);
    RUN_TEST(test_potentiometer_api_set_value_should_accept_max_adc_value_4095);
    RUN_TEST(test_potentiometer_api_set_value_should_reject_adc_value_4096);
    RUN_TEST(test_potentiometer_api_set_value_should_reject_adc_value_greater_than_4096);
    RUN_TEST(test_potentiometer_api_set_value_should_reject_invalid_potentiometer_count);
    RUN_TEST(test_potentiometer_api_set_value_should_reject_potentiometer_after_count);
    RUN_TEST(test_potentiometer_api_set_value_should_reject_invalid_potentiometer_and_invalid_value);

    return UNITY_END();
}