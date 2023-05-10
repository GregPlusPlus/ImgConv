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

#ifndef UTILS_H
#define UTILS_H

#include <QVector>
#include <QImage>

#include <QFile>
#include <QTextStream>

#include <QRegularExpression>

namespace Utils {
    void scaleMatrix(QVector<QVector<float>> &v, float c);
    void imageToMatrix(QVector<QVector<float>> &m, QImage &i);
    bool CSVToMatrix(QVector<QVector<float>> &m, QString &in);
    float matrixSumCoef(const QVector<QVector<float>> &m);
    QString matrixToBoxString(const QVector<QVector<float>> &mat);
    QString matrixToCSVString(const QVector<QVector<float>> &mat);
}

#endif // UTILS_H
