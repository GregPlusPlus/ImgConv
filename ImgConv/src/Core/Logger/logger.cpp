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

#include "logger.h"

using namespace Core;

Logger::Logger(QObject *parent)
    : QObject{parent} {

}

void Logger::logInfo(const QString &str) {
    emit outputLogInfo(str);
}

void Logger::logOutput(const QString &str) {
    emit outputLogOutput(str);
}

void Logger::logError(const QString &str) {
    emit outputLogError(str);
}

void Logger::criticalError(const QString &str) {
    emit showCriticalError(str);
}
