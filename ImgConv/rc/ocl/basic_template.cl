#include "common.h"
#include "convolution.h"

__kernel void pixelKernel(const __global uchar *In,
                                __global uchar *Out,
                                __global float *k) {

    size_t x = get_global_id(0);
    size_t y = get_global_id(1);
    size_t i = (W * y + x) * 3;

    Out[i + 0] = In[i + 0];
    Out[i + 1] = In[i + 1];
    Out[i + 2] = In[i + 2];
}
