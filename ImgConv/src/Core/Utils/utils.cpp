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

#include "utils.h"

void Utils::scaleMatrix(QVector<QVector<float>> &v, float c) {
    for(QVector<float> &l : v) {
        for(float &e : l) {
            e = e * c;
        }
    }
}

void Utils::imageToMatrix(QVector<QVector<float>> &m, QImage &i) {
    m.resize(i.height());

    for(int y = 0; y < i.height(); y ++) {
        m[y].resize(i.width());
        for(int x = 0; x < i.width(); x ++) {
            float v = (float)(qRed(i.pixel(x, y)) - 128.f) / 128.f;

            m[y][x] = v;
        }
    }
}

float Utils::matrixSumCoef(const QVector<QVector<float>> &m) {
    float s = 0;

    for(const QVector<float> &l : m) {
        for(float v : l) {
            s += v;
        }
    }

    return s;
}
