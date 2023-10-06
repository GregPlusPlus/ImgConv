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

#include "emboss.h"

using namespace Core::Processing::ConvKernels;

#define SIZE_SETTING_NAME       "Size"
#define SMOOTHING_SETTING_NAME  "Smoothing"

Emboss::Emboss(QObject *parent)
    : ConvKernel{parent} {
    m_sizeSetting = new ConvKernelSetting(SIZE_SETTING_NAME,
                        true, 1,
                        true, 128,
                        1,
                        this);

    m_smoothSetting = new ConvKernelSetting(SMOOTHING_SETTING_NAME,
                                            true, 1.f,
                                            true, 100.f,
                                            1.f,
                                            this);

    connect(m_sizeSetting, &ConvKernelSetting::valueChanged, this, &Emboss::settingChanged);
    connect(m_smoothSetting, &ConvKernelSetting::valueChanged, this, &Emboss::settingChanged);

    addSetting(m_sizeSetting);
    addSetting(m_smoothSetting);

    settingChanged();
}

QVector<QVector<float> > Emboss::getMat() const {
    return m_k;
}

float Emboss::getScalar() const {
    return m_s;
}

QString Emboss::getName() const {
    return tr("Emboss");
}

void Emboss::updateSettingsNames() {
    m_sizeSetting->setName(tr(SIZE_SETTING_NAME));
    m_smoothSetting->setName(tr(SMOOTHING_SETTING_NAME));
}

QString Emboss::getDescription() {
    return tr("Applies an <i>Emboss</i> effect.<br>" \
              "<ul>" \
              "<li><strong>Size : </strong>The \"witdh\" of the emboss effect along the edges. The bigger the number, the stronger the effect.</li>" \
              "<li><strong>Smoothing : </strong>How much the effect must be smoothed (increases the center pixel's ponderation).</li>" \
              "</ul>");
}

void Emboss::settingChanged() {
    size_t kSize = m_sizeSetting->valInt() * 2;

    if((kSize % 2) == 0) {
        kSize += 1;
    }

    QVector<QVector<float>> k;
    k.resize(kSize);

    for(uint32_t y = 0; y < kSize; y ++) {
        k[y].resize(kSize);
        for(uint32_t x = 0; x < kSize; x ++) {
            if((x == y) && (x < (kSize / 2))) {
                k[y][x] = -2.f;
            } else if((x == y) && (x > (kSize / 2))) {
                k[y][x] = 2.f;
            } else if((y == (kSize / 2)) && (x < (kSize / 2))) {
                k[y][x] = -1.f;
            } else if((y == (kSize / 2)) && (x > (kSize / 2))) {
                k[y][x] = 1.f;
            } else if((x == (kSize / 2)) && (y < (kSize / 2))) {
                k[y][x] = -1.f;
            } else if((x == (kSize / 2)) && (y > (kSize / 2))) {
                k[y][x] = 1.f;
            }
        }
    }

    k[(kSize / 2)][(kSize / 2)] = m_smoothSetting->valF();

    m_k = k;
    m_s = 1.f/m_smoothSetting->valF();
}
