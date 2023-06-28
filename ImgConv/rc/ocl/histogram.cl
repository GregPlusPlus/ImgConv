#include "common.h"

#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable

__kernel void pixelKernel(const __global uchar *In,
                                __global size_t *histR,
                                __global size_t *histG,
                                __global size_t *histB) {

    color_t color = pixelColorAtCurrentCoord(In);

#if CL_DEVICE_ADDRESS_BITS == 64
    atomic_inc((volatile __global ulong*)&histR[color.r]);
    atomic_inc((volatile __global ulong*)&histG[color.g]);
    atomic_inc((volatile __global ulong*)&histB[color.b]);
#else
    atomic_inc((volatile __global uint*)&histR[color.r]);
    atomic_inc((volatile __global uint*)&histG[color.g]);
    atomic_inc((volatile __global uint*)&histB[color.b]);
#endif
}
