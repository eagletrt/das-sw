#include "unity.h"

#include "acquisinator.h"
#include "acquisinator-api.h"

#include <stdint.h>

extern struct AcquisinatorHandler acquisinator_api_handler;

void setUp(void) {
    (void)acquisinator_api_init();
}

void tearDown(void) {
}

void test_acquisinator_api_init_should_return_ok_and_set_all_acquisinators_to_zero(void) {
    struct AcquisinatorStrainGauge expected_values[ACQUISINATOR_NAME_COUNT];

    for (uint8_t i = 0U; i < (uint8_t)ACQUISINATOR_NAME_COUNT; i++) {
        acquisinator_api_handler.strain_gauges[i].first = 1;
        acquisinator_api_handler.strain_gauges[i].second = 1;

        expected_values[i].first = 0U;
        expected_values[i].second = 0U;
    }

    enum AcquisinatorReturnCode rc = acquisinator_api_init();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        ACQUISINATOR_RC_OK,
        rc,
        "acquisinator_api_init() should return ACQUISINATOR_RC_OK");

    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(
        expected_values,
        acquisinator_api_handler.strain_gauges,
        ACQUISINATOR_NAME_COUNT,
        "Each acquisinator value should be initialized to 0");
}

void test_acquisinator_api_get_values_should_return_saved_value(void) {
    enum AcquisinatorName acquisinator = ACQUISINATOR_NAME_FIRST;

    acquisinator_api_handler.strain_gauges[acquisinator].first = 1;
    acquisinator_api_handler.strain_gauges[acquisinator].second = 1;

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        1,
        acquisinator_api_get_values(acquisinator).first,
        "acquisinator_api_get_values() should return the saved value for each valid acquisinator");
}

void test_acquisinator_api_get_values_should_return_uint32_max_for_invalid_acquisinator_count(void) {
    struct AcquisinatorStrainGauge strain_gauges = acquisinator_api_get_values(ACQUISINATOR_NAME_COUNT);

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        UINT32_MAX,
        strain_gauges.first,
        "acquisinator_api_get_values(ACQUISINATOR_NAME_COUNT) should return uint32_max");
}

void test_acquisinator_api_set_values_should_update_value_for_valid_input(void) {
    enum AcquisinatorName acquisinator = 0U;

    enum AcquisinatorReturnCode rc = acquisinator_api_set_values(
        acquisinator,
        (struct AcquisinatorStrainGauge){.first = 100.0f, .second = 100.0f});

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        ACQUISINATOR_RC_OK,
        rc,
        "feedback_api_set_state() should return FEEDBACK_RC_OK for valid input");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        100.0f,
        acquisinator_api_handler.strain_gauges[acquisinator].first,
        "acquisinator_api_set_values() should update the requested acquisinator value");
}

void test_acquisinator_api_set_values_should_return_error_and_reject_invalid_acquisinator_count(void) {
    struct AcquisinatorStrainGauge expected_values[ACQUISINATOR_NAME_COUNT];
    float value = 1;

    for (enum AcquisinatorName acquisinator = 0; acquisinator < ACQUISINATOR_NAME_COUNT; ++acquisinator) {
        acquisinator_api_handler.strain_gauges[acquisinator].first = value;
        acquisinator_api_handler.strain_gauges[acquisinator].second = value;

        expected_values[acquisinator].first = value;
        expected_values[acquisinator].second = value;
    }

    enum AcquisinatorReturnCode rc = acquisinator_api_set_values(
        ACQUISINATOR_NAME_COUNT,
        (struct AcquisinatorStrainGauge){.first = 100.0f, .second = 100.0f});

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        ACQUISINATOR_RC_ERROR,
        rc,
        "acquisinator_api_set_values(ACQUISINATOR_NAME_COUNT, ...) should return ACQUISINATOR_RC_ERROR");

    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(
        expected_values,
        acquisinator_api_handler.strain_gauges,
        ACQUISINATOR_NAME_COUNT,
        "Invalid acquisinator should not modify any valid acquisinator value");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_acquisinator_api_init_should_return_ok_and_set_all_acquisinators_to_zero);
    RUN_TEST(test_acquisinator_api_get_values_should_return_saved_value);
    RUN_TEST(test_acquisinator_api_get_values_should_return_uint32_max_for_invalid_acquisinator_count);
    RUN_TEST(test_acquisinator_api_set_values_should_update_value_for_valid_input);
    RUN_TEST(test_acquisinator_api_set_values_should_return_error_and_reject_invalid_acquisinator_count);

    return UNITY_END();
}