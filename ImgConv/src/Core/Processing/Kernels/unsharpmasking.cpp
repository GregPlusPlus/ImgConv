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

#include "unsharpmasking.h"

using namespace Core::Processing::ConvKernels;

UnsharpMasking::UnsharpMasking(QObject *parent)
    : ConvKernel{parent} {

}

QVector<QVector<float> > UnsharpMasking::getMat() const {
    static QVector<QVector<float>> k = {
        {1,  4,    6,  4, 1},
        {4, 16,   24, 16, 4},
        {6, 24, -476, 24, 6},
        {4, 16,   24, 16, 4},
        {1,  4,    6,  4, 1}
    };

    return k;
}

float UnsharpMasking::getScalar() const {
    return -1.f/256.f;
}

QString UnsharpMasking::getName() const {
    return tr("Unsharp masking");
}

QString UnsharpMasking::getDescription() {
    return tr("Applies the <i>Unsharp Masking (USM)</i> effect. This effect increases the edge's contrast, " \
              "and is an improved version of the <i>Sharpen</i> effect.<br><br>" \
              "This effect doesn't have any parameters to tweak.");
}
