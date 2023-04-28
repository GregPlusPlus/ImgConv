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

#ifndef RANDOM_H
#define RANDOM_H

#include "common.h"

#define RSEED VRSEED
#define RAND_MAX ((uint)0xFFFFFFFF)

ulong state = 0;

static uint rseed[4] = RSEED;

inline void srand() {
    state = rseed[0] + ((CURR_PIX_INDEX * 89657654) ^ rseed[1]);
    state = state ^ (state << 11);
    state = rseed[1] ^ (rseed[1] >> 19) ^ (state ^ (state >> 8));
    state ^= ((ulong)rseed[2] << 32 | rseed[3]);
}

inline uint rand() {
    state = (ulong)(state * 6364136223846793005UL + 1);

    return (uint)(state >> 32) & 0x7FFFFFFF;
}

inline float randf() {
    return (float)(rand()) / RAND_MAX;
}

inline float randMax(float max) {
    return max * randf();
}

inline float randIn(float min, float max) {
    return min + randMax(max - min);
}

inline float randCenter(float max) {
    return randMax(max) - (max / 2);
}

#endif //RANDOM_H
