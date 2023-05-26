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

    float sumR = abs(gx.r + gy.r);
    float sumG = abs(gx.g + gy.g);
    float sumB = abs(gx.b + gy.b);

    sumR = (sumR > 255)? 255: sumR;
    sumG = (sumG > 255)? 255: sumG;
    sumB = (sumB > 255)? 255: sumB;

    color_t color = {
        .r = sumR,
        .g = sumG,
        .b = sumB
    };

    writePixelColorAtCurrentCoord(Out, color);
}
