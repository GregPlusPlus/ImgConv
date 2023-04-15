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

#ifndef COMMON_H
#define COMMON_H

#define X                   (get_global_id(0))
#define Y                   (get_global_id(1))

#define INDEX_AT(_x, _y)    ((W * _y + _x) * 3)
#define CURR_PIX_INDEX      (INDEX_AT(X, Y))

#define INDEX2X(_i)         (_i % W)
#define INDEX2Y(_i)         (_i / W)
#define CURR_INDEX2X        (INDEX2X(CURR_PIX_INDEX))
#define CURR_INDEX2Y        (INDEX2Y(CURR_PIX_INDEX))

#define RED_OFFSET          (0)
#define GREEN_OFFSET        (1)
#define BLUE_OFFSET         (2)

#define RED(_p, _x, _y)     (_p[INDEX_AT(_x, _y) + RED_OFFSET])
#define GREEN(_p, _x, _y)   (_p[INDEX_AT(_x, _y) + GREEN_OFFSET])
#define BLUE(_p, _x, _y)    (_p[INDEX_AT(_x, _y) + BLUE_OFFSET])
#define CURR_RED(_p)        (RED(_p, X, Y))
#define CURR_GREEN(_p)      (GREEN(_p, X, Y))
#define CURR_BLUE(_p)       (BLUE(_p, X, Y))

typedef struct {
    size_t x;
    size_t y;
} coord2D_t;

typedef struct {
    uchar r;
    uchar g;
    uchar b;
} color_t;

inline coord2D_t getCurrentPixelCoord(void) {
    coord2D_t c = {
        .x = X,
        .y = Y
    };

    return c;
}

inline coord2D_t index2Coord(size_t i) {
    coord2D_t c = {
        .x = INDEX2X(i),
        .y = INDEX2Y(i)
    };

    return c;
}

inline color_t pixelColor(uchar *img, coord2D_t coord) {
    color_t c = {
        .r = RED(img,   coord.x, coord.y),
        .g = GREEN(img, coord.x, coord.y),
        .b = BLUE(img,  coord.x, coord.y)
    };

    return c;
}

inline color_t pixelColorAtCurrentCoord(uchar *img) {
    return pixelColor(img, getCurrentPixelCoord());
}

inline void writePixelColor(uchar *img, coord2D_t coord, color_t color) {
    RED(img, coord.x, coord.y) = color.r;
    GREEN(img, coord.x, coord.y) = color.g;
    BLUE(img, coord.x, coord.y) = color.b;
}

inline void writePixelColorAtCurrentCoord(uchar *img, color_t color) {
    writePixelColor(img, getCurrentPixelCoord(), color);
}

#endif //COMMON_H
