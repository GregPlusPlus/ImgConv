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

#include "unity.h"

using namespace Core::Processing::ConvKernels;

#define GAIN_SETTING_NAME "Gain"

Unity::Unity(QObject *parent)
    : ConvKernels::ConvKernel{parent} {
    m_scalar = new ConvKernelSetting(GAIN_SETTING_NAME,
                        true, 0.f,
                        false, 0.f,
                        1.f,
                        this);

    addSetting(m_scalar);
}

QVector<QVector<float> > Unity::getMat() const {
    static QVector<QVector<float>> k = {
        {1}
    };

    return k;
}

float Unity::getScalar() const {
    return m_scalar->valF();
}

QString Unity::getName() const {
    return tr("Unity kernel");
}

void Unity::updateSettingsNames() {
    m_scalar->setName(tr(GAIN_SETTING_NAME));
}

QString Unity::getDescription() {
    return tr("Applies a Unity convolution matrix." \
              "<ul>" \
              "<li><strong>Gain : </strong>Adjust the gain of the image.</li>" \
              "</ul>");
}
