#include "unity.h"

#include "feedback.h"
#include "feedback-api.h"

#include <stdint.h>

extern struct FeedbackHandler feedback_api_handler;

void setUp(void) {
    (void)feedback_api_init();
}

void tearDown(void) {
}

void test_feedback_api_init_should_return_ok_and_set_all_feedbacks_to_error(void) {
    uint8_t expected_states[FEEDBACK_NAME_COUNT];

    for (uint8_t i = 0U; i < FEEDBACK_NAME_COUNT; i++) {
        feedback_api_handler.feedback_line_state[i] = FEEDBACK_STATE_LOW;
        expected_states[i] = FEEDBACK_STATE_ERROR;
    }

    enum FeedbackReturnCode rc = feedback_api_init();

    TEST_ASSERT_EQUAL_UINT8(FEEDBACK_RC_OK, rc);

    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(
        expected_states,
        feedback_api_handler.feedback_line_state,
        FEEDBACK_NAME_COUNT,
        "Each feedback state should be initialized to FEEDBACK_STATE_ERROR");
}

void test_feedback_api_get_state_should_return_saved_state_for_valid_feedback(void) {
    enum FeedbackName feedback = (enum FeedbackName)0U;
    feedback_api_handler.feedback_line_state[feedback] = FEEDBACK_STATE_HIGH;

    enum FeedbackState state = feedback_api_get_state(feedback);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_STATE_HIGH,
        state,
        "feedback_api_get_state() should return the saved state for a valid feedback");
}

void test_feedback_api_get_state_should_return_error_for_invalid_feedback_count(void) {
    enum FeedbackState state = feedback_api_get_state(FEEDBACK_NAME_COUNT);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_STATE_ERROR,
        state,
        "feedback_api_get_state(FEEDBACK_NAME_COUNT) should return FEEDBACK_STATE_ERROR");
}

void test_feedback_api_set_state_should_update_state_for_valid_input(void) {
    enum FeedbackName feedback = (enum FeedbackName)0U;

    enum FeedbackReturnCode rc = feedback_api_set_state(
        feedback,
        FEEDBACK_STATE_HIGH);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_OK,
        rc,
        "feedback_api_set_state() should return FEEDBACK_RC_OK for valid input");

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_STATE_HIGH,
        feedback_api_handler.feedback_line_state[feedback],
        "feedback_api_set_state() should update the requested feedback state");
}

void test_feedback_api_set_state_should_reject_invalid_feedback_count(void) {
    uint8_t expected_states[FEEDBACK_NAME_COUNT];

    for (uint8_t i = 0U; i < FEEDBACK_NAME_COUNT; i++) {
        enum FeedbackState state = FEEDBACK_STATE_LOW;

        feedback_api_handler.feedback_line_state[i] = state;
        expected_states[i] = state;
    }

    enum FeedbackReturnCode rc = feedback_api_set_state(
        FEEDBACK_NAME_COUNT,
        FEEDBACK_STATE_HIGH);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_ERROR,
        rc,
        "feedback_api_set_state(FEEDBACK_NAME_COUNT, ...) should return FEEDBACK_RC_ERROR");

    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(
        expected_states,
        feedback_api_handler.feedback_line_state,
        FEEDBACK_NAME_COUNT,
        "Invalid feedback should not modify any valid feedback state");
}

void test_feedback_api_set_state_should_reject_invalid_state_count(void) {
    enum FeedbackName feedback = (enum FeedbackName)0U;
    feedback_api_handler.feedback_line_state[0] = FEEDBACK_STATE_LOW;

    enum FeedbackReturnCode rc = feedback_api_set_state(
        feedback,
        FEEDBACK_STATE_COUNT);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_ERROR,
        rc,
        "feedback_api_set_state(..., FEEDBACK_STATE_COUNT) should return FEEDBACK_RC_ERROR");

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_STATE_LOW,
        feedback_api_handler.feedback_line_state[0],
        "Invalid state should not change the previous feedback state");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_feedback_api_init_should_return_ok_and_set_all_feedbacks_to_error);
    RUN_TEST(test_feedback_api_get_state_should_return_saved_state_for_valid_feedback);
    RUN_TEST(test_feedback_api_get_state_should_return_error_for_invalid_feedback_count);
    RUN_TEST(test_feedback_api_set_state_should_update_state_for_valid_input);
    RUN_TEST(test_feedback_api_set_state_should_reject_invalid_feedback_count);
    RUN_TEST(test_feedback_api_set_state_should_reject_invalid_state_count);

    return UNITY_END();
}
