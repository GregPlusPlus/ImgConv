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

#ifndef LOGPANEL_H
#define LOGPANEL_H

#include <QDockWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVector>

#include "logwidget.h"
#include "Core/Logger/logger.h"

namespace UI::GUI::Panels {
class LogPanel : public QDockWidget {
    Q_OBJECT

public:
    LogPanel(QWidget *parent = 0);

public slots:
    void logInfo(const QString &str);
    void logOutput(const QString &str);
    void logError(const QString &str);
    void addLogger(Core::Logger *logger);

private slots:
    void clear();

private:
    QTabWidget *mw_tabs;
    LogWidget *mw_info;
    LogWidget *mw_output;
    LogWidget *mw_errors;
    QPushButton *mw_clear;
};
}

#endif // LOGPANEL_H
