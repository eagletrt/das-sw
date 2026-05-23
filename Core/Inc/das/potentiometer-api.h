#include "potentiometer.h"

#include "eagletrt.h"
#include <stdlib.h>
#include <stdint.h>

/*!
 * \brief Initializes the module
 *
 * \retval POTENTIOMETER_RC_OK if successful
 * \retval POTENTIOMETER_RC_ERROR if fail
 */
enum PotentiometerReturnCode potentiometer_api_init(void);

/*!
 * \brief  Get the current state of a potentiometer line
 *
 * \param potentiometer The potentiometer to query
 *
 * \retval enum PotentiometerState of \p potentiometer
 */
int16_t potentiometer_api_get_state(enum PotentiometerName potentiometer);

/*!
 * \brief  Set the current state of a potentiometer line
 *
 * \param potentiometer The potentiometer to be set
 * \param state The state to set \p potentiometer to
 *
 * \retval POTENTIOMETER_RC_OK if successful
 * \retval POTENTIOMETER_RC_ERROR if \p potentiometer or \p state are out of bounds
 */
enum PotentiometerReturnCode potentiometer_api_set_state(enum PotentiometerName potentiometer, uint16_t state);