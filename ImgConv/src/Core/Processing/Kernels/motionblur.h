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

#ifndef MOTIONBLUR_H
#define MOTIONBLUR_H

#include <QImage>
#include <QPainter>

#include "Core/Processing/convkernel.h"
#include "Core/Utils/utils.h"

namespace ConvKernels {
class MotionBlur : public ConvKernel
{
    Q_OBJECT
public:
    explicit MotionBlur(QObject *parent = nullptr);

    QVector<QVector<float>> getMat() const;
    float getScalar() const;
    QString getName() const;

private slots:
    void settingChanged();

private:
    QVector<QVector<float>> m_k;
    float m_s;

private:
    ConvKenrelSetting *m_sizeSetting;
    ConvKenrelSetting *m_angleSetting;
};
}

#endif // MOTIONBLUR_H
