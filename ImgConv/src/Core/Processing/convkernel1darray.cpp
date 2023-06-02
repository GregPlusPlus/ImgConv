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

#include "convkernel1darray.h"

using namespace Core::Processing;

ConvKernel1DArray::ConvKernel1DArray(const QVector<QVector<float> > &k) {
    m_s = k.size() * k[0].size();
    m_k = new float[m_s];

    for(int y = 0; y < k.size(); y ++) {
        for(int x = 0; x < k[0].size(); x ++) {
            size_t i = (y * k[0].size()) + x;

            m_k[i] = k[y][x];
        }
    }
}

ConvKernel1DArray::~ConvKernel1DArray() {
    if(m_k) {
        delete[] m_k;
    }
}

size_t ConvKernel1DArray::size() const {
    return m_s;
}

size_t ConvKernel1DArray::buffSize() const {
    return size() * sizeof(float);
}

float *ConvKernel1DArray::getKArray() const {
    return m_k;
}
