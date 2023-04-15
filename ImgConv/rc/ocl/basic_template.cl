#include "common.h"
#include "convolution.h"

__kernel void pixelKernel(const __global uchar *In,
                                __global uchar *Out,
                                __global float *k) {

    OUT_RED = IN_RED;
    OUT_GREEN = IN_GREEN;
    OUT_BLUE = IN_BLUE;
}
