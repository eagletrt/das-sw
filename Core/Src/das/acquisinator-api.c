#include "acquisinator-api.h"
#include <string.h>

EAGLETRT_STATIC struct AcquisinatorHandler acquisinator_api_handler;

enum AcquisinatorReturnCode acquisinator_api_init(void) {
    // Initialize acquisinator value to 0 to indicate no data
    memset(&acquisinator_api_handler, 0, sizeof(acquisinator_api_handler));

    return ACQUISINATOR_RC_OK;
}

struct AcquisinatorValue acquisinator_api_get_struct_value(enum AcquisinatorName acquisinator) {
    if (acquisinator >= ACQUISINATOR_NAME_COUNT) {
        // create a struct with al data set to 0
        struct AcquisinatorValue empty_value = { 0 };
        return empty_value;
    }

    return acquisinator_api_handler.acquisinator_value[acquisinator];
}

enum AcquisinatorReturnCode acquisinator_api_set_values(enum AcquisinatorName acquisinator, float first_strain_gauge, float second_strain_gauge) {
    if (acquisinator >= ACQUISINATOR_NAME_COUNT) {
        return ACQUISINATOR_RC_ERROR;
    }

    acquisinator_api_handler.acquisinator_value[acquisinator].first_strain_gauge = first_strain_gauge;
    acquisinator_api_handler.acquisinator_value[acquisinator].second_strain_gauge = second_strain_gauge;

    return ACQUISINATOR_RC_OK;
}