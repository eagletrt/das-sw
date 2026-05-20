#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "eagletrt.h"

#if defined(DAS_FRONT) && defined(DAS_REAR)
#error "Only one between DAS_FRONT and DAS_REAR can be defined"
#endif

#if defined(DAS_FRONT)

enum FeedbackName {
    FEEDBACK_NAME_PILOT,
    FEEDBACK_NAME_SX,
    FEEDBACK_NAME_DX,
    FEEDBACK_NAME_INERTIAL,
    FEEDBACK_NAME_COUNT
};

#elif defined(DAS_REAR)

enum FeedbackName {
    FEEDBACK_NAME_INTERLOCK,
    FEEDBACK_NAME_ARMS_LINE,
    FEEDBACK_NAME_COUNT
};

#else
#error "Either DAS_FRONT or DAS_REAR must be defined"
#endif

#define FEEDBACK_THRESHOLD_LOW 300
#define FEEDBACK_THRESHOLD_HIGH 3900

enum FeedbackReturnCode {
    FEEDBACK_RC_OK,
    FEEDBACK_RC_ERROR
};

enum FeedbackState {
    FEEDBACK_STATE_LOW,
    FEEDBACK_STATE_IMPLAUSIBILITY,
    FEEDBACK_STATE_HIGH,
    FEEDBACK_STATE_ERROR,
    FEEDBACK_STATE_COUNT
};

struct FeedbackHandler {
    EAGLETRT_VOLATILE enum FeedbackState feedback_line_state[FEEDBACK_NAME_COUNT];
};

#endif // FEEDBACK_H