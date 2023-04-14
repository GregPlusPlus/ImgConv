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

    mw_splitter = new QSplitter(this);
    mw_splitter->setOrientation(Qt::Vertical);

    m_settingsLayout = new QVBoxLayout;

    mw_container = new QWidget(this);
    mw_container->setLayout(m_settingsLayout);

    mw_resetButton = new QPushButton(tr("Reset settings"), this);
    connect(mw_resetButton, &QPushButton::clicked, this, &FilterSettingsDock::resetSettings);

    mw_descriptionField = new QTextEdit(tr("<h2>Filter description</h2>"), this);
    mw_descriptionField->setReadOnly(true);
    mw_descriptionField->setMinimumHeight(300);

    mw_splitter->addWidget(mw_container);
    mw_splitter->addWidget(mw_resetButton);
    mw_splitter->addWidget(mw_descriptionField);

    setWidget(mw_splitter);
}

void FilterSettingsDock::setConvKernel(ConvKernels::ConvKernel *k) {
    m_k = k;

    for(FilterSettingsWidget *w : m_FilterSettingsWidgets) {
        if(w) {
            m_settingsLayout->removeWidget(w);
            delete w;
        }
    }

    m_FilterSettingsWidgets.clear();

    for(ConvKernels::ConvKenrelSetting *s : k->settings()) {
        FilterSettingsWidget *w = new FilterSettingsWidget(s, mw_container);
        w->show();
        m_FilterSettingsWidgets.append(w);
        m_settingsLayout->addWidget(w);
    }

    updateDescription(k);
}

void FilterSettingsDock::updateDescription(ConvKernels::ConvKernel *k) {
    mw_descriptionField->setText(tr("<h2>%1</h2><hr>%2").arg(k->getName()).arg(k->getDescription()));
}

void FilterSettingsDock::resetSettings() {
    if(m_k) {
        m_k->reset();

        setConvKernel(m_k);
    }
}
