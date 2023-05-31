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

#ifndef PROCESSCONV2D_H
#define PROCESSCONV2D_H

#include <QImage>
#include <QElapsedTimer>
#include <QVector>

#include "virtualthread.h"
#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/Processing/processing.h"

namespace Threads {
class Conv2D : public QObject, public VirtualThread
{
    Q_OBJECT

public:
    Conv2D(OCLWrapper *ocl, const QImage &original, const QVector<QVector<float>> &mat);

    void run() override;

signals:
    void finished(const QImage &img, qint64 et, bool res);

private:
    OCLWrapper *m_ocl;
    QImage m_original;
    QVector<QVector<float>> m_mat;
};
}

#endif // PROCESSCONV2D_H
