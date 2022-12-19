#include "emboss.h"

ConvKernels::Emboss::Emboss(QObject *parent)
    : ConvKernel{parent} {
    m_sizeSetting = new ConvKenrelSetting(tr("Size"),
                        true, 1,
                        true, 128,
                        1,
                        this);

    m_smoothSetting = new ConvKenrelSetting(tr("Smoothing"),
                                            true, 1.f,
                                            true, 100.f,
                                            1.f,
                                            this);

    connect(m_sizeSetting, &ConvKenrelSetting::valueChanged, this, &Emboss::settingChanged);
    connect(m_smoothSetting, &ConvKenrelSetting::valueChanged, this, &Emboss::settingChanged);

    m_settings.append(m_sizeSetting);
    m_settings.append(m_smoothSetting);

    settingChanged();
}

QVector<QVector<float> > ConvKernels::Emboss::getMat() const {
    return m_k;
}

float ConvKernels::Emboss::getScalar() const {
    return m_s;
}

QString ConvKernels::Emboss::getName() const {
    return tr("Emboss");
}

void ConvKernels::Emboss::settingChanged() {
    size_t kSize = m_sizeSetting->val() * 2;

    if((kSize % 2) == 0) {
        kSize += 1;
    }

    QVector<QVector<float>> k;
    k.resize(kSize);

    for(uint32_t y = 0; y < kSize; y ++) {
        k[y].resize(kSize);
        for(uint32_t x = 0; x < kSize; x ++) {
            if((x == y) && (x < (kSize / 2))) {
                k[y][x] = -2.f;
            } else if((x == y) && (x > (kSize / 2))) {
                k[y][x] = 2.f;
            } else if((y == (kSize / 2)) && (x < (kSize / 2))) {
                k[y][x] = -1.f;
            } else if((y == (kSize / 2)) && (x > (kSize / 2))) {
                k[y][x] = 1.f;
            } else if((x == (kSize / 2)) && (y < (kSize / 2))) {
                k[y][x] = -1.f;
            } else if((x == (kSize / 2)) && (y > (kSize / 2))) {
                k[y][x] = 1.f;
            }
        }
    }

    k[(kSize / 2)][(kSize / 2)] = m_smoothSetting->valF();

    m_k = k;
    m_s = 1.f/m_smoothSetting->valF();
}
