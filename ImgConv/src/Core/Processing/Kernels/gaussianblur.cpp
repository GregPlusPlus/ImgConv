#include "gaussianblur.h"

#include <cmath>

ConvKernels::GaussianBlur::GaussianBlur(QObject *parent)
    : ConvKernels::ConvKernel{parent}{
    m_sizeSetting = new ConvKenrelSetting(tr("Size"),
                        ConvKenrelSetting::SettingType_Int,
                        true, (uint32_t)1,
                        false, (uint32_t)0,
                        1,
                        this);

    m_stddevSetting = new ConvKenrelSetting(tr("Std Dev"),
                          ConvKenrelSetting::SettingType_Float,
                          true, (float)1,
                          false, (float)0,
                          (float)10,
                          this);

    connect(m_sizeSetting, &ConvKenrelSetting::valueChanged, this, &GaussianBlur::settingChanged);
    connect(m_stddevSetting, &ConvKenrelSetting::valueChanged, this, &GaussianBlur::settingChanged);

    m_settings.append(m_sizeSetting);
    m_settings.append(m_stddevSetting);

    settingChanged();
}

QVector<QVector<float> > ConvKernels::GaussianBlur::getMat() const {
    return m_k;
}

float ConvKernels::GaussianBlur::getScalar() const {
    return m_s;
}

QString ConvKernels::GaussianBlur::getName() const {
    return tr("Gaussian blur");
}

void ConvKernels::GaussianBlur::settingChanged() {
    size_t kSize = m_sizeSetting->val() * 3;

    if((kSize % 2) == 0) {
        kSize += 1;
    }

    float s = 0;
    QVector<QVector<float>> k;
    k.resize(kSize);

    for(uint32_t y = 0; y < kSize; y ++) {
        k[y].resize(kSize);
        for(uint32_t x = 0; x < kSize; x ++) {
            k[y][x] = 1.f/(2*M_PI*(float)pow(m_stddevSetting->valF(), 2))
                    *exp(-(float)(x*x+y*y)/(float)(2.f*pow(m_stddevSetting->valF(),2)));
            s += k[y][x];
        }
    }

    m_k = k;
    m_s = 1.f/s;
}
