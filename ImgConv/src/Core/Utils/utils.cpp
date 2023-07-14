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

namespace Core::Utils {
void scaleMatrix(QVector<QVector<float>> &v, float c) {
    for(QVector<float> &l : v) {
        for(float &e : l) {
            e = e * c;
        }
    }
}

void imageToMatrix(QVector<QVector<float>> &m, QImage &i) {
    m.resize(i.height());

    for(int y = 0; y < i.height(); y ++) {
        m[y].resize(i.width());
        for(int x = 0; x < i.width(); x ++) {
            float v = (float)(qRed(i.pixel(x, y)) - 128.f) / 128.f;

            m[y][x] = v;
        }
    }
}

float matrixSumCoef(const QVector<QVector<float>> &m) {
    float s = 0;

    for(const QVector<float> &l : m) {
        for(float v : l) {
            s += v;
        }
    }

    return s;
}

QString matrixToBoxString(const QVector<QVector<float> > &mat) {
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

QString matrixToCSVString(const QVector<QVector<float>> &mat) {
    QString str;

    for(int i = 0; i < mat.size(); i ++) {
        for(int j = 0; j < mat[0].size(); j ++) {
            QString numberAsStr = QString::number(mat[i][j]);

            str += numberAsStr;

            if(j < (mat[0].size() - 1)) {
                str += ", ";
            }
        }

        if(i < (mat.size() - 1)) {
            str += "\n";
        }
    }

    return str;
}

bool CSVToMatrix(QVector<QVector<float>> &m, QString &in) {
    static QRegularExpression regex("\\s*,\\s*");

    qsizetype prevLineLength = 0;
    QVector<QVector<float>> mat;

    QTextStream stream(&in);

    while (!stream.atEnd()) {
        QStringList line = stream.readLine().split(regex);

        if(line.isEmpty()) {
           return false;
        }

        if((prevLineLength != 0) && (prevLineLength != line.size())) {
            return false;
        }

        prevLineLength = line.size();

        mat.append(QVector<float>());

        for(const QString &tok : line) {
            bool ok = false;

            mat.last().append(tok.toFloat(&ok));

            if(!ok) {
                return false;
            }
        }
    }

    m = mat;

    return true;
}

uint8_t *imageToArray(const QImage &img) {
    int size = img.width() * img.height() * 3;

    QImage imgRGB888 = img;

    if(imgRGB888.format() != QImage::Format_RGB888) {
        imgRGB888.convertTo(QImage::Format_RGB888);
    }

    uint8_t *array = new uint8_t[size];

    for(int r = 0; r < imgRGB888.height(); r ++) {
        QRgb *line = reinterpret_cast<QRgb*>(imgRGB888.scanLine(r));
        memcpy(array + (r * imgRGB888.width() * 3), line, imgRGB888.width() * 3);
    }

    return array;
}

QImage arrayToImage(const uint8_t *array, const QSize &size) {
    QImage img = QImage(size, QImage::Format_RGB888);

    for(int r = 0; r < img.height(); r ++) {
        QRgb *line = reinterpret_cast<QRgb*>(img.scanLine(r));

        memcpy(line, array + (r * size.width() * 3), size.width() * 3);
    }

    return img;
}
}
