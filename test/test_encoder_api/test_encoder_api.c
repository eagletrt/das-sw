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
        encoder_api_get_angle(),
        "encoder_api_get_angle() should return the saved angle");
}

void test_encoder_api_set_angle_should_update_angle_for_valid_input(void) {
    enum EncoderReturnCode rc = encoder_api_set_angle(
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

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_encoder_api_init_should_return_ok_and_set_angle_to_zero);
    RUN_TEST(test_encoder_api_get_angle_should_return_saved_angle);
    RUN_TEST(test_encoder_api_set_angle_should_update_angle_for_valid_input);

    return UNITY_END();
}
