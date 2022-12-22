/**
 ** This file is part of the ImgConv project.
 ** Copyright 2022-2023 Grégoire BOST <bostgregoire@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

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
