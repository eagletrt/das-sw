#include "potentiometer-api.h"
#include <string.h>

#define MAX_ADC_VALUE (4095)

EAGLETRT_STATIC struct PotentiometerHandler potentiometer_api_handler;

enum PotentiometerReturnCode potentiometer_api_init(void) {
    // Initialize potentiometer value to 0 to indicate no data
    memset(&potentiometer_api_handler, 0, sizeof(potentiometer_api_handler));

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
    if (potentiometer >= POTENTIOMETER_NAME_COUNT || value > MAX_ADC_VALUE) {
        return POTENTIOMETER_RC_ERROR;
    }

    potentiometer_api_handler.potentiometer_value[potentiometer] = value;

    return POTENTIOMETER_RC_OK;
}