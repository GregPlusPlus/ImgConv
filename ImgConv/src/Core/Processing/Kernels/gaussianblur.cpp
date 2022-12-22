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

#include "gaussianblur.h"

#include <cmath>

ConvKernels::GaussianBlur::GaussianBlur(QObject *parent)
    : ConvKernels::ConvKernel{parent}{
    m_sizeSetting = new ConvKenrelSetting(tr("Size"),
                        true, 1,
                        true, 128,
                        1,
                        this);

    m_stddevSetting = new ConvKenrelSetting(tr("Std Dev"),
                          true, 1.f,
                          false, 0.f,
                          10.f,
                          this);

    connect(m_sizeSetting, &ConvKenrelSetting::valueChanged, this, &GaussianBlur::settingChanged);
    connect(m_stddevSetting, &ConvKenrelSetting::valueChanged, this, &GaussianBlur::settingChanged);

    addSetting(m_sizeSetting);
    addSetting(m_stddevSetting);

    settingChanged();
}

QVector<QVector<float> > ConvKernels::GaussianBlur::getMat() const {
    return m_k;
}

float ConvKernels::GaussianBlur::getScalar() const {
    return m_s;
}

QString ConvKernels::GaussianBlur::getName() const {
    return tr("Gaussian blur");
}

void ConvKernels::GaussianBlur::settingChanged() {
    size_t kSize = m_sizeSetting->val() * 2;

    if((kSize % 2) == 0) {
        kSize += 1;
    }

    float s = 0;
    QVector<QVector<float>> k;
    k.resize(kSize);

    for(uint32_t y = 0; y < kSize; y ++) {
        k[y].resize(kSize);
        for(uint32_t x = 0; x < kSize; x ++) {
            int kx = (kSize / 2) - x;
            int ky = (kSize / 2) - y;
            k[y][x] = 1.f/(2*M_PI*(float)pow(m_stddevSetting->valF(), 2))
                    *exp(-(float)(kx*kx+ky*ky)/(float)(2.f*pow(m_stddevSetting->valF(),2)));
            s += k[y][x];
        }
    }

    m_k = k;
    m_s = 1.f/s;
}
