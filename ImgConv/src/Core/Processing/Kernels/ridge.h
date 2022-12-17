#ifndef RIDGE_H
#define RIDGE_H

#include "Core/Processing/convkernel.h"

namespace ConvKernels {
class Ridge : public ConvKernel {
    Q_OBJECT
public:
    explicit Ridge(QObject *parent = nullptr);

    QVector<QVector<float>> getMat() const;
    float getScalar() const;
    QString getName() const;
};
}

#endif // RIDGE_H
