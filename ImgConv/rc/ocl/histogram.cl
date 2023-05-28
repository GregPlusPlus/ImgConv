#include "common.h"

__kernel void pixelKernel(const __global uchar *In,
                                __global size_t *histR,
                                __global size_t *histG,
                                __global size_t *histB) {

    color_t color = pixelColorAtCurrentCoord(In);

    histR[color.r] ++;
    histG[color.g] ++;
    histB[color.b] ++;
}
