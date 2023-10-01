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

#ifndef UTILSGUI_H
#define UTILSGUI_H

#include <QFrame>
#include <QAction>
#include <QToolTip>
#include <QMessageBox>

#include <QApplication>
#include <QFile>

#include "Core/OCLWrapper/oclutils.h"

#include "app_strings.h"

namespace UI::GUI::Utils {
    QString strippedActionText(QString s);
    void addShortcutToToolTip(QAction *action);
    void showAboutDialog(QWidget *parent);
    void showOpenCLDevicesDialog(QWidget *parent);
    QFrame *createSeparator(QWidget *parent, QFrame::Shape shape = QFrame::HLine);
}

#endif // UTILSGUI_H
