#include "sharpen.h"

ConvKernels::Sharpen::Sharpen(QObject *parent)
    : ConvKernel{parent} {

}

QVector<QVector<float> > ConvKernels::Sharpen::getMat() const {
    static QVector<QVector<float>> k = {
        {0, -1,  0},
        {-1, 5, -1},
        {0, -1,  0}
    };

    return k;
}

float ConvKernels::Sharpen::getScalar() const {
    return 1.f;
}

QString ConvKernels::Sharpen::getName() const {
    return tr("Sharpen");
}
