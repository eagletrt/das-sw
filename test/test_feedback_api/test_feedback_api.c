#include "unity.h"

#include "feedback.h"
#include "feedback-api.h"

#include <stdint.h>

extern struct FeedbackHandler feedback_api_handler;

static enum FeedbackState valid_state_at(uint8_t index) {
    static const enum FeedbackState states[] = {
        FEEDBACK_STATE_LOW,
        FEEDBACK_STATE_IMPLAUSIBILITY,
        FEEDBACK_STATE_HIGH,
        FEEDBACK_STATE_ERROR,
    };

    return states[index % (uint8_t)(sizeof(states) / sizeof(states[0]))];
}

void setUp(void) {
    (void)feedback_api_init();
}

void tearDown(void) {
}

void test_feedback_api_init_should_return_ok(void) {
    enum FeedbackReturnCode rc = feedback_api_init();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_OK,
        rc,
        "feedback_api_init() should return FEEDBACK_RC_OK");
}

void test_feedback_api_init_should_set_all_feedbacks_to_error(void) {
    uint8_t expected_states[FEEDBACK_NAME_COUNT];
    uint8_t actual_states[FEEDBACK_NAME_COUNT];

    for (uint8_t i = 0U; i < (uint8_t)FEEDBACK_NAME_COUNT; i++) {
        feedback_api_handler.feedback_line_state[i] = FEEDBACK_STATE_LOW;
        expected_states[i] = (uint8_t)FEEDBACK_STATE_ERROR;
    }

    enum FeedbackReturnCode rc = feedback_api_init();

    TEST_ASSERT_EQUAL_UINT8(FEEDBACK_RC_OK, rc);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(
        expected_states,
        feedback_api_handler.feedback_line_state,
        FEEDBACK_NAME_COUNT,
        "Each feedback state should be initialized to FEEDBACK_STATE_ERROR");
}

void test_feedback_api_get_state_should_return_saved_state_for_each_valid_feedback(void) {
    for (uint8_t i = 0U; i < (uint8_t)FEEDBACK_NAME_COUNT; i++) {
        enum FeedbackState expected_state = valid_state_at(i);
        feedback_api_handler.feedback_line_state[i] = expected_state;

        enum FeedbackState actual_state = feedback_api_get_state((enum FeedbackName)i);

        TEST_ASSERT_EQUAL_UINT8_MESSAGE(
            expected_state,
            actual_state,
            "feedback_api_get_state() should return the saved state for valid feedback");
    }
}

void test_feedback_api_get_state_should_return_error_for_invalid_feedback_count(void) {
    enum FeedbackState state = feedback_api_get_state(FEEDBACK_NAME_COUNT);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_STATE_ERROR,
        state,
        "feedback_api_get_state(FEEDBACK_NAME_COUNT) should return FEEDBACK_STATE_ERROR");
}

void test_feedback_api_get_state_should_return_error_for_feedback_after_count(void) {
    enum FeedbackState state = feedback_api_get_state((enum FeedbackName)(FEEDBACK_NAME_COUNT + 1));

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_STATE_ERROR,
        state,
        "feedback_api_get_state() should reject feedback values greater than FEEDBACK_NAME_COUNT");
}

void test_feedback_api_set_state_should_accept_each_valid_feedback_and_each_valid_state(void) {
    const enum FeedbackState valid_states[] = {
        FEEDBACK_STATE_LOW,
        FEEDBACK_STATE_IMPLAUSIBILITY,
        FEEDBACK_STATE_HIGH,
        FEEDBACK_STATE_ERROR,
    };

    enum {
        valid_state_count = sizeof(valid_states) / sizeof(valid_states[0]),
        test_case_count = FEEDBACK_NAME_COUNT * valid_state_count,
    };

    uint8_t return_codes[test_case_count];
    uint8_t state_update_results[test_case_count];

    uint8_t test_case_index = 0U;

    for (uint8_t feedback_index = 0U; feedback_index < (uint8_t)FEEDBACK_NAME_COUNT; feedback_index++) {
        for (uint8_t state_index = 0U; state_index < (uint8_t)valid_state_count; state_index++) {
            enum FeedbackState expected_state = valid_states[state_index];

            enum FeedbackReturnCode rc = feedback_api_set_state(
                (enum FeedbackName)feedback_index,
                expected_state);

            return_codes[test_case_index] = (uint8_t)rc;

            state_update_results[test_case_index] =
                (feedback_api_handler.feedback_line_state[feedback_index] == expected_state)
                    ? 1U
                    : 0U;

            test_case_index++;
        }
    }

    TEST_ASSERT_EACH_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_OK,
        return_codes,
        test_case_count,
        "feedback_api_set_state() should return OK for each valid feedback and valid state");

    TEST_ASSERT_EACH_EQUAL_UINT8_MESSAGE(
        1U,
        state_update_results,
        test_case_count,
        "feedback_api_set_state() should update the requested feedback state for each valid feedback and valid state");
}

void test_feedback_api_set_state_should_reject_invalid_feedback_count(void) {
    uint8_t expected_states[FEEDBACK_NAME_COUNT];
    uint8_t actual_states[FEEDBACK_NAME_COUNT];

    for (uint8_t i = 0U; i < (uint8_t)FEEDBACK_NAME_COUNT; i++) {
        enum FeedbackState state = valid_state_at(i);

        feedback_api_handler.feedback_line_state[i] = state;
        expected_states[i] = (uint8_t)state;
    }

    enum FeedbackReturnCode rc = feedback_api_set_state(
        FEEDBACK_NAME_COUNT,
        FEEDBACK_STATE_HIGH);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_ERROR,
        rc,
        "feedback_api_set_state(FEEDBACK_NAME_COUNT, ...) should return FEEDBACK_RC_ERROR");

    // actual_states used for conversion enum --> uint8_t
    for (uint8_t i = 0U; i < (uint8_t)FEEDBACK_NAME_COUNT; i++) {
        actual_states[i] = (uint8_t)feedback_api_handler.feedback_line_state[i];
    }

    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(
        expected_states,
        actual_states,
        FEEDBACK_NAME_COUNT,
        "Invalid feedback should not modify any valid feedback state");
}

void test_feedback_api_set_state_should_reject_feedback_after_count(void) {
    uint8_t expected_states[FEEDBACK_NAME_COUNT];
    uint8_t actual_states[FEEDBACK_NAME_COUNT];

    for (uint8_t i = 0U; i < (uint8_t)FEEDBACK_NAME_COUNT; i++) {
        enum FeedbackState state = valid_state_at(i);

        feedback_api_handler.feedback_line_state[i] = state;
        expected_states[i] = (uint8_t)state;
    }

    enum FeedbackReturnCode rc = feedback_api_set_state(
        (enum FeedbackName)(FEEDBACK_NAME_COUNT + 1),
        FEEDBACK_STATE_HIGH);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_ERROR,
        rc,
        "feedback_api_set_state() should reject feedback values greater than FEEDBACK_NAME_COUNT");

    for (uint8_t i = 0U; i < (uint8_t)FEEDBACK_NAME_COUNT; i++) {
        actual_states[i] = (uint8_t)feedback_api_handler.feedback_line_state[i];
    }

    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(
        expected_states,
        actual_states,
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

void test_feedback_api_set_state_should_reject_state_after_count(void) {
    enum FeedbackName feedback = (enum FeedbackName)0U;
    feedback_api_handler.feedback_line_state[0] = FEEDBACK_STATE_HIGH;

    enum FeedbackReturnCode rc = feedback_api_set_state(
        feedback,
        (enum FeedbackState)(FEEDBACK_STATE_COUNT + 1));

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_ERROR,
        rc,
        "feedback_api_set_state() should reject state values greater than FEEDBACK_STATE_COUNT");

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_STATE_HIGH,
        feedback_api_handler.feedback_line_state[0],
        "Invalid state should not change the previous feedback state");
}

void test_feedback_api_set_state_should_reject_invalid_feedback_and_invalid_state(void) {
    enum FeedbackReturnCode rc = feedback_api_set_state(
        FEEDBACK_NAME_COUNT,
        FEEDBACK_STATE_COUNT);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_ERROR,
        rc,
        "feedback_api_set_state() should reject invalid feedback and invalid state");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_feedback_api_init_should_return_ok);
    RUN_TEST(test_feedback_api_init_should_set_all_feedbacks_to_error);
    RUN_TEST(test_feedback_api_get_state_should_return_saved_state_for_each_valid_feedback);
    RUN_TEST(test_feedback_api_get_state_should_return_error_for_invalid_feedback_count);
    RUN_TEST(test_feedback_api_get_state_should_return_error_for_feedback_after_count);
    RUN_TEST(test_feedback_api_set_state_should_accept_each_valid_feedback_and_each_valid_state);
    RUN_TEST(test_feedback_api_set_state_should_reject_invalid_feedback_count);
    RUN_TEST(test_feedback_api_set_state_should_reject_feedback_after_count);
    RUN_TEST(test_feedback_api_set_state_should_reject_invalid_state_count);
    RUN_TEST(test_feedback_api_set_state_should_reject_state_after_count);
    RUN_TEST(test_feedback_api_set_state_should_reject_invalid_feedback_and_invalid_state);

    return UNITY_END();
}
