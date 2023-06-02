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

namespace Core::Processing::Algorithms {
class Histogram {

public:
    QVector<size_t> r;
    QVector<size_t> g;
    QVector<size_t> b;

    QVector<size_t> getMax() {
        QVector<size_t> max = {0, 0, 0};

        for(qsizetype i = 0; i < r.size(); i ++) {
            if(r.at(i) > max[0]) {
                max[0] = r.at(i);
            }
        }

        for(qsizetype i = 0; i < g.size(); i ++) {
            if(g.at(i) > max[1]) {
                max[1] = g.at(i);
            }
        }

        for(qsizetype i = 0; i < b.size(); i ++) {
            if(b.at(i) > max[2]) {
                max[2] = b.at(i);
            }
        }

        return max;
    };

    QVector<size_t> getSum() {
        QVector<size_t> sum = {0, 0, 0};

        for(qsizetype i = 0; i < r.size(); i ++) {
            sum[0] += r.at(i);
        }

        for(qsizetype i = 0; i < g.size(); i ++) {
            sum[1] += g.at(i);
        }

        for(qsizetype i = 0; i < b.size(); i ++) {
            sum[2] += b.at(i);
        }

        return sum;
    };

    Processing::Algorithms::Histogram getCDF() const {
        Algorithms::Histogram cdf = *this;

        for(size_t i = 1; i < 256; i ++) {
            cdf.r[i] = cdf.r[i] + cdf.r[i - 1];
            cdf.g[i] = cdf.g[i] + cdf.g[i - 1];
            cdf.b[i] = cdf.b[i] + cdf.b[i - 1];
        }

        return cdf;
    }
};

    bool conv2D(OCLWrapper *ocl, const QImage &in, QImage &out, const QVector<QVector<float>> &k);
    bool computeHistogram(OCLWrapper *ocl, const QImage &in, Histogram &hist);
    bool applyCorrection(OCLWrapper *ocl, const QImage &in, QImage &out, const Histogram &cdf);
}

#endif // ALGORITHMS_H
