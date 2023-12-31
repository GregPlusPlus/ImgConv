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

#ifndef FILTERSETTINGSPANEL_H
#define FILTERSETTINGSPANEL_H

#include <QDockWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QSplitter>

#include <QFileDialog>

#include <QList>
#include <QFile>

#include "Core/Utils/utils.h"
#include "UI/GUI/FilterSettingsWidget/filtersettingswidget.h"

namespace UI::GUI::Panels {
class FilterSettingsPanel : public QDockWidget {
    Q_OBJECT

public:
    explicit FilterSettingsPanel(QWidget *parent = 0);

public slots:
    void setConvKernel(Core::Processing::ConvKernels::ConvKernel *k);

private slots:
    void updateDescription(Core::Processing::ConvKernels::ConvKernel *k);
    void resetSettings();
    void exportMatrix();

private:
    QSplitter *mw_splitter;
    QWidget *mw_container;
    QWidget *mw_containerSettings;
    QPushButton *mw_resetButton;
    QPushButton *mw_exportButton;
    QTextEdit *mw_descriptionField;
    QVBoxLayout *m_layout;
    QVBoxLayout *m_settingsLayout = nullptr;

private:
    Core::Processing::ConvKernels::ConvKernel *m_k;
    QList<FilterSettingsWidget*> m_FilterSettingsWidgets;
};
}

#endif // FILTERSETTINGSPANEL_H
