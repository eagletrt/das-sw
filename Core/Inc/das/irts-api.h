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
 * \retval int16_t value of \p irts
 */
double irts_api_get_value(enum IrtsName irts);

/*!
 * \brief  Set the current state of a irts line
 *
 * \param irts The irts to be set
 * \param value The value to set \p irts to
 *
 * \retval IRTS_RC_OK if successful
 * \retval IRTS_RC_ERROR if \p irts or \p value are out of bounds
 */
enum IrtsReturnCode irts_api_set_value(enum IrtsName irts, double value);