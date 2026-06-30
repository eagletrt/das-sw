#ifndef IRTS_H
#define IRTS_H

#include "eagletrt.h"
#include <stdint.h>

/*!
 * \brief Names for checked irts
 */
enum IrtsName : uint8_t {
    IRTS_NAME_LEFT,  /*!< Irts LEFT */
    IRTS_NAME_RIGHT, /*!< Irts RIGHT */
    IRTS_NAME_COUNT  /*!< Total number of irts */
};

/*!
 * \brief Possible return codes for irts initialization function
 */
enum IrtsReturnCode : uint8_t {
    IRTS_RC_OK,   /*!< Initialization successful */
    IRTS_RC_ERROR /*!< Error during initialization */
};

/*!
 * \brief Struct that handles all temperature from irts
 */
struct IrtsHandler {
    float left_temperature;
    float right_temperature;
};

#endif // IRTS_H