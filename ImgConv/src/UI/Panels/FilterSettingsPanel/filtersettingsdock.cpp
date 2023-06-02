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

using namespace UI::Panels;

FilterSettingsDock::FilterSettingsDock(QWidget *parent)
    : QDockWidget(tr("Filter settings"), parent) {
    setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    setMinimumWidth(200);

    mw_splitter = new QSplitter(this);
    mw_splitter->setOrientation(Qt::Vertical);

    mw_container = new QWidget(this);
    m_layout = new QVBoxLayout;

    m_settingsLayout = new QVBoxLayout;

    mw_containerSettings = new QWidget(this);
    mw_containerSettings->setLayout(m_settingsLayout);

    mw_resetButton = new QPushButton(tr("Reset settings"), this);
    connect(mw_resetButton, &QPushButton::clicked, this, &FilterSettingsDock::resetSettings);

    mw_exportButton = new QPushButton(tr("Export matrix"), this);
    connect(mw_exportButton, &QPushButton::clicked, this, &FilterSettingsDock::exportMatrix);

    m_layout->addWidget(mw_containerSettings);
    m_layout->addStretch(10);
    m_layout->addWidget(mw_resetButton);
    m_layout->addWidget(mw_exportButton);
    mw_container->setLayout(m_layout);

    mw_descriptionField = new QTextEdit(tr("<h2>Filter description</h2>"), this);
    mw_descriptionField->setReadOnly(true);
    mw_descriptionField->setMinimumHeight(150);

    mw_splitter->addWidget(mw_container);
    mw_splitter->addWidget(mw_descriptionField);
    mw_splitter->setStretchFactor(0, 10);
    mw_splitter->setStretchFactor(1, 1);

    setWidget(mw_splitter);
}

void FilterSettingsDock::setConvKernel(Core::Processing::ConvKernels::ConvKernel *k) {
    m_k = k;

    for(FilterSettingsWidget *w : m_FilterSettingsWidgets) {
        if(w) {
            m_settingsLayout->removeWidget(w);
            delete w;
        }
    }

    m_FilterSettingsWidgets.clear();

    for(Core::Processing::ConvKernels::ConvKenrelSetting *s : k->settings()) {
        FilterSettingsWidget *w = new FilterSettingsWidget(s, mw_containerSettings);
        w->show();
        m_FilterSettingsWidgets.append(w);
        m_settingsLayout->addWidget(w);
    }

    updateDescription(k);
}

void FilterSettingsDock::updateDescription(Core::Processing::ConvKernels::ConvKernel *k) {
    mw_descriptionField->setText(tr("<h2>%1</h2><hr>%2").arg(k->getName()).arg(k->getDescription()));
}

void FilterSettingsDock::resetSettings() {
    if(m_k) {
        m_k->reset();

        setConvKernel(m_k);
    }
}

void FilterSettingsDock::exportMatrix() {
    QString csv = Core::Utils::matrixToCSVString(m_k->getMat());

    QString fn = QFileDialog::getSaveFileName(this, tr("Save Convolution matrix..."),
                                      QString(), tr("CSV File (*.csv);;All files (*.*)"));

    if(fn.isEmpty()) {
        return;
    }

    if(fn.isEmpty()) {
        return;
    }

    QFile f(fn);

    if(!f.open(QFile::WriteOnly)) {
        f.close();

        return;
    }

    f.write(csv.toLatin1());

    f.close();
}
