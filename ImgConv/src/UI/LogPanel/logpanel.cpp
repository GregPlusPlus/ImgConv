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

#include "logpanel.h"

LogPanel::LogPanel(QWidget *parent)
    : QDockWidget(tr("Logs"), parent) {

    mw_tabs = new QTabWidget(this);

    mw_info = new LogWidget(this);

    mw_output = new LogWidget(this);

    mw_errors = new LogWidget(this);

    mw_clear = new QPushButton(QIcon(":/icons/broom.png"), QString(), this);
    connect(mw_clear, &QPushButton::clicked, this, &LogPanel::clear);

    mw_tabs->addTab(mw_info, QIcon(":/icons/information.png"), tr("Info"));
    mw_tabs->addTab(mw_output, QIcon(":/icons/script-text.png"), tr("Output"));
    mw_tabs->addTab(mw_errors, QIcon(":/icons/cross-circle.png"), tr("Errors"));
    mw_tabs->setCornerWidget(mw_clear);

    setWidget(mw_tabs);
}

void LogPanel::logInfo(const QString &str) {
    mw_info->append(str);
    mw_info->ensureCursorVisible();

    mw_tabs->setCurrentWidget(mw_info);
}

void LogPanel::logOutput(const QString &str) {
    mw_output->append(str);
    mw_output->ensureCursorVisible();

    mw_tabs->setCurrentWidget(mw_output);
}

void LogPanel::logError(const QString &str) {
    mw_errors->append(str);
    mw_errors->ensureCursorVisible();

    mw_tabs->setCurrentWidget(mw_errors);
}

void LogPanel::clear() {
    QTextEdit *textEdit = dynamic_cast<QTextEdit*>(mw_tabs->currentWidget());

    if(textEdit == nullptr) {
        return;
    }

    textEdit->clear();
}
