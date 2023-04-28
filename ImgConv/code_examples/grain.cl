#include "common.h"
#include "random.h"

#define GRAIN 64

__kernel void pixelKernel(const __global uchar *In,
                                __global uchar *Out,
                                __global float *k) {
                                
    srand();

    color_t color = pixelColorAtCurrentCoord(In);
    
    color.r += randCenter(GRAIN);
    color.g += randCenter(GRAIN);
    color.b += randCenter(GRAIN);

    writePixelColorAtCurrentCoord(Out, color);
}
