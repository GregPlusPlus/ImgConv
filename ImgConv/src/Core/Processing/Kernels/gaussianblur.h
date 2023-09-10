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

#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "Core/Processing/convkernel.h"

namespace Core::Processing::ConvKernels {
class GaussianBlur : public ConvKernels::ConvKernel {
    Q_OBJECT

public:
    explicit GaussianBlur(QObject *parent = nullptr);

    QVector<QVector<float>> getMat() const;
    float getScalar() const;
    QString getName() const;
    QString getDescription();

private slots:
    void settingChanged();

private:
    QVector<QVector<float>> m_k;
    float m_s;

private:
    ConvKernelSetting *m_sizeSetting;
    ConvKernelSetting *m_stddevSetting;
};
}

#endif // GAUSSIANBLUR_H
