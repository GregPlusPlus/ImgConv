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

#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

namespace Core {
class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

public slots:
    void logInfo(const QString &str);
    void logOutput(const QString &str);
    void logError(const QString &str);

    void criticalError(const QString &str);

signals:
    void outputLogInfo(const QString &str);
    void outputLogOutput(const QString &str);
    void outputLogError(const QString &str);

    void showCriticalError(const QString &str);
};
}

#endif // LOGGER_H
