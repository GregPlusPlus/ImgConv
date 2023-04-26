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

    mw_info = new QTextEdit(this);
    mw_info->setReadOnly(true);

    mw_output = new QTextEdit(this);
    mw_output->setReadOnly(true);

    mw_errors = new QTextEdit(this);
    mw_errors->setReadOnly(true);

    mw_tabs->addTab(mw_info, QIcon(":/icons/information.png"), tr("Info"));
    mw_tabs->addTab(mw_output, QIcon(":/icons/script-text.png"), tr("Output"));
    mw_tabs->addTab(mw_errors, QIcon(":/icons/cross-circle.png"), tr("Errors"));

    setWidget(mw_tabs);
}
