#include "spi.h"
#include "eagletrt.h"

#include "limits.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"

#include <float.h>
#include <math.h>
#include <string.h>

#define ENC_ROLLAVG_SIZE (5)

EAGLETRT_STATIC uint8_t buf[2];

/*!
 * \brief Converts raw data of encoder into angle
 *
 * \param byte0 less significant byte of original message
 * \param byte1 most significant byte of original message
 * 
 * \retval float angle converted
 */
float raw_to_angle(uint8_t byte0, uint8_t byte1);

/*!
 * \brief update the rolling average
 * 
 * \param average old average
 * \param new value to add into average
 * 
 * \retval float new rolling average
 */
float update_rolling_average(float average, float new_value);