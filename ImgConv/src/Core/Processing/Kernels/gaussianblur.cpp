#include "gaussianblur.h"

ConvKernels::GaussianBlur::GaussianBlur(QObject *parent)
    : ConvKernels::ConvKernel{parent}{

}

QVector<QVector<float> > ConvKernels::GaussianBlur::getMat() const {
    static QVector<QVector<float>> k = {
        {1,  4,  6,  4, 1},
        {4, 16, 24, 16, 4},
        {6, 24, 36, 24, 6},
        {4, 16, 24, 16, 4},
        {1,  4,  6,  4, 1}
    };

    return k;
}

float ConvKernels::GaussianBlur::getScalar() const {
    return 1.f/256.f;
}

QString ConvKernels::GaussianBlur::getName() const {
    return tr("Gaussian blur");
}
