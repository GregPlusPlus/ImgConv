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

#include "setting.h"

using namespace Core::Settings;

Setting::Setting(const QString &key, const QVariant &defaultValue, bool liveUpdate)
    : QObject{}, m_key{key}, m_value{defaultValue}, m_liveUpdate{liveUpdate} {

}

Setting::~Setting() {
    emit saveValue(m_key, m_value);
}

const QString &Setting::key() const {
    return m_key;
}

const QVariant &Setting::value() const {
    return m_value;
}

void Setting::setValue(const QVariant &value) {
    m_value = value;

    emit valueChanged(m_key, m_value);

    if(m_liveUpdate) {
        emit saveValue(m_key, m_value);
    }
}

bool Setting::liveUpdate() const {
    return m_liveUpdate;
}

void Setting::setLiveUpdate(bool liveUpdate) {
    m_liveUpdate = liveUpdate;
}
