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

#ifndef FILTERSETTINGSWIDGET_H
#define FILTERSETTINGSWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFormLayout>

#include "Core/Processing/convkernel.h"

class FilterSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterSettingsWidget(ConvKernels::ConvKenrelSetting *setting, QWidget *parent = nullptr);

    ConvKernels::ConvKenrelSetting *setting() const;

signals:

private:
    QFormLayout *m_layout;

    ConvKernels::ConvKenrelSetting  *m_setting;

};

#endif // FILTERSETTINGSWIDGET_H
