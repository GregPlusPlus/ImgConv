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

#include "utils.h"

void Utils::scaleMatrix(QVector<QVector<float>> &v, float c) {
    for(QVector<float> &l : v) {
        for(float &e : l) {
            e = e * c;
        }
    }
}

void Utils::imageToMatrix(QVector<QVector<float>> &m, QImage &i) {
    m.resize(i.height());

    for(int y = 0; y < i.height(); y ++) {
        m[y].resize(i.width());
        for(int x = 0; x < i.width(); x ++) {
            float v = (float)(qRed(i.pixel(x, y)) - 128.f) / 128.f;

            m[y][x] = v;
        }
    }
}

float Utils::matrixSumCoef(const QVector<QVector<float>> &m) {
    float s = 0;

    for(const QVector<float> &l : m) {
        for(float v : l) {
            s += v;
        }
    }

    return s;
}

QString Utils::matrixToBoxString(const QVector<QVector<float> > &mat) {
    QString str;

    QVector<int> maxColLen(mat[0].size());

    for(int i = 0; i < mat.size(); i ++) {
        for(int j = 0; j < mat[0].size(); j ++) {
            QString numberAsStr = QString::number(mat[i][j]);

            if(numberAsStr.size() > maxColLen[j]) {
                maxColLen[j] = numberAsStr.size();
            }
        }
    }

    str += "┌";

    for(int j = 0; j < mat[0].size(); j ++) {
        str += QString("─").repeated(maxColLen[j] + 2);

        if(j < (mat[0].size() - 1)) {
            str += "┬";
        }
    }

    str += "┐\n";

    for(int i = 0; i < mat.size(); i ++) {
        str += "│ ";

        for(int j = 0; j < mat[0].size(); j ++) {
            QString numberAsStr = QString::number(mat[i][j]);
            int nSpaces = maxColLen[j] - numberAsStr.size();

            str += numberAsStr + QString(" ").repeated(nSpaces) + " │ ";
        }

        str += "\n";

        if(i < (mat.size() - 1)) {
            str += "├";

            for(int j = 0; j < mat[0].size(); j ++) {
                str += QString("─").repeated(maxColLen[j] + 2);

                if(j < (mat[0].size() - 1)) {
                    str += "┼";
                }
            }

            str += "┤\n";
        }
    }

    str += "└";

    for(int j = 0; j < mat[0].size(); j ++) {
        str += QString("─").repeated(maxColLen[j] + 2);

        if(j < (mat[0].size() - 1)) {
            str += "┴";
        }
    }

    str += "┘";

    return str;
}
