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

inline void conv2D(const uchar *In,
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

#endif //CONVOLUTION_H
