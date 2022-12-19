#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "Core/Processing/convkernel.h"

namespace ConvKernels {
class GaussianBlur : public ConvKernels::ConvKernel {
    Q_OBJECT
public:
    explicit GaussianBlur(QObject *parent = nullptr);

    QVector<QVector<float>> getMat() const;
    float getScalar() const;
    QString getName() const;

private slots:
    void settingChanged();

private:
    QVector<QVector<float>> m_k;
    float m_s;

private:
    ConvKenrelSetting *m_sizeSetting;
    ConvKenrelSetting *m_stddevSetting;
};
}

#endif // GAUSSIANBLUR_H
