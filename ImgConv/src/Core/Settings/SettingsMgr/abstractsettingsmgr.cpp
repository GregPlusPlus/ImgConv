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

#include "abstractsettingsmgr.h"

using namespace Core::Settings;

AbstractSettingsMgr::AbstractSettingsMgr(const QString &filename, QObject *parent)
    : QObject{parent} {
    m_settings = new QSettings(filename, QSettings::IniFormat, this);
}

AbstractSettingsMgr::~AbstractSettingsMgr() {
    for(Setting *s : m_settingsStore) {
        if(s) {
            delete s;
        }
    }
}

void AbstractSettingsMgr::load() {
    for(Setting *s : m_settingsStore) {
        if(s) {
            QVariant value = m_settings->value(s->key());

            if(value.isValid()) {
                s->setValue(value);
            }
        }
    }
}

void AbstractSettingsMgr::registerSetting(Setting *setting) {
    if(setting == nullptr) {
        return;
    }

    connect(setting, &Setting::saveValue, this, &AbstractSettingsMgr::saveValue);

    m_settingsStore.append(setting);
}

Setting* AbstractSettingsMgr::getSetting(const QString &key) const {
    for(Setting *s : m_settingsStore) {
        if(s && (s->key() == key)) {
            return s;
        }
    }

    return nullptr;
}

void AbstractSettingsMgr::saveValue(const QString &key, const QVariant &value) {
    if(value.isValid()) {
        m_settings->setValue(key, value);
    }
}
