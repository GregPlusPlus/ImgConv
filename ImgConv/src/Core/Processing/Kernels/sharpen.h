#ifndef SHARPEN_H
#define SHARPEN_H

#include "Core/Processing/convkernel.h"

namespace ConvKernels {
class Sharpen : public ConvKernel {
    Q_OBJECT
public:
    explicit Sharpen(QObject *parent = nullptr);

    QVector<QVector<float>> getMat() const;
    float getScalar() const;
    QString getName() const;

private slots:
    void settingChanged();

private:
    QVector<QVector<float>> m_k;
    float m_s;

private:
    ConvKenrelSetting *m_strengthSetting;
    ConvKenrelSetting *m_smoothSetting;
};
}

#endif // SHARPEN_H
