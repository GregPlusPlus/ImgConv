#include "common.h"
#include "convolution.h"

__global float dh[9] = {
    -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1
};

__global float dv[9] = {
    -1, -2, -1,
     0,  0,  0,
     1,  2,  1
};

__kernel void pixelKernel(const __global uchar *In,
                                __global uchar *Out,
                                __global float *k) {

    conv2D(In, Out, dh);
    color_t gx = pixelColorAtCurrentCoord(Out);

    conv2D(In, Out, dv);
    color_t gy = pixelColorAtCurrentCoord(Out);

    color_t color = {
        .r = sqrt((float)(gx.r * gx.r)),
        .g = sqrt((float)(gx.g * gx.g)),
        .b = sqrt((float)(gx.b * gx.b))
    };

    writePixelColorAtCurrentCoord(Out, color);
}
