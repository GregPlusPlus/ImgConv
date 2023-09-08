/**
 ** This file is part of the ImgConv project.
 ** Copyright 2022-2023 Grégoire BOST <bostgregoire@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "common.h"

#if (!defined(PIXEL_BOUNDARY_FIXED_COLOR)) && \
    (!defined(PIXEL_BOUNDARY_CLAMP)) && \
    (!defined(PIXEL_BOUNDARY_WRAP))
#define PIXEL_BOUNDARY_CLAMP
#endif

inline void conv2D(const uchar *In,
                   uchar *Out,
                   const float *k) {

    float sum[3] = {0, 0, 0};

    float kv = 0;

    int kRow;
    int px;
    int py;
    int refX = (int)X - (int)(KW / 2);
    int refY = (int)Y - (int)(KH / 2);

    for(int yK = 0; yK < KH; yK ++) {
        kRow = KH * yK;

        for(int xK = 0; xK < KW; xK ++) {
            kv = k[kRow + xK];

            px = refX + xK;
            py = refY + yK;
            
            int ii;

            if( (px >= 0) &&
                (py >= 0) &&
                (px < W) &&
                (py < H)) {

                ii = INDEX_AT(px, py);

                sum[0] += kv * In[ii + 0];
                sum[1] += kv * In[ii + 1];
                sum[2] += kv * In[ii + 2];
            } else {
#if     defined(PIXEL_BOUNDARY_FIXED_COLOR)
                sum[0] += kv * PIXEL_BOUNDARY_COLOR.r;
                sum[1] += kv * PIXEL_BOUNDARY_COLOR.g;
                sum[2] += kv * PIXEL_BOUNDARY_COLOR.b;
#elif   defined(PIXEL_BOUNDARY_CLAMP)
                if(px < 0) {
                    px = 0;
                } else if(px >= W) {
                    px = (W - 1);
                }

                if(py < 0) {
                    py = 0;
                } else if(py >= H) {
                    py = (H - 1);
                }

                ii = INDEX_AT(px, py);

                sum[0] += kv * In[ii + 0];
                sum[1] += kv * In[ii + 1];
                sum[2] += kv * In[ii + 2];
#elif   defined(PIXEL_BOUNDARY_WRAP)
                if(px < 0) {
                    px = ((W - 1) - (W % px));
                } else if(px >= W) {
                    px = ((W - 1)  % px);
                }

                if(py < 0) {
                    py = ((H - 1) - (H % py));
                } else if(py >= H) {
                    py = ((H - 1) % py);
                }

                ii = INDEX_AT(px, py);

                sum[0] += kv * In[ii + 0];
                sum[1] += kv * In[ii + 1];
                sum[2] += kv * In[ii + 2];
#endif
            }
        }
    }

    sum[0] = (sum[0] < 0)? 0: sum[0];
    sum[1] = (sum[1] < 0)? 0: sum[1];
    sum[2] = (sum[2] < 0)? 0: sum[2];
    sum[0] = (sum[0] > 255)? 255: sum[0];
    sum[1] = (sum[1] > 255)? 255: sum[1];
    sum[2] = (sum[2] > 255)? 255: sum[2];

    writePixelColorAtCurrentCoord(Out, (color_t) {
        .r = sum[0],
        .g = sum[1],
        .b = sum[2]
    });
}

#endif //CONVOLUTION_H
