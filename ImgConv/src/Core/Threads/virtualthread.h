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

#ifndef VIRTUALTHREAD_H
#define VIRTUALTHREAD_H

#include <QObject>
#include <QRunnable>
#include <QUuid>

#include "Core/Threads/processclass.h"

namespace Threads {
class VirtualThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    VirtualThread(Classes::ProcessClass pClass);

    QUuid getUUID();

    Classes::ProcessClass processClass() const;
    void setProcessClass(Classes::ProcessClass pClass);

private:
    QUuid m_uuid;
    Classes::ProcessClass m_processClass;
};
}

#endif // VIRTUALTHREAD_H
