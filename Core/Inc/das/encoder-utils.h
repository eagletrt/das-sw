#include "eagletrt.h"
#include <stdint.h>

#define ENCODER_ROLLAVG_SIZE (5)

extern uint8_t encoder_raw_buf[2];
extern float encoder_rolling_average;

/*!
 * \brief Converts raw data of encoder into angle
 *
 * \param byte0 less significant byte of raw value
 * \param byte1 most significant byte of raw value
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