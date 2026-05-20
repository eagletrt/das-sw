#include "feedback.h"

#include "eagletrt.h"
#include <stdlib.h>
#include <stdint.h>

enum FeedbackReturnCode feedback_api_init(void);
enum FeedbackState feedback_api_get_state(enum FeedbackName feedback);
enum FeedbackReturnCode feedback_api_set_state(enum FeedbackName feedback, enum FeedbackState value);