#include "common.h"
#include "convolution.h"

__const float dhr[9] = {
    -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1
};

__const float dvb[9] = {
    -1, -2, -1,
     0,  0,  0,
     1,  2,  1
};

__const float dhl[9] = {
    1, 0, -1,
    2, 0, -2,
    1, 0, -1
};

__const float dvt[9] = {
    1,  2,  1,
    0,  0,  0,
    -1, -2, -1
};

__kernel void pixelKernel(const __global uchar *In,
                                __global uchar *Out,
                                __global float *k) {

    float threshold = k[4];

    conv2D(In, Out, dhr);
    color_t gxr = pixelColorAtCurrentCoord(Out);

    conv2D(In, Out, dvb);
    color_t gyb = pixelColorAtCurrentCoord(Out);

    conv2D(In, Out, dhl);
    color_t gxl = pixelColorAtCurrentCoord(Out);

    conv2D(In, Out, dvt);
    color_t gyt = pixelColorAtCurrentCoord(Out);

    float sumR = abs(gxr.r + gyb.r + gxl.r + gyt.r);
    float sumG = abs(gxr.g + gyb.g + gxl.g + gyt.g);
    float sumB = abs(gxr.b + gyb.b + gxl.b + gyt.b);

    sumR = (sumR > 255)? 255: sumR;
    sumG = (sumG > 255)? 255: sumG;
    sumB = (sumB > 255)? 255: sumB;

    sumR = (sumR < threshold)? 0: sumR;
    sumG = (sumG < threshold)? 0: sumG;
    sumB = (sumB < threshold)? 0: sumB;

    color_t color = {
        .r = sumR,
        .g = sumG,
        .b = sumB
    };

    writePixelColorAtCurrentCoord(Out, color);
}
