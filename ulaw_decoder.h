#ifndef __ULAW_DECODER__
#define __ULAW_DECODER__

#include <stdint.h>
#include <math.h>

//decode ulaw byte to signed n bit sample
static void ulaw_decode(int16_t* dst, int8_t* src, const uint16_t num_samples, const uint8_t target_res);
static void ulaw_decode(int16_t* dst, int8_t* src, const uint16_t num_samples, const uint8_t target_res)
{
    const uint16_t max_amp = (1UL << target_res) / 2;
    const double scl_factor = (double)(max_amp) / 255.0;

    for (uint16_t x = 0; x < num_samples; x++)
    {
        int8_t samp = ~src[x];
        int8_t sign = samp & 0x80 ? - 1 : 1;
        samp &= 0x7f;

        double temp = (double)(samp) / 127.0;
        temp = pow(256.0, temp) - 1;
        int32_t out = (int32_t)(temp * scl_factor);
        out *= sign;

        if (out == max_amp)
        out -= 1;

        dst[x] = (int16_t)(out);
    }
}

#endif