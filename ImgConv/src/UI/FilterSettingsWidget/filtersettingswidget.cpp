#include "filtersettingswidget.h"

FilterSettingsWidget::FilterSettingsWidget(ConvKernels::ConvKenrelSetting *setting, QWidget *parent)
    : QWidget{parent}, m_setting{setting} {
    m_layout = new QFormLayout;

    QAbstractSpinBox *spin = nullptr;

    if(setting->type() == ConvKernels::ConvKenrelSetting::SettingType_Int) {
        QSpinBox *s = new QSpinBox(this);

        if(setting->hasMax()) {
            s->setMaximum(setting->max());
        } else {
            s->setMaximum(INT32_MAX);
        }

        if(setting->hasMin()) {
            s->setMinimum(setting->min());
        } else {
            s->setMinimum(INT32_MIN);
        }

        s->setValue(setting->val());

        connect(s, &QSpinBox::valueChanged, setting,
                QOverload<int>::of(&ConvKernels::ConvKenrelSetting::setVal));

        spin = s;
    } else if(setting->type() == ConvKernels::ConvKenrelSetting::SettingType_Float) {
        QDoubleSpinBox *s = new QDoubleSpinBox(this);

        s->setSingleStep(0.1f);

        if(setting->hasMax()) {
            s->setMaximum(setting->maxF());
        } else {
            s->setMaximum(9999999999.f);
        }
        if(setting->hasMin()) {
            s->setMinimum(setting->minF());
        } else {
            s->setMinimum(-9999999999.f);
        }

        s->setValue(setting->valF());

        connect(s, &QDoubleSpinBox::valueChanged, setting,
                QOverload<float>::of(&ConvKernels::ConvKenrelSetting::setVal));

        spin = s;
    }

    if(spin) {
        m_layout->addRow(setting->name(), spin);
    }

    setLayout(m_layout);
}

ConvKernels::ConvKenrelSetting* FilterSettingsWidget::setting() const {
    return m_setting;
}
