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

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QImage>
#include <QElapsedTimer>
#include <QVector>

#include "virtualthread.h"
#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/Processing/processing.h"

namespace Core::Threads {
class Histogram : public VirtualThread
{
    Q_OBJECT

public:
    Histogram(OCLWrapper *ocl, const QImage &original);

    void run() override;

signals:
    void finished(const Processing::Algorithms::Histogram &hist, qint64 et, bool res);

private:
    OCLWrapper *m_ocl;
    QImage m_original;
};
}

#endif // HISTOGRAM_H
