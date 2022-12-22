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

#include "filtersettingsdock.h"

FilterSettingsDock::FilterSettingsDock(QWidget *parent)
    : QDockWidget(tr("Filter settings"), parent) {
    setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    setMinimumWidth(200);

    mw_container = new QWidget(this);

    setWidget(mw_container);
}

void FilterSettingsDock::setConvKernel(ConvKernels::ConvKernel *k) {
    for(FilterSettingsWidget *w : m_FilterSettingsWidgets) {
        if(w) {
            delete w;
        }
    }

    m_FilterSettingsWidgets.clear();

    if(m_layout) {
        delete m_layout;
    }
    m_layout = new QVBoxLayout;
    mw_container->setLayout(m_layout);

    for(ConvKernels::ConvKenrelSetting *s : k->settings()) {
        FilterSettingsWidget *w = new FilterSettingsWidget(s, mw_container);
        w->show();
        m_FilterSettingsWidgets.append(w);
        m_layout->addWidget(w);
    }

    m_layout->addStretch();
}
