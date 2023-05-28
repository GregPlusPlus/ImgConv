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

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/Processing/convkernel1darray.h"

#include <QImage>

namespace Processing {
namespace Algorithms {

struct Histogram {
    QVector<size_t> r;
    QVector<size_t> g;
    QVector<size_t> b;
};

    bool conv2D(OCLWrapper *ocl, const QImage &in, QImage &out, const QVector<QVector<float>> &k);
    bool computeHistogram(OCLWrapper *ocl, const QImage &in, Histogram &hist);
}
}

#endif // ALGORITHMS_H
