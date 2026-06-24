#include "irts-api.h"
#include <string.h>

EAGLETRT_STATIC struct IrtsHandler irts_api_handler;

enum IrtsReturnCode irts_api_init(void) {
    // Initialize irts value to 0 to indicate no data
    memset(&irts_api_handler, 0, sizeof(irts_api_handler));

    return IRTS_RC_OK;
}

double irts_api_get_value(enum IrtsName irts) {
    if (irts == IRTS_NAME_LEFT)
        return (double)irts_api_handler.left_temperature;
    else if (irts == IRTS_NAME_RIGHT)
        return (double)irts_api_handler.right_temperature;
    else
        return -1;
}

enum IrtsReturnCode irts_api_set_value(enum IrtsName irts, double value) {
    if (irts >= IRTS_NAME_COUNT) {
        return IRTS_RC_ERROR;
    }

    if (irts == IRTS_NAME_LEFT) {
        irts_api_handler.left_temperature = value;
    } else if (irts == IRTS_NAME_RIGHT) {
        irts_api_handler.right_temperature = value;
    }

    return IRTS_RC_OK;
}