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

#ifndef CONVKERNEL1DARRAY_H
#define CONVKERNEL1DARRAY_H

#include <QObject>
#include <QSize>

#include <QDebug>

namespace Core::Processing {
class ConvKernel1DArray : public QObject
{
Q_OBJECT
public:
    explicit ConvKernel1DArray(const QVector<QVector<float>> &k);
    virtual ~ConvKernel1DArray();

    size_t size() const;
    size_t buffSize() const;

    float *getKArray() const;

signals:

private:
    float *m_k = nullptr;
    size_t m_s;

};
}

#endif // CONVKERNEL1DARRAY_H
