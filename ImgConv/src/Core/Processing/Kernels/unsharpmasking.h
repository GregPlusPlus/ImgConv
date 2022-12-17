#ifndef UNSHARPMASKING_H
#define UNSHARPMASKING_H

#include "Core/Processing/convkernel.h"

namespace ConvKernels {
class UnsharpMasking : public ConvKernel
{
    Q_OBJECT
public:
    explicit UnsharpMasking(QObject *parent = nullptr);

    QVector<QVector<float>> getMat() const;
    float getScalar() const;
    QString getName() const;
};
}

#endif // UNSHARPMASKING_H
