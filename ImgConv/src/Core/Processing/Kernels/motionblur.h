#ifndef MOTIONBLUR_H
#define MOTIONBLUR_H

#include "Core/Processing/convkernel.h"

namespace ConvKernels {
class MotionBlur : public ConvKernel
{
    Q_OBJECT
public:
    explicit MotionBlur(QObject *parent = nullptr);

    QVector<QVector<float>> getMat() const;
    float getScalar() const;
    QString getName() const;
};
}

#endif // MOTIONBLUR_H
