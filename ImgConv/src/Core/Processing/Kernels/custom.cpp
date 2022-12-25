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

#include "custom.h"

ConvKernels::Custom::Custom(QObject *parent)
    : ConvKernel{parent} {
    m_normalizeSetting = new ConvKenrelSetting(tr("Normalize kernel"),
                                               true,
                                               this);

    connect(m_normalizeSetting, &ConvKenrelSetting::valueChanged, this, &Custom::settingChanged);

    addSetting(m_normalizeSetting);
}

QVector<QVector<float> > ConvKernels::Custom::getMat() const {
    return m_k;
}

float ConvKernels::Custom::getScalar() const {
    return m_s;
}

QString ConvKernels::Custom::getName() const {
    return tr("Custom kernel");
}

void ConvKernels::Custom::select() {
    QString fn = QFileDialog::getOpenFileName(nullptr, tr("Open kernel as image file"), QString(),
                                              tr("Image files (*.png *.jpg *.bmp)"));

    if(fn.isEmpty()) {
        return;
    }

    QImage kImg(fn);

    Utils::imageToMatrix(m_k, kImg);

    settingChanged();
}

void ConvKernels::Custom::settingChanged() {
    float s = 1.f;

    if(m_normalizeSetting->valB()) {
        s = 1.f/Utils::matrixSumCoef(m_k);
    }

    m_s = s;
}
