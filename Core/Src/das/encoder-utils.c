#include "encoder-utils.h"
#include "encoder.h"

EAGLETRT_STATIC SPI_HandleTypeDef *const hspi_encoder = &hspi1;

float _ENC_C_inplace_average = 0.0f;

float raw_to_angle(uint8_t byte0, uint8_t byte1) {
    // byte1 contains the 7 most significant bits of the angle, while byte0 contains the 5 least significant bits
    uint16_t parsed = ((uint16_t)(byte1 & 0b01111111) << 5) | (byte0 & 0b11111000) >> 3;
    return parsed / 4095.f * 360.f;
}

float update_rolling_average(float average, float new_value) {
    static const float a = 1.0f / ENC_ROLLAVG_SIZE;
    average = average * (1.0f - a) + new_value * a;
    return average;
}

float ms_to_radsec(float vel) {
    float enc_circ_m = 0.2368760861f;
    float rpm = vel / enc_circ_m;
    return rpm * 0.10472f;
}