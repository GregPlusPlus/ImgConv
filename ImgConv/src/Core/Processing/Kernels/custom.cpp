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
    static QStringList supportedImgFiles = {
        "png", "jpg", "jpeg", "bmp", "gif"
    };

    m_kernelFileSetting = new ConvKenrelSetting(tr("Kernel"), tr("Open kernel as image file"),
                                                tr("Image files (%1);;" \
                                                   "CSV file (*.csv *.txt)")
                                                .arg(generateSupportedImgFilesStringFilter(supportedImgFiles)),
                                                QString(), this);

    m_normalizeSetting = new ConvKenrelSetting(tr("Normalize kernel"),
                                               true,
                                               this);

    connect(m_kernelFileSetting, &ConvKenrelSetting::valueChanged, this, [=]() {
        QString fn = m_kernelFileSetting->valS();

        if(fn.isEmpty()) {
            return;
        }

        QString fileSuffix = QFileInfo(fn).suffix();

        if(supportedImgFiles.contains(fileSuffix)) {
            QImage kImg(fn);

            Utils::imageToMatrix(m_k, kImg);
        } else {
            QFile f(fn);

            if(!f.open(QFile::ReadOnly)) {
                f.close();
                return;
            }

            QVector<QVector<float>> k;

            QString in = f.readAll();

            if(!Utils::CSVToMatrix(k, in)) {
                f.close();
                return;
            }

            m_k = k;

            f.close();
        }

        updateFilter();
    });

    connect(m_normalizeSetting, &ConvKenrelSetting::valueChanged, this, &ConvKernels::Custom::updateFilter);

    addSetting(m_kernelFileSetting);
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

QString ConvKernels::Custom::getDescription() {
    return tr("Allows to load an image file as a custom convolution kernel matrix.<br>" \
              "<ul>" \
              "<li><strong>Kernel : </strong>The image to be loaded as a kernel.</li>" \
              "<li><strong>Normalize kernel : </strong>Should the kernel be normalized (sum of coefs = 1).</li>" \
              "</ul><br>" \
              "The mapping is the following :" \
              "<ul>" \
              "<li>0 => -1</li>" \
              "<li>128 => 0</li>" \
              "<li>255 => +1</li>" \
              "</ul>");
}

void ConvKernels::Custom::select() {
    updateFilter();
}

void ConvKernels::Custom::updateFilter() {
    float s = 1.f;

    if(m_normalizeSetting->valB()) {
        s = 1.f/Utils::matrixSumCoef(m_k);
    }

    m_s = s;
}

QString ConvKernels::Custom::generateSupportedImgFilesStringFilter(const QStringList &formats) {
    QString str;

    for(const QString &format : formats) {
        str += "*." + format + " ";
    }

    return str;
}
