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

using namespace Core::Processing::ConvKernels;

#define KERNEL_PATH_SETTING_NAME        "Kernel"
#define NORMALIZE_KERNEL_SETTING_NAME   "Normalize kernel"

Custom::Custom(QObject *parent)
    : ConvKernel{parent} {
    m_kernelFileSetting = new ConvKernelSetting(KERNEL_PATH_SETTING_NAME, tr("Open kernel as image file"),
                                                tr("CSV file (*.csv *.txt);;" \
                                                   "Image files (%1)")
                                                .arg(generateSupportedImgFilesStringFilter()),
                                                QString(), this);

    m_normalizeSetting = new ConvKernelSetting(NORMALIZE_KERNEL_SETTING_NAME,
                                               true,
                                               this);

    connect(m_kernelFileSetting, &ConvKernelSetting::valueChanged, this, &ConvKernels::Custom::updateFilter);
    connect(m_normalizeSetting, &ConvKernelSetting::valueChanged, this, &ConvKernels::Custom::updateFilter);

    addSetting(m_kernelFileSetting);
    addSetting(m_normalizeSetting);
}

QVector<QVector<float> > Custom::getMat() const {
    return m_k;
}

float Custom::getScalar() const {
    return m_s;
}

QString Custom::getName() const {
    return tr("Custom kernel");
}

void Custom::updateSettingsNames() {
    m_kernelFileSetting->setName(tr(KERNEL_PATH_SETTING_NAME));
    m_normalizeSetting->setName(tr(NORMALIZE_KERNEL_SETTING_NAME));
}

QString Custom::getDescription() {
    return tr("Allows to load a custom convolution kernel matrix from a CSV or an image file.<br>" \
              "<ul>" \
              "<li><strong>Kernel : </strong>The file to be loaded as a kernel.</li>" \
              "<li><strong>Normalize kernel : </strong>Should the kernel be normalized (sum of coefs = 1).</li>" \
              "</ul><br>" \
              "When using an image as the matrix, the mapping is the following :" \
              "<ul>" \
              "<li>0 → -1</li>" \
              "<li>128 → 0</li>" \
              "<li>255 → +1</li>" \
              "</ul>");
}

void Custom::select() {
    updateFilter();
}

void Custom::importMatrix() {
    QString fn = m_kernelFileSetting->valS();

    if(fn.isEmpty()) {
        return;
    }

    QString fileSuffix = QFileInfo(fn).suffix();

    if(supportedImgFilesList().contains(fileSuffix)) {
        QImage kImg(fn);

        Utils::imageToMatrix(m_k, kImg);
    } else {
        QFile f(fn);

        if(!f.open(QFile::ReadOnly)) {
            f.close();
            return;
        }

        QVector<QVector<float>> k(0);

        QString in = f.readAll();

        if(!Utils::CSVToMatrix(k, in)) {
            m_k = k;

            f.close();

            return;
        }

        m_k = k;

        f.close();
    }
}

void Custom::updateFilter() {
    float s = 1.f;

    importMatrix();

    if(m_normalizeSetting->valB()) {
        s = 1.f/Utils::matrixSumCoef(m_k);
    }

    m_s = s;
}

QStringList Custom::supportedImgFilesList() {
    static QStringList supportedImgFiles = {
        "png", "jpg", "jpeg", "bmp", "gif"
    };

    return supportedImgFiles;
}

QString Custom::generateSupportedImgFilesStringFilter() {
    QString str;
    QStringList formats = supportedImgFilesList();

    for(const QString &format : formats) {
        str += "*." + format + " ";
    }

    return str;
}
