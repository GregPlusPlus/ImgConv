#include "common.h"

__kernel void pixelKernel(const __global uchar *In,
                          const __global size_t *cdfR,
                          const __global size_t *cdfG,
                          const __global size_t *cdfB,
                                __global uchar *Out) {

    color_t color = pixelColorAtCurrentCoord(In);

    unsigned int mean = color.r + color.g + color.b;
    mean /= 3;

    color.r = mean;
    color.g = mean;
    color.b = mean;

    writePixelColorAtCurrentCoord(Out, color);
}
