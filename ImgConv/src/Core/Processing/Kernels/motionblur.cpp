#include "motionblur.h"

ConvKernels::MotionBlur::MotionBlur(QObject *parent)
    : ConvKernel{parent} {
    m_sizeSetting = new ConvKenrelSetting(tr("Size"),
                        true, 1,
                        true, 128,
                        10,
                        this);

    m_angleSetting = new ConvKenrelSetting(tr("Angle"),
                         true, 0,
                         true, 360,
                         0,
                         this);

    connect(m_sizeSetting, &ConvKenrelSetting::valueChanged, this, &MotionBlur::settingChanged);
    connect(m_angleSetting, &ConvKenrelSetting::valueChanged, this, &MotionBlur::settingChanged);

    addSetting(m_sizeSetting);
    addSetting(m_angleSetting);

    settingChanged();
}

QVector<QVector<float> > ConvKernels::MotionBlur::getMat() const {
    return m_k;
}

float ConvKernels::MotionBlur::getScalar() const {
    return m_s;
}

QString ConvKernels::MotionBlur::getName() const {
    return tr("Motion blur");
}

void ConvKernels::MotionBlur::settingChanged() {
    size_t kSize = m_sizeSetting->val() * 2;

    if((kSize % 2) == 0) {
        kSize += 1;
    }

    QVector<QVector<float>> k;

    QImage kImg(kSize, kSize, QImage::Format_ARGB32);
    kImg.fill(Qt::black);
    QPainter p(&kImg);
    p.translate(kSize / 2, kSize / 2);

    p.setPen(Qt::white);
    p.rotate(m_angleSetting->val());
    p.drawLine(-kSize / 2, 0, kSize / 2, 0);

    Utils::imageToMatrix(k, kImg);

    m_k = k;
    m_s = 1.f/Utils::matrixSumCoef(k);
}
