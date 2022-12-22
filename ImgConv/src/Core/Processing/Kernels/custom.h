#ifndef CUSTOM_H
#define CUSTOM_H

#include <QFileDialog>
#include <QImage>

#include "Core/Processing/convkernel.h"
#include "Core/Utils/utils.h"

namespace ConvKernels {
class Custom : public ConvKernel {
    Q_OBJECT
public:
    explicit Custom(QObject *parent = nullptr);

    QVector<QVector<float>> getMat() const;
    float getScalar() const;
    QString getName() const;

public slots:
    void select();

private:
    QVector<QVector<float>> m_k;
    float m_s;
};
}

#endif // CUSTOM_H
