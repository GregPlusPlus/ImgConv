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

#include "sharpen.h"

ConvKernels::Sharpen::Sharpen(QObject *parent)
    : ConvKernel{parent} {
    m_strengthSetting = new ConvKenrelSetting(tr("Contour strength"),
                        true, 1,
                        true, 128,
                        1,
                        this);

    m_smoothSetting = new ConvKenrelSetting(tr("Smoothing"),
                                            true, -.99f,
                                            true, 100.f,
                                            1.f,
                                            this);

    connect(m_strengthSetting, &ConvKenrelSetting::valueChanged, this, &Sharpen::settingChanged);
    connect(m_smoothSetting, &ConvKenrelSetting::valueChanged, this, &Sharpen::settingChanged);

    addSetting(m_strengthSetting);
    addSetting(m_smoothSetting);

    settingChanged();
}

QVector<QVector<float> > ConvKernels::Sharpen::getMat() const {
    return m_k;
}

float ConvKernels::Sharpen::getScalar() const {
    return m_s;
}

QString ConvKernels::Sharpen::getName() const {
    return tr("Sharpen");
}

QString ConvKernels::Sharpen::getDescription() {
    return tr("Applies a <i>Sharpen</i> effect. This effect increases the edge's contrast.<br>" \
              "<ul>" \
              "<li><strong>Contour strength : </strong>How strong the effect is. As the contrast increases, the noise does as well.</li>" \
              "<li><strong>Smoothing : </strong>How much the effect must be smoothed (increases the center pixel's ponderation).</li>" \
              "</ul>");
}

void ConvKernels::Sharpen::settingChanged() {
    size_t kSize = m_strengthSetting->val() * 2;

    if((kSize % 2) == 0) {
        kSize += 1;
    }

    QVector<QVector<float>> k;
    k.resize(kSize);

    for(uint32_t y = 0; y < kSize; y ++) {
        k[y].resize(kSize);
        for(uint32_t x = 0; x < kSize; x ++) {
            if(y == (kSize / 2)) {
                k[y][x] = -1.f;
            } else if(x == (kSize / 2)) {
                k[y][x] = -1.f;
            }
        }
    }

    k[kSize / 2][kSize / 2] = m_strengthSetting->val() * 4 + 1 + m_smoothSetting->valF();

    m_k = k;
    m_s = 1.f/(1.f + m_smoothSetting->valF());
    //m_s = 1;
}
