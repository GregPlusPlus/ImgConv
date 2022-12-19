#ifndef EMBOSS_H
#define EMBOSS_H

#include "kernels.h"

namespace ConvKernels {
class Emboss : public ConvKernel {
    Q_OBJECT
public:
    explicit Emboss(QObject *parent = nullptr);

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
    ConvKenrelSetting *m_smoothSetting;
};
}

#endif // EMBOSS_H
