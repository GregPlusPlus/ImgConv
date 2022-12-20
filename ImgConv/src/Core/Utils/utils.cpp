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
            m[y][x] = qRed(i.pixel(x, y)) / 255.f;
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
