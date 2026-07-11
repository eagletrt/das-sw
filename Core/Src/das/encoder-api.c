#include "encoder-api.h"
#include <string.h>

#if defined(DAS_FRONT)

EAGLETRT_STATIC struct EncoderHandler encoder_api_handler;

enum EncoderReturnCode encoder_api_init(void) {
    // Initialize encoder value to 0 to indicate no data
    memset(&encoder_api_handler, 0, sizeof(encoder_api_handler));

    return ENCODER_RC_OK;
}

float encoder_api_get_angle(void) {
    if (encoder >= ENCODER_NAME_COUNT) {
        return FLT_MAX;
    }

    return (float)encoder_api_handler.encoder_steering_wheel_angle;
}

enum EncoderReturnCode encoder_api_set_angle(float value) {
    if (encoder >= ENCODER_NAME_COUNT) {
        return ENCODER_RC_ERROR;
    }

    encoder_api_handler.encoder_steering_wheel_angle = value;

    return ENCODER_RC_OK;
}

#endif // DAS_FRONT