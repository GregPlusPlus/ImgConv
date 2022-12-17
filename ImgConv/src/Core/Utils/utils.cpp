#include "utils.h"

void Utils::scaleMatrix(QVector<QVector<float>> &v, float c) {
    for(QVector<float> &l : v) {
        for(float &e : l) {
            e = e * c;
        }
    }
}
