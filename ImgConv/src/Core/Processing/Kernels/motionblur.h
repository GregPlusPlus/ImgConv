#ifndef MOTIONBLUR_H
#define MOTIONBLUR_H

#include <QImage>
#include <QPainter>

#include "Core/Processing/convkernel.h"
#include "Core/Utils/utils.h"

namespace ConvKernels {
class MotionBlur : public ConvKernel
{
    Q_OBJECT
public:
    explicit MotionBlur(QObject *parent = nullptr);

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
    ConvKenrelSetting *m_angleSetting;
};
}

#endif // MOTIONBLUR_H
