#ifndef ENCODER_H
#define ENCODER_H

#include "eagletrt.h"
#include <stdint.h>

#if defined(DAS_FRONT)

/*!
 * \brief Names for checked shutdowns of DAS FRONT
 */
// should I keep that? Or I assume that there can be only 1 encoder
enum EncoderName : uint8_t {
    ENCODER_NAME_STEERING, /*!< Encoder steering wheel */
    ENCODER_NAME_COUNT     /*!< Total number of encoders */
};

/*!
 * \brief Possible return codes for encoder initialization function
 */
enum EncoderReturnCode : uint8_t {
    ENCODER_RC_OK,   /*!< Initialization successful */
    ENCODER_RC_ERROR /*!< Error during initialization */
};

/*!
 * \brief Struct that handles all relevant encoder information
 */
struct EncoderHandler {
    float encoder_steering_wheel_angle; /*!< Encoder angle */
};

#endif // DAS_FRONT

#endif // ENCODER_H