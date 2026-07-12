#include "acquisinator-api.h"
#include <string.h>

EAGLETRT_STATIC struct AcquisinatorHandler acquisinator_api_handler;

enum AcquisinatorReturnCode acquisinator_api_init(void) {
    // Initialize acquisinator value to 0 to indicate no data
    memset(&acquisinator_api_handler, 0, sizeof(acquisinator_api_handler));

    return ACQUISINATOR_RC_OK;
}

struct AcquisinatorStrainGauge acquisinator_api_get_values(enum AcquisinatorName acquisinator) {
    if (acquisinator >= ACQUISINATOR_NAME_COUNT) {
        // create a struct with all data set to implausible values
        struct AcquisinatorStrainGauge empty_value = { .first = UINT32_MAX, .second = UINT32_MAX };
        return empty_value;
    }

    return acquisinator_api_handler.strain_gauges[acquisinator];
}

enum AcquisinatorReturnCode acquisinator_api_set_values(enum AcquisinatorName acquisinator, struct AcquisinatorStrainGauge acquisinator_strain_gauge) {
    if (acquisinator >= ACQUISINATOR_NAME_COUNT) {
        return ACQUISINATOR_RC_ERROR;
    }

    acquisinator_api_handler.strain_gauges[acquisinator].first = acquisinator_strain_gauge.first;
    acquisinator_api_handler.strain_gauges[acquisinator].second = acquisinator_strain_gauge.second;

    return ACQUISINATOR_RC_OK;
}