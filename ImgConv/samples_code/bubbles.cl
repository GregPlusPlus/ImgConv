#include "common.h"

typedef struct {
    size_t x;
    size_t y;
    size_t r;
} circle_t;

bool isInsideCircle(circle_t c, int x, int y)
{
    if (((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y)) <= (c.r * c.r)){
        return true;
    } else {
        return false;
    }
}

void conv2D(const uchar *In,
                     uchar *Out,
                     float *k) {

    size_t x = get_global_id(0);
    size_t y = get_global_id(1);
    size_t i = (W * y + x) * 3;

    float sumR = 0;
    float sumG = 0;
    float sumB = 0;

    float kv = 0;

    int kRow;
    int px;
    int py;
    int refX = (int)x - (int)(KW / 2);
    int refY = (int)y - (int)(KH / 2);

    for(int yK = 0; yK < KH; yK ++) {
        kRow = KH * yK;

        for(int xK = 0; xK < KW; xK ++) {
            kv = k[kRow + xK];

            px = refX + xK;
            py = refY + yK;

            if(px < 0) {
                px = 0;
            } else if(px >= W) {
                px = W - 1;
            }

            if(py < 0) {
                py = 0;
            } else if(py >= H) {
                py = H - 1;
            }

            int ii = (W * py + px) * 3;

            sumR += kv * In[ii + 0];
            sumG += kv * In[ii + 1];
            sumB += kv * In[ii + 2];
        }
    }

    Out[i + 0] = (sumR > 255)? 255: sumR;
    Out[i + 1] = (sumG > 255)? 255: sumG;
    Out[i + 2] = (sumB > 255)? 255: sumB;
}

#define N_CIRCLES 3
#define EFFECT_OUTSIDE true

__kernel void pixelKernel(const __global uchar *In,
                     __global uchar *Out,
                     __global float *k) {

    circle_t circle1 = {
        .x = 250,
        .y = 250,
        .r = 200
    };
    
    circle_t circle2 = {
        .x = 550,
        .y = 500,
        .r = 70
    };
    
    circle_t circle3 = {
        .x = 750,
        .y = 300,
        .r = 120
    };
    
    circle_t circles[N_CIRCLES] = {
        circle1,
        circle2,
        circle3
    };
    
    bool insideCircles = false;
    
    for(size_t i = 0; i < N_CIRCLES; i ++) {
        if(isInsideCircle(circles[i], X, Y)) {
            insideCircles = true;
            
            break;
        }
    }

    if(insideCircles == EFFECT_OUTSIDE) {
        OUT_RED = IN_RED;
        OUT_GREEN = IN_GREEN;
        OUT_BLUE = IN_BLUE;
    } else {
        conv2D(In, Out, k);
    }
}
