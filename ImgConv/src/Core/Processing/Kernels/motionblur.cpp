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

#include "motionblur.h"

using namespace Core::Processing::ConvKernels;

#define SIZE_SETTING_NAME   "Size"
#define ANGLE_SETTING_NAME  "Angle"

MotionBlur::MotionBlur(QObject *parent)
    : ConvKernel{parent} {
    m_sizeSetting = new ConvKernelSetting(SIZE_SETTING_NAME,
                        true, 1,
                        true, 128,
                        10,
                        this);

    m_angleSetting = new ConvKernelSetting(ANGLE_SETTING_NAME,
                         true, 0,
                         true, 360,
                         0,
                         this);

    connect(m_sizeSetting, &ConvKernelSetting::valueChanged, this, &MotionBlur::settingChanged);
    connect(m_angleSetting, &ConvKernelSetting::valueChanged, this, &MotionBlur::settingChanged);

    addSetting(m_sizeSetting);
    addSetting(m_angleSetting);

    settingChanged();
}

QVector<QVector<float> > MotionBlur::getMat() const {
    return m_k;
}

float MotionBlur::getScalar() const {
    return m_s;
}

QString MotionBlur::getName() const {
    return tr("Motion blur");
}

void MotionBlur::updateSettingsNames() {
    m_sizeSetting->setName(tr(SIZE_SETTING_NAME));
    m_angleSetting->setName(tr(ANGLE_SETTING_NAME));
}

QString MotionBlur::getDescription() {
    return tr("Applies a <i>Motion Blur</i> effect.<br>" \
              "This effect mimics a camera's shutter exposure time on moving objects." \
              "<ul>" \
              "<li><strong>Size : </strong>The size of the movement effect. " \
              "In reality, it is determined by the shutter speed as well as the speed of the moving object.</li>" \
              "<li><strong>Angle : </strong>Simulates the direction of the moving object.</li>" \
              "</ul>");
}

void MotionBlur::settingChanged() {
    size_t kSize = m_sizeSetting->valInt() * 2;

    if((kSize % 2) == 0) {
        kSize += 1;
    }

    QVector<QVector<float>> k;

    QImage kImg(kSize, kSize, QImage::Format_ARGB32);
    kImg.fill(QColor(128, 128, 128));

    QPainter p(&kImg);
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(kSize / 2, kSize / 2);

    p.setPen(QColor(255, 255, 255));
    p.rotate(m_angleSetting->valInt());
    p.drawLine(-kSize, 0, kSize, 0);

    Utils::imageToMatrix(k, kImg);

    m_k = k;
    m_s = 1.f / Utils::matrixSumCoef(k);
}
