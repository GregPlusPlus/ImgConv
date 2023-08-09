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

#include "convkernelsetting.h"

using namespace Core::Processing;

ConvKernelSetting::ConvKernelSetting(const QString &name, SettingType type, QObject *parent)
    : QObject{parent}, m_name{name}, m_type{type} {
    setVal((int)0);
    setDefault();
}

ConvKernelSetting::ConvKernelSetting(const QString &name, bool hasMin, int min, bool hasMax, int max, int val, QObject *parent)
    : QObject{parent}, m_name{name}, m_hasMin{hasMin}, m_hasMax{hasMax}, m_type{SettingType_Int} {
    if(hasMin) {
        setMin(min);
    } else {
        setVal((int)0);
    }

    if(hasMax) {
        setMax(max);
    }

    setVal(val);
    setDefault();
}

ConvKernelSetting::ConvKernelSetting(const QString &name, bool hasMin, float min, bool hasMax, float max, float val, QObject *parent)
    : QObject{parent}, m_name{name}, m_hasMin{hasMin}, m_hasMax{hasMax}, m_type{SettingType_Float} {
    if(hasMin) {
        setMin(min);
    } else {
        setVal((float)0);
    }

    if(hasMax) {
        setMax(max);
    }

    setVal(val);
    setDefault();
}

ConvKernelSetting::ConvKernelSetting(const QString &name, bool val, QObject *parent)
: QObject{parent}, m_name{name}, m_type{SettingsType_Bool} {
    setVal(val);
    setDefault();
}

ConvKernelSetting::ConvKernelSetting(const QString &name, QString val, QObject *parent)
    : QObject{parent}, m_name{name}, m_type{SettingsType_String} {
    setVal(val);
    setDefault();
}

ConvKernelSetting::ConvKernelSetting(const QString &name, QString title, QString filter, QString fileName, QObject *parent)
    : QObject{parent}, m_name{name}, m_type{SettingsType_FileName} {
    setVal(fileName);
    setDefault();

    setFileNameTitle(title);
    setFileNameFilter(filter);
}

QString ConvKernelSetting::name() const {
    return m_name;
}

void ConvKernelSetting::setName(const QString &name) {
    m_name = name;
}

bool ConvKernelSetting::hasMax() const {
    return m_hasMax;
}

void ConvKernelSetting::setHasMax(bool hasMax) {
    m_hasMax = hasMax;
}

ConvKernelSetting::SettingType ConvKernelSetting::type() const {
    return m_type;
}

void ConvKernelSetting::setType(SettingType type) {
    m_type = type;
}

int ConvKernelSetting::val() const {
    return m_val.toInt();
}

float ConvKernelSetting::valF() const {
    return m_val.toFloat();
}

bool ConvKernelSetting::valB() const {
    return m_val.toBool();
}

QString ConvKernelSetting::valS() const {
    return m_val.toString();
}

void ConvKernelSetting::setVal(int val) {
    m_val = QVariant(val);

    emit valueChanged(this);
}

void ConvKernelSetting::setVal(float val) {
    m_val = QVariant(val);

    emit valueChanged(this);
}

void ConvKernelSetting::setVal(bool val) {
    m_val = QVariant(val);

    emit valueChanged(this);
}

void ConvKernelSetting::setVal(QString val) {
    m_val = QVariant(val);

    emit valueChanged(this);
}

int ConvKernelSetting::max() const{
    return m_max.toInt();
}

int ConvKernelSetting::min() const {
    return m_min.toInt();
}

float ConvKernelSetting::minF() const {
    return m_min.toFloat();
}

float ConvKernelSetting::maxF() const {
    return m_max.toFloat();
}

void ConvKernelSetting::setMax(int max) {
    m_max = QVariant(max);
}

void ConvKernelSetting::setMax(float max) {
    m_max = QVariant(max);
}

void ConvKernelSetting::reset() {
    m_val = m_default;
}

void ConvKernelSetting::setDefault() {
    m_default = m_val;
}

const QVariant &ConvKernelSetting::defaultVal() const {
    return m_default;
}

void ConvKernelSetting::setMin(int min) {
    m_min = QVariant(min);
}

void ConvKernelSetting::setMin(float min) {
    m_min = QVariant(min);
}

bool ConvKernelSetting::hasMin() const {
    return m_hasMin;
}

void ConvKernelSetting::setHasMin(bool hasMin) {
    m_hasMin = hasMin;
}

const QString &ConvKernelSetting::fileNameTitle() const {
    return m_fileNameTitle;
}

void ConvKernelSetting::setFileNameTitle(const QString &newFileNameTitle) {
    m_fileNameTitle = newFileNameTitle;
}

const QString &ConvKernelSetting::fileNameFilter() const {
    return m_fileNameFilter;
}

void ConvKernelSetting::setFileNameFilter(const QString &newFileNameFilter) {
    m_fileNameFilter = newFileNameFilter;
}

void ConvKernelSetting::setVal(const QVariant &val) {
    m_val = val;
}
