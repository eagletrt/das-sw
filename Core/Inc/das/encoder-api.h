#include "encoder.h"

#include "eagletrt.h"
#include <stdlib.h>
#include <stdint.h>

#if defined(DAS_FRONT)

/*!
 * \brief Initializes the module
 *
 * \retval ENCODER_RC_OK if successful
 * \retval ENCODER_RC_ERROR if fail
 */
enum EncoderReturnCode encoder_api_init(void);

/*!
 * \brief  Get the current angle of a encoder steering wheel
 *
 * \retval float angle of \p encoder steering wheel
 */
float encoder_api_get_angle(enum EncoderName encoder);

/*!
 * \brief  Set the current state of a encoder line
 *
 * \param state The state to set \p encoder to
 *
 * \retval ENCODER_RC_OK if successful
 * \retval ENCODER_RC_ERROR if \p encoder or \p state are out of bounds
 */
enum EncoderReturnCode encoder_api_set_angle(enum EncoderName encoder, float angle);

#endif // DAS_FRONT