#include "unity.h"

#include "encoder-api.h"
#include "encoder-utils.h"
#include "encoder.h"

#include <math.h>
#include <stdint.h>

extern struct EncoderHandler encoder_api_handler;

void setUp(void) {
    (void)encoder_api_init();
}

void tearDown(void) {
}

void test_encoder_api_init_should_return_ok_and_set_angle_to_zero(void) {
    encoder_api_handler.encoder_steering_wheel_angle = 123.0F;

    enum EncoderReturnCode rc = encoder_api_init();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        ENCODER_RC_OK,
        rc,
        "encoder_api_init() should return ENCODER_RC_OK");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        0.0F,
        encoder_api_handler.encoder_steering_wheel_angle,
        "The steering encoder angle should be initialized to zero");
}

void test_encoder_api_get_angle_should_return_saved_angle(void) {
    encoder_api_handler.encoder_steering_wheel_angle = 87.25F;

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        87.25F,
        encoder_api_get_angle(ENCODER_NAME_STEERING),
        "encoder_api_get_angle() should return the saved angle");
}

void test_encoder_api_get_angle_should_return_invalid_value_for_invalid_encoder(void) {
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        ENCODER_INVALID_ANGLE_DEG,
        encoder_api_get_angle(ENCODER_NAME_COUNT),
        "An invalid encoder should return ENCODER_INVALID_ANGLE_DEG");
}

void test_encoder_api_set_angle_should_update_angle_for_valid_input(void) {
    enum EncoderReturnCode rc = encoder_api_set_angle(
        ENCODER_NAME_STEERING,
        45.5F);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        ENCODER_RC_OK,
        rc,
        "A valid angle should be accepted");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        45.5F,
        encoder_api_handler.encoder_steering_wheel_angle,
        "The steering encoder angle should be updated");
}

void test_encoder_api_set_angle_should_reject_invalid_encoder(void) {
    encoder_api_handler.encoder_steering_wheel_angle = 10.0F;

    enum EncoderReturnCode rc = encoder_api_set_angle(
        ENCODER_NAME_COUNT,
        20.0F);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        ENCODER_RC_ERROR,
        rc,
        "An invalid encoder should be rejected");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        10.0F,
        encoder_api_handler.encoder_steering_wheel_angle,
        "An invalid encoder should not modify the stored angle");
}

void test_encoder_api_set_angle_should_reject_nan(void) {
    encoder_api_handler.encoder_steering_wheel_angle = 10.0F;

    enum EncoderReturnCode rc = encoder_api_set_angle(
        ENCODER_NAME_STEERING,
        NAN);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        ENCODER_RC_ERROR,
        rc,
        "NaN should be rejected");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        10.0F,
        encoder_api_handler.encoder_steering_wheel_angle,
        "NaN should not modify the stored angle");
}

void test_encoder_get_raw_position_should_keep_only_12_bits(void) {
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(
        0x0ABCU,
        encoder_get_raw_position(0xFABCU),
        "Only the 12 position bits should be kept");
}

void test_encoder_raw_position_to_angle_should_convert_zero(void) {
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        0.0F,
        encoder_raw_position_to_angle_deg(0U),
        "Raw position zero should be zero degrees");
}

void test_encoder_raw_position_to_angle_should_convert_half_turn(void) {
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        180.0F,
        encoder_raw_position_to_angle_deg(2048U),
        "Raw position 2048 should be 180 degrees");
}

void test_encoder_raw_position_to_angle_should_keep_last_count_below_360(void) {
    float angle = encoder_raw_position_to_angle_deg(4095U);

    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(
        0.0001F,
        359.912109375F,
        angle,
        "The last encoder count should remain below 360 degrees");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_encoder_api_init_should_return_ok_and_set_angle_to_zero);
    RUN_TEST(test_encoder_api_get_angle_should_return_saved_angle);
    RUN_TEST(test_encoder_api_get_angle_should_return_invalid_value_for_invalid_encoder);
    RUN_TEST(test_encoder_api_set_angle_should_update_angle_for_valid_input);
    RUN_TEST(test_encoder_api_set_angle_should_reject_invalid_encoder);
    RUN_TEST(test_encoder_api_set_angle_should_reject_nan);
    RUN_TEST(test_encoder_get_raw_position_should_keep_only_12_bits);
    RUN_TEST(test_encoder_raw_position_to_angle_should_convert_zero);
    RUN_TEST(test_encoder_raw_position_to_angle_should_convert_half_turn);
    RUN_TEST(test_encoder_raw_position_to_angle_should_keep_last_count_below_360);

    return UNITY_END();
}
