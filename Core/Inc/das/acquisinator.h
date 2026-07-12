#ifndef ACQUISINATOR_H
#define ACQUISINATOR_H

#include "eagletrt.h"
#include <stdint.h>

/*!
 * \brief Names for checked acquisinator
 */
enum AcquisinatorName : uint8_t {
    ACQUISINATOR_NAME_FIRST,  /*!< FIRST Acquisinator */
    ACQUISINATOR_NAME_SECOND, /*!< SECOND Acquisinator */
    ACQUISINATOR_NAME_THIRD,  /*!< THIRD Acquisinator */
    ACQUISINATOR_NAME_FOURTH, /*!< FOURTH Acquisinator */
    ACQUISINATOR_NAME_FIFTH,  /*!< FIFTH Acquisinator */
    ACQUISINATOR_NAME_SIXTH,  /*!< SIXTH Acquisinator */
    ACQUISINATOR_NAME_COUNT   /*!< Total number of acquisinators */
};

/*!
 * \brief Possible return codes for acquisinator initialization function
 */
enum AcquisinatorReturnCode : uint8_t {
    ACQUISINATOR_RC_OK,   /*!< Initialization successful */
    ACQUISINATOR_RC_ERROR /*!< Error during initialization */
};

/*!
 * \brief Struct that handles all relevant acquisinator information
 *
 * \note 3 acquisinator for each tyre, each acquisinator collect 2 strain gauge value
 */
struct AcquisinatorStrainGauge {
    float first;
    float second;
};

struct AcquisinatorHandler {
    struct AcquisinatorValue acquisinator_value[ACQUISINATOR_NAME_COUNT]; /*!< Acquisinator values array */
};

#endif // ACQUISINATOR_H