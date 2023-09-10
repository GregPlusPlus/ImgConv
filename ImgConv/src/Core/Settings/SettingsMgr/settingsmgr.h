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

#ifndef SETTINGSMGR_H
#define SETTINGSMGR_H

#include "abstractsettingsmgr.h"

#include "Core/Processing/processing.h"

namespace Core::Settings {
class SettingsMgr : public AbstractSettingsMgr {
    Q_OBJECT

public:
    explicit SettingsMgr(QObject *parent = nullptr);

    void init();

public:
    QString getLang() const;
    void setLang(const QString &lang);

    QString getDevice() const;
    void setDevice(const QString &name);

    QRect getWindowGeometry() const;
    void setWindowGeometry(const QRect &rect);

    Core::Processing::Options::BoundaryMode getBoundaryMode() const;
    void setBoundaryMode(Core::Processing::Options::BoundaryMode mode);

    QColor getBoundaryFixedColor() const ;
    void setBoundaryFixedColor(const QColor &color);

    QString getUserIncludePath() const;
    void setUserIncludePath(const QString &path);

signals:
    void langChanged();
};
}

#endif // SETTINGSMGR_H
