#include "common.h"
#include "convolution.h"
#include "geometry.h"

#define EFFECT_INSIDE true

static geom_circle_t circle1 = {
    .c = {
        .x =250,
        .y = 250
    },
    .r = 200
};
    
static geom_circle_t circle2 = {
    .c = {
        .x = 550,
        .y = 500
    },
    .r = 70
};
    
static geom_circle_t circle3 = {
    .c = {
        .x = 750,
        .y = 300
    },
    .r = 120
};

__kernel void pixelKernel(const __global uchar *In,
                     __global uchar *Out,
                     __global float *k) {
    
    geom_circle_t circles[] = {
        circle1,
        circle2,
        circle3
    };
    
    bool insideCircles = false;
    
    for(size_t i = 0; i < (sizeof(circles) / sizeof(geom_circle_t)); i ++) {
        if(isOnCircleBorder(circles[i], X, Y, 15)) {
            insideCircles = true;
            
            break;
        }
    }

    if(insideCircles == EFFECT_INSIDE) {
        conv2D(In, Out, k);
    } else {
        copyPixelAtCurrentCoord(In, Out);
    }
}
