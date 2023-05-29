#include "common.h"

__kernel void pixelKernel(const __global uchar *In,
                                __global size_t *cdfR,
                                __global size_t *cdfG,
                                __global size_t *cdfB,
                                __global uchar *Out) {

    color_t color = pixelColorAtCurrentCoord(In);

    color.r = 255 - color.r;
    color.g = 255 - color.g;
    color.b = 255 - color.b;

    writePixelColorAtCurrentCoord(Out, color);
}
