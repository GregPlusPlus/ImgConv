#include "common.h"

__kernel void pixelKernel(const __global uchar *In,
                          __global uchar *Out,
                          const __global size_t *cdfR,
                          const __global size_t *cdfG,
                          const __global size_t *cdfB) {

    const float k = 255.f / (float)(W * H);
    color_t color = pixelColorAtCurrentCoord(In);

    color.r = (uchar)((float)cdfR[color.r] * k);
    color.g = (uchar)((float)cdfG[color.g] * k);
    color.b = (uchar)((float)cdfB[color.b] * k);

    writePixelColorAtCurrentCoord(Out, color);
}
