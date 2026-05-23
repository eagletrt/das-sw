#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "eagletrt.h"
#include <stdint.h>

/*!
 * \brief Names for checked potentiometer
 */
enum PotentiometerName {
    POTENTIOMETER_NAME_1,    /*!< Potentiometer N1 */
    POTENTIOMETER_NAME_2,    /*!< Potentiometer N2 */
    POTENTIOMETER_NAME_COUNT /*!< Total number of potentiometers */
};

/*!
 * \brief Possible return codes for potentiometer initialization function
 */
enum PotentiometerReturnCode {
    POTENTIOMETER_RC_OK,   /*!< Initialization successful */
    POTENTIOMETER_RC_ERROR /*!< Error during initialization */
};

/*!
 * \brief Struct that handles all relevant potentiometer information
 */
struct PotentiometerHandler {
    EAGLETRT_VOLATILE uint16_t potentiometer_value[POTENTIOMETER_NAME_COUNT]; /*!< Potentiometer values array */
};

#endif // POTENTIOMETER_H