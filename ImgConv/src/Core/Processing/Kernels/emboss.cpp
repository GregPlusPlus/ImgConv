#include "emboss.h"

ConvKernels::Emboss::Emboss(QObject *parent)
    : ConvKernel{parent} {

}

QVector<QVector<float> > ConvKernels::Emboss::getMat() const {
    static QVector<QVector<float>> k = {
        {-2, -1, 0},
        {-1,  1, 1},
        {0,   1, 2}
    };

    return k;
}

float ConvKernels::Emboss::getScalar() const {
    return 1.f;
}

QString ConvKernels::Emboss::getName() const {
    return tr("Emboss");
}
