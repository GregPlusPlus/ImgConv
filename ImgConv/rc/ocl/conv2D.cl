#include "common.h"
#include "convolution.h"

__kernel void pixelKernel(const __global uchar *In,
                                __global uchar *Out,
                                __global float *k) {

    conv2D(In, Out, k);
}
