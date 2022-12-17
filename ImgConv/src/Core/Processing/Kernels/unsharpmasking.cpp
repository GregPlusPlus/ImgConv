#include "unsharpmasking.h"

ConvKernels::UnsharpMasking::UnsharpMasking(QObject *parent)
    : ConvKernel{parent} {

}

QVector<QVector<float> > ConvKernels::UnsharpMasking::getMat() const {
    static QVector<QVector<float>> k = {
        {1,  4,    6,  4, 1},
        {4, 16,   24, 16, 4},
        {6, 24, -476, 24, 6},
        {4, 16,   24, 16, 4},
        {1,  4,    6,  4, 1}
    };

    return k;
}

float ConvKernels::UnsharpMasking::getScalar() const {
    return -1.f/256.f;
}

QString ConvKernels::UnsharpMasking::getName() const {
    return tr("Unsharp masking");
}
