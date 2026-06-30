#include "irts-api.h"
#include <string.h>

EAGLETRT_STATIC struct IrtsHandler irts_api_handler;

enum IrtsReturnCode irts_api_init(void) {
    // Initialize irts temperature to 0 to indicate no data
    memset(&irts_api_handler, 0, sizeof(irts_api_handler));

    return IRTS_RC_OK;
}

float irts_api_get_temperature(enum IrtsName irts) {
    switch (irts) {
        case IRTS_NAME_LEFT:
            return (float)irts_api_handler.left_temperature;
        case IRTS_NAME_RIGHT:
            return (float)irts_api_handler.right_temperature;
        default:
            return -1;
    }
}

enum IrtsReturnCode irts_api_set_temperature(enum IrtsName irts, float temperature) {
    if (irts >= IRTS_NAME_COUNT) {
        return IRTS_RC_ERROR;
    }

    if (irts == IRTS_NAME_LEFT) {
        irts_api_handler.left_temperature = temperature;
    } else if (irts == IRTS_NAME_RIGHT) {
        irts_api_handler.right_temperature = temperature;
    }

    return IRTS_RC_OK;
}