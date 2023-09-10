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

using namespace UI::GUI;

FilterSettingsWidget::FilterSettingsWidget(Core::Processing::ConvKernelSetting *setting, QWidget *parent)
    : QWidget{parent}, m_setting{setting} {

    m_layout = new QFormLayout;

    if(setting->type() == Core::Processing::ConvKernelSetting::Data::SettingType_Int) {
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

        s->setValue(setting->valInt());

        connect(s, &QSpinBox::valueChanged, setting,
                QOverload<int>::of(&Core::Processing::ConvKernelSetting::setVal));

        m_w = s;
    } else if(setting->type() == Core::Processing::ConvKernelSetting::Data::SettingType_Float) {
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
                QOverload<float>::of(&Core::Processing::ConvKernelSetting::setVal));

        m_w = s;
    } else if(setting->type() == Core::Processing::ConvKernelSetting::Data::SettingsType_Bool) {
        QCheckBox *c = new QCheckBox(this);
        c->setChecked(setting->valB());

        connect(c, &QCheckBox::stateChanged, setting,
                QOverload<bool>::of(&Core::Processing::ConvKernelSetting::setVal));

        m_w = c;
    } else if(setting->type() == Core::Processing::ConvKernelSetting::Data::SettingsType_String) {
        QLineEdit *l = new QLineEdit(setting->valS(), this);

        connect(l, &QLineEdit::textChanged, setting,
                QOverload<QString>::of(&Core::Processing::ConvKernelSetting::setVal));

        m_w = l;
    } else if(setting->type() == Core::Processing::ConvKernelSetting::Data::SettingsType_FileName) {
        Components::FilenamePicker *fnp = new Components::FilenamePicker(setting->fileNameTitle(), setting->fileNameFilter(),
                                                                         Components::FilenamePicker::Files, this);
        fnp->setFileName(setting->valS());

        connect(fnp, &Components::FilenamePicker::fileNameChanged, setting,
                QOverload<QString>::of(&Core::Processing::ConvKernelSetting::setVal));

        m_w = fnp;
    }

    if(m_w) {
        m_layout->addRow(setting->name(), m_w);
    }

    setLayout(m_layout);

    connect(setting, &Core::Processing::ConvKernelSetting::valueChanged, this, &FilterSettingsWidget::settingChanged);
}

Core::Processing::ConvKernelSetting* FilterSettingsWidget::setting() const {
    return m_setting;
}

void FilterSettingsWidget::settingChanged(const Core::Processing::ConvKernelSetting *setting) {
    if(setting->type() == Core::Processing::ConvKernelSetting::Data::SettingType_Int) {
        QSpinBox *s = static_cast<QSpinBox *>(m_w);
        s->disconnect();
        s->setValue(setting->valInt());
        connect(s, &QSpinBox::valueChanged, setting,
                QOverload<int>::of(&Core::Processing::ConvKernelSetting::setVal));

    } else if(setting->type() == Core::Processing::ConvKernelSetting::Data::SettingType_Float) {
        QDoubleSpinBox *s = static_cast<QDoubleSpinBox *>(m_w);
        s->disconnect();
        s->setValue(setting->valF());
        connect(s, &QDoubleSpinBox::valueChanged, setting,
                QOverload<float>::of(&Core::Processing::ConvKernelSetting::setVal));

    } else if(setting->type() == Core::Processing::ConvKernelSetting::Data::SettingsType_Bool) {
        QCheckBox *c = static_cast<QCheckBox *>(m_w);
        c->disconnect();
        c->setChecked(setting->valB());
        connect(c, &QCheckBox::stateChanged, setting,
                QOverload<bool>::of(&Core::Processing::ConvKernelSetting::setVal));

    } else if(setting->type() == Core::Processing::ConvKernelSetting::Data::SettingsType_String) {
        QLineEdit *l = static_cast<QLineEdit *>(m_w);
        l->disconnect();
        l->setText(setting->valS());
        connect(l, &QLineEdit::textChanged, setting,
                QOverload<QString>::of(&Core::Processing::ConvKernelSetting::setVal));

    } else if(setting->type() == Core::Processing::ConvKernelSetting::Data::SettingsType_FileName) {
        Components::FilenamePicker *fnp = static_cast<Components::FilenamePicker *>(m_w);
        fnp->disconnect();
        fnp->setFileName(setting->valS());
        connect(fnp, &Components::FilenamePicker::fileNameChanged, setting,
                QOverload<QString>::of(&Core::Processing::ConvKernelSetting::setVal));

    }
}
