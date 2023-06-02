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

#include "ridge.h"

using namespace Core::Processing::ConvKernels;

Ridge::Ridge(QObject *parent)
    : ConvKernel{parent} {

}

QVector<QVector<float> > Ridge::getMat() const {
    static QVector<QVector<float>> k = {
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
    };

    return k;
}

float Ridge::getScalar() const {
    return 1.f;
}

QString Ridge::getName() const {
    return tr("Ridge");
}

QString Ridge::getDescription() {
    return tr("Applies an <i>Ridge</i> effect (a kind of edge-detection effect).<br><br>" \
              "This effect doesn't have any parameters to tweak.");
}
