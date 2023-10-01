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

#ifndef WAITDIALOGMANAGER_H
#define WAITDIALOGMANAGER_H

#include <QObject>
#include <QMap>
#include <QUuid>

#include "UI/GUI/Dialogs/WaitDialog/waitdialog.h"

namespace UI::GUI {
class WaitDialogManager : public QObject {
    Q_OBJECT

public:
    explicit WaitDialogManager(QObject *parent = nullptr);
    ~WaitDialogManager();

public slots:
    Dialogs::WaitDialog* createWaitDialog(const QUuid &uuid, const QString &msg, int flags = Dialogs::WaitDialog::Flags::None);
    void closeDialog(const QUuid &uuid);
    void updateDialogProgress(const QUuid &uuid, size_t percentage);
    void hideAll();
    void showAll();
    qsizetype getNumberOfOpenDialogs();
    void moveAll(const QPoint &offset, const QRect &mainWindowRect);

signals:

private:
    QMap<QUuid, Dialogs::WaitDialog*> m_waitDialogs;

};
}

#endif // WAITDIALOGMANAGER_H
