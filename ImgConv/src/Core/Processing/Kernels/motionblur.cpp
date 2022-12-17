#include "motionblur.h"

ConvKernels::MotionBlur::MotionBlur(QObject *parent)
    : ConvKernel{parent} {

}

QVector<QVector<float> > ConvKernels::MotionBlur::getMat() const {
    static QVector<QVector<float>> k = {
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
    };

    return k;
}

float ConvKernels::MotionBlur::getScalar() const {
    return 1.f/5.f;
}

QString ConvKernels::MotionBlur::getName() const {
    return tr("Motion blur");
}
