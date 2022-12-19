#include "sharpen.h"

ConvKernels::Sharpen::Sharpen(QObject *parent)
    : ConvKernel{parent} {
    m_strengthSetting = new ConvKenrelSetting(tr("Contour strength"),
                        true, 1,
                        true, 128,
                        1,
                        this);

    m_smoothSetting = new ConvKenrelSetting(tr("Smoothing"),
                                            true, -.99f,
                                            true, 100.f,
                                            1.f,
                                            this);

    connect(m_strengthSetting, &ConvKenrelSetting::valueChanged, this, &Sharpen::settingChanged);
    connect(m_smoothSetting, &ConvKenrelSetting::valueChanged, this, &Sharpen::settingChanged);

    m_settings.append(m_strengthSetting);
    m_settings.append(m_smoothSetting);

    settingChanged();
}

QVector<QVector<float> > ConvKernels::Sharpen::getMat() const {
    return m_k;
}

float ConvKernels::Sharpen::getScalar() const {
    return m_s;
}

QString ConvKernels::Sharpen::getName() const {
    return tr("Sharpen");
}

void ConvKernels::Sharpen::settingChanged() {
    size_t kSize = m_strengthSetting->val() * 2;

    if((kSize % 2) == 0) {
        kSize += 1;
    }

    QVector<QVector<float>> k;
    k.resize(kSize);

    for(uint32_t y = 0; y < kSize; y ++) {
        k[y].resize(kSize);
        for(uint32_t x = 0; x < kSize; x ++) {
            if(y == (kSize / 2)) {
                k[y][x] = -1.f;
            } else if(x == (kSize / 2)) {
                k[y][x] = -1.f;
            }
        }
    }

    k[kSize / 2][kSize / 2] = m_strengthSetting->val() * 4 + 1 + m_smoothSetting->valF();

    m_k = k;
    m_s = 1.f/(1.f + m_smoothSetting->valF());
    //m_s = 1;
}
