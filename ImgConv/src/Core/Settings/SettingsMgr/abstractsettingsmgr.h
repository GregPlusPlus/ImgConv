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

#ifndef ABSTRACTSETTINGSMGR_H
#define ABSTRACTSETTINGSMGR_H

#include <QObject>
#include <QVector>
#include <QSettings>
#include <QApplication>

#include "Core/Settings/Setting/setting.h"

namespace Core::Settings {
class AbstractSettingsMgr : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSettingsMgr(const QString &filename, QObject *parent = nullptr);
    virtual ~AbstractSettingsMgr();

    virtual void init() = 0;

    void load();

    void registerSetting(Setting *setting);
    Setting *getSetting(const QString &key) const;

public slots:
    void saveValue(const QString &key, const QVariant &value);

signals:

private:
    QSettings *m_settings;
    QVector<Setting*> m_settingsStore;

};
}

#endif // ABSTRACTSETTINGSMGR_H
