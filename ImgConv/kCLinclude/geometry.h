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

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "common.h"

typedef struct {
    size_t x;
    size_t y;
} geom_coord2D_t;

typedef struct {
    geom_coord2D_t c;
    size_t r;
} geom_circle_t;

inline bool isInsideCircle(geom_circle_t c, size_t x, size_t y) {
    return (((x - c.c.x) * (x - c.c.x) + (y - c.c.y) * (y - c.c.y)) <= (c.r * c.r));
}

inline bool isOnCircleBorder(geom_circle_t c, size_t x, size_t y, size_t bw) {
    return ((((x - c.c.x) * (x - c.c.x) + (y - c.c.y) * (y - c.c.y)) > ((c.r - bw) * (c.r - bw))) &&
            (((x - c.c.x) * (x - c.c.x) + (y - c.c.y) * (y - c.c.y)) < ((c.r + bw) * (c.r + bw))));
}

#endif //GEOMETRY_H
