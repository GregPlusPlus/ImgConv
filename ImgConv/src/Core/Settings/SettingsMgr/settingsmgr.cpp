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

#include "settingsmgr.h"

using namespace Core::Settings;

SettingsMgr::SettingsMgr(QObject *parent)
    : AbstractSettingsMgr{QApplication::applicationDirPath() + "/settings.ini", parent} {

}

void SettingsMgr::init() {
    registerSetting(new Setting("UI/lang", "default", true));
    registerSetting(new Setting("Core/device", "default", true));
    registerSetting(new Setting("GUI/windowGeometry", QRect()));
    registerSetting(new Setting("Processing/boundaryMode", (int)Processing::Options::Fixed_Color));
    registerSetting(new Setting("Processing/boundaryFixedColor", QColor(Qt::black)));
    registerSetting(new Setting("Processing/userIncludePath", QString(), true));

    connect(getSetting("UI/lang"), &Settings::Setting::valueChanged, this, [this](const QString &key, const QVariant &value) {
        Q_UNUSED(key)
        Q_UNUSED(value)
        emit langChanged();
    });
}

QString SettingsMgr::getLang() const {
    return getSetting("UI/lang")->value().toString();
}

void SettingsMgr::setLang(const QString &lang) {
    getSetting("UI/lang")->setValue(lang);
}

QString SettingsMgr::getDevice() const {
    return getSetting("Core/device")->value().toString();
}

void SettingsMgr::setDevice(const QString &name) {
    getSetting("Core/device")->setValue(name);
}

QRect SettingsMgr::getWindowGeometry() const {
    return getSetting("GUI/windowGeometry")->value().toRect();
}

void SettingsMgr::setWindowGeometry(const QRect &rect) {
    getSetting("GUI/windowGeometry")->setValue(rect);
}

Core::Processing::Options::BoundaryMode SettingsMgr::getBoundaryMode() const {
    return static_cast<Processing::Options::BoundaryMode>(getSetting("Processing/boundaryMode")->value().toInt());
}

void SettingsMgr::setBoundaryMode(Processing::Options::BoundaryMode mode) {
    getSetting("Processing/boundaryMode")->setValue((int)mode);
}

QColor SettingsMgr::getBoundaryFixedColor() const {
    return getSetting("Processing/boundaryFixedColor")->value().value<QColor>();
}

void SettingsMgr::setBoundaryFixedColor(const QColor &color) {
    getSetting("Processing/boundaryFixedColor")->setValue(color);
}

QString SettingsMgr::getUserIncludePath() const {
    return getSetting("Processing/userIncludePath")->value().toString();
}

void SettingsMgr::setUserIncludePath(const QString &path) {
    return getSetting("Processing/userIncludePath")->setValue(path);
}
