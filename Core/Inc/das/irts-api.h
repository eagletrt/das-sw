#include "irts.h"

#include "eagletrt.h"
#include <stdlib.h>
#include <stdint.h>

/*!
 * \brief Initializes the module
 *
 * \retval IRTS_RC_OK if successful
 * \retval IRTS_RC_ERROR if fail
 */
enum IrtsReturnCode irts_api_init(void);

/*!
 * \brief  Get the current state of a irts line
 *
 * \param irts The irts to query
 *
 * \retval int16_t temperature of \p irts
 */
float irts_api_get_temperature(enum IrtsName irts);

/*!
 * \brief  Set the current state of a irts line
 *
 * \param irts The irts to be set
 * \param temperature The temperature to set \p irts to
 *
 * \retval IRTS_RC_OK if successful
 * \retval IRTS_RC_ERROR if \p irts or \p temperature are out of bounds
 */
enum IrtsReturnCode irts_api_set_temperature(enum IrtsName irts, float temperature);