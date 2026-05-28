#include "potentiometer-api.h"

EAGLETRT_STATIC struct PotentiometerHandler potentiometer_api_handler;

/**
 * \attention shall i keep these func? value setted at 0 by default
 */
enum PotentiometerReturnCode potentiometer_api_init(void) {
    // Initialize potentiometer value to 0 to indicate no data
    for (int i = 0; i < POTENTIOMETER_NAME_COUNT; i++) {
        potentiometer_api_handler.potentiometer_value[i] = 0;
    }

    return POTENTIOMETER_RC_OK;
}

/**
 * \attention int16_t used cause of -1
 */
int16_t potentiometer_api_get_value(enum PotentiometerName potentiometer) {
    if (potentiometer >= POTENTIOMETER_NAME_COUNT) {
        return -1;
    }

    return (int16_t)potentiometer_api_handler.potentiometer_value[potentiometer];
}

enum PotentiometerReturnCode potentiometer_api_set_value(enum PotentiometerName potentiometer, uint16_t value) {
    if (potentiometer >= POTENTIOMETER_NAME_COUNT || value >= 4096) {
        return POTENTIOMETER_RC_ERROR;
    }

    potentiometer_api_handler.potentiometer_value[potentiometer] = value;

    return POTENTIOMETER_RC_OK;
}