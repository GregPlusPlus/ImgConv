#ifndef UTILS_H
#define UTILS_H

#include <QVector>
#include <QImage>

namespace Utils {
    void scaleMatrix(QVector<QVector<float>> &v, float c);
    void imageToMatrix(QVector<QVector<float>> &m, QImage &i);
    float matrixSumCoef(const QVector<QVector<float>> &m);
}

#endif // UTILS_H
