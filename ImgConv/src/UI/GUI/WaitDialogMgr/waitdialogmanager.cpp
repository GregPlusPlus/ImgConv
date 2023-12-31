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

#include "waitdialogmanager.h"

using namespace UI::GUI;

WaitDialogManager::WaitDialogManager(QObject *parent)
    : QObject{parent} {

}

WaitDialogManager::~WaitDialogManager() {
    for(Dialogs::WaitDialog *dialog : qAsConst(m_waitDialogs)) {
        delete dialog;
    }
}

Dialogs::WaitDialog *WaitDialogManager::createWaitDialog(const QUuid &uuid, const QString &msg, int flags) {
    Dialogs::WaitDialog *dialog = new Dialogs::WaitDialog(msg, flags);
    dialog->show();

    m_waitDialogs.insert(uuid, dialog);

    return dialog;
}

void WaitDialogManager::closeDialog(const QUuid &uuid) {
    Dialogs::WaitDialog *dialog = m_waitDialogs.value(uuid, nullptr);

    if(dialog) {
        m_waitDialogs.remove(uuid);

        delete dialog;
    }
}

void WaitDialogManager::updateDialogProgress(const QUuid &uuid, size_t percentage) {
    Dialogs::WaitDialog *dialog = m_waitDialogs.value(uuid, nullptr);

    if(dialog) {
        dialog->updateProgress(percentage);
    }
}

void WaitDialogManager::hideAll() {
    for(Dialogs::WaitDialog *dialog : qAsConst(m_waitDialogs)) {
        dialog->hide();
    }
}

void WaitDialogManager::showAll() {
    for(Dialogs::WaitDialog *dialog : qAsConst(m_waitDialogs)) {
        dialog->show();
    }
}

qsizetype WaitDialogManager::getNumberOfOpenDialogs() {
    return m_waitDialogs.size();
}

void WaitDialogManager::moveAll(const QPoint &offset, const QRect &mainWindowRect) {
    for(Dialogs::WaitDialog *dialog : qAsConst(m_waitDialogs)) {
        if(mainWindowRect.contains(dialog->geometry())) {
            dialog->move(dialog->pos() + offset);
        }
    }
}
