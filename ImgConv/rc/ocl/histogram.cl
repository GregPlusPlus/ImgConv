#include "common.h"

#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_int32_base_atomics : enable

__kernel void pixelKernel(const __global uchar *In,
                                __global size_t *histR,
                                __global size_t *histG,
                                __global size_t *histB) {

    color_t color = pixelColorAtCurrentCoord(In);

    atomic_inc(&histR[color.r]);
    atomic_inc(&histG[color.g]);
    atomic_inc(&histB[color.b]);
}
