#include "ridge.h"

ConvKernels::Ridge::Ridge(QObject *parent)
    : ConvKernel{parent} {

}

QVector<QVector<float> > ConvKernels::Ridge::getMat() const {
    static QVector<QVector<float>> k = {
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
    };

    return k;
}

float ConvKernels::Ridge::getScalar() const {
    return 1.f;
}

QString ConvKernels::Ridge::getName() const {
    return tr("Ridge");
}
