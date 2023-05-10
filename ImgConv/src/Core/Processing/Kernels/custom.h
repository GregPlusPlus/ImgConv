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

#ifndef CUSTOM_H
#define CUSTOM_H

#include <QFileDialog>
#include <QImage>

#include <QFileInfo>

#include "Core/Processing/convkernel.h"
#include "Core/Utils/utils.h"

namespace ConvKernels {
class Custom : public ConvKernel {
    Q_OBJECT
public:
    explicit Custom(QObject *parent = nullptr);

    QVector<QVector<float>> getMat() const;
    float getScalar() const;
    QString getName() const;
    QString getDescription();

public slots:
    void select();

private slots:
    void importMatrix();
    void updateFilter();

private:
    QStringList supportedImgFilesList();
    QString generateSupportedImgFilesStringFilter();

private:
    ConvKenrelSetting *m_kernelFileSetting;
    ConvKenrelSetting *m_normalizeSetting;
    QVector<QVector<float>> m_k;
    float m_s;
};
}

#endif // CUSTOM_H
