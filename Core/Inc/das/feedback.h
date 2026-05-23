#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "eagletrt.h"
#include <stdint.h>

#if defined(DAS_FRONT) && defined(DAS_REAR)
#error "Only one between DAS_FRONT and DAS_REAR can be defined"
#endif

#if defined(DAS_FRONT)

/*!
 * \brief Names for checked shutdowns of DAS FRONT
 */
enum FeedbackName : uint8_t {
    FEEDBACK_NAME_PILOT,    /*!< Shutdown button for the pilot */
    FEEDBACK_NAME_SX,       /*!< Mainhoop SX shutdown */
    FEEDBACK_NAME_DX,       /*!< Mainhoop DX shutdown */
    FEEDBACK_NAME_INERTIAL, /*!< Inertial shutdown */
    FEEDBACK_NAME_COUNT     /*!< Total number of feedback lines */
};

#elif defined(DAS_REAR)

/*!
 * \brief Names for checked shutdowns of DAS REAR
 */
enum FeedbackName : uint8_t {
    FEEDBACK_NAME_INTERLOCK, /*!< Interlock feedback */
    FEEDBACK_NAME_ARMS_LINE, /*!< Arms line feedback signal */
    FEEDBACK_NAME_COUNT      /*!< Total number of feedback lines */
};

#else
#error "Either DAS_FRONT or DAS_REAR must be defined"
#endif

#define FEEDBACK_THRESHOLD_LOW (300)
#define FEEDBACK_THRESHOLD_HIGH (3900)

/*!
 * \brief Possible return codes for feedback initialization function
 */
enum FeedbackReturnCode : uint8_t {
    FEEDBACK_RC_OK,   /*!< Initialization successful */
    FEEDBACK_RC_ERROR /*!< Error during initialization */
};

/*!
 * \brief Possible return codes for feedback status functions
 */
enum FeedbackState : uint8_t {
    FEEDBACK_STATE_LOW,            /*!< Feedback line is low */
    FEEDBACK_STATE_IMPLAUSIBILITY, /*!< Feedback line is on a borderline state */
    FEEDBACK_STATE_HIGH,           /*!< Feedback line is high */
    FEEDBACK_STATE_ERROR,          /*!< Error in reading feedback button states */
    FEEDBACK_STATE_COUNT           /*!< Total number of feedback statuses */
};

/*!
 * \brief Struct that handles all relevant feedback information
 */
struct FeedbackHandler {
    EAGLETRT_VOLATILE enum FeedbackState feedback_line_state[FEEDBACK_NAME_COUNT]; /*!< Feedback button state array */
};

#endif // FEEDBACK_H