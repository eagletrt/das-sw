#include "irts-api.h"
#include <string.h>

EAGLETRT_STATIC struct IrtsHandler irts_api_handler;

enum IrtsReturnCode irts_api_init(void) {
    // Initialize irts temperature to 0 to indicate no data
    memset(&irts_api_handler, 0, sizeof(irts_api_handler));

    return IRTS_RC_OK;
}

float irts_api_get_temperature(enum IrtsName irts) {
    if (irts >= IRTS_NAME_COUNT) {
        return -1.0F;
    }
    return irts_api_handler.irts_temperature[irts];
}

enum IrtsReturnCode irts_api_set_temperature(enum IrtsName irts, float temperature) {
    if (irts >= IRTS_NAME_COUNT) {
        return IRTS_RC_ERROR;
    }
    irts_api_handler.irts_temperature[irts] = temperature;

    return IRTS_RC_OK;
}