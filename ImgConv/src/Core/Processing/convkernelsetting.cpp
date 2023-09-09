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

ConvKernelSetting::ConvKernelSetting(const QString &name, Data::SettingType type, QObject *parent)
    : QObject{parent} {

    m_data.name = name;
    m_data.type = type;

    setVal((int)0);
    setDefault();
}

ConvKernelSetting::ConvKernelSetting(const QString &name, bool hasMin, int min, bool hasMax, int max, int val, QObject *parent)
    : QObject{parent} {

    m_data.name = name;
    m_data.hasMin = hasMin;
    m_data.hasMax = hasMax;
    m_data.type = Data::SettingType_Int;

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
    : QObject{parent} {

    m_data.name = name;
    m_data.hasMin = hasMin;
    m_data.hasMax = hasMax;
    m_data.type = Data::SettingType_Float;

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
: QObject{parent} {

    m_data.name = name;
    m_data.type = Data::SettingsType_Bool;

    setVal(val);
    setDefault();
}

ConvKernelSetting::ConvKernelSetting(const QString &name, QString val, QObject *parent)
    : QObject{parent} {

    m_data.name = name;
    m_data.type = Data::SettingsType_String;

    setVal(val);
    setDefault();
}

ConvKernelSetting::ConvKernelSetting(const QString &name, QString title, QString filter, QString fileName, QObject *parent)
    : QObject{parent} {

    m_data.name = name;
    m_data.type = Data::SettingsType_FileName;

    setVal(fileName);
    setDefault();

    setFileNameTitle(title);
    setFileNameFilter(filter);
}

QString ConvKernelSetting::name() const {
    return m_data.name;
}

void ConvKernelSetting::setName(const QString &name) {
    m_data.name = name;
}

ConvKernelSetting::Data ConvKernelSetting::data() const {
    return m_data;
}

void ConvKernelSetting::setData(const Data &data) {
    m_data = data;

    emit valueChanged(this);
}

bool ConvKernelSetting::hasMax() const {
    return m_data.hasMax;
}

void ConvKernelSetting::setHasMax(bool hasMax) {
    m_data.hasMax = hasMax;
}

ConvKernelSetting::Data::SettingType ConvKernelSetting::type() const {
    return m_data.type;
}

void ConvKernelSetting::setType(Data::SettingType type) {
    m_data.type = type;
}

QVariant ConvKernelSetting::val() const {
    return m_data.val;
}

int ConvKernelSetting::valInt() const {
    return m_data.val.toInt();
}

float ConvKernelSetting::valF() const {
    return m_data.val.toFloat();
}

bool ConvKernelSetting::valB() const {
    return m_data.val.toBool();
}

QString ConvKernelSetting::valS() const {
    return m_data.val.toString();
}

void ConvKernelSetting::setVal(int val) {
    m_data.val = QVariant(val);

    emit valueChanged(this);
}

void ConvKernelSetting::setVal(float val) {
    m_data.val = QVariant(val);

    emit valueChanged(this);
}

void ConvKernelSetting::setVal(bool val) {
    m_data.val = QVariant(val);

    emit valueChanged(this);
}

void ConvKernelSetting::setVal(QString val) {
    m_data.val = QVariant(val);

    emit valueChanged(this);
}

int ConvKernelSetting::max() const{
    return m_data.max.toInt();
}

int ConvKernelSetting::min() const {
    return m_data.min.toInt();
}

float ConvKernelSetting::minF() const {
    return m_data.min.toFloat();
}

float ConvKernelSetting::maxF() const {
    return m_data.max.toFloat();
}

void ConvKernelSetting::setMax(int max) {
    m_data.max = QVariant(max);
}

void ConvKernelSetting::setMax(float max) {
    m_data.max = QVariant(max);
}

void ConvKernelSetting::reset() {
    m_data.val = m_data.defaultValue;
}

void ConvKernelSetting::setDefault() {
    m_data.defaultValue = m_data.val;
}

const QVariant &ConvKernelSetting::defaultVal() const {
    return m_data.defaultValue;
}

void ConvKernelSetting::setMin(int min) {
    m_data.min = QVariant(min);
}

void ConvKernelSetting::setMin(float min) {
    m_data.min = QVariant(min);
}

bool ConvKernelSetting::hasMin() const {
    return m_data.hasMin;
}

void ConvKernelSetting::setHasMin(bool hasMin) {
    m_data.hasMin = hasMin;
}

const QString &ConvKernelSetting::fileNameTitle() const {
    return m_data.fileNameTitle;
}

void ConvKernelSetting::setFileNameTitle(const QString &newFileNameTitle) {
    m_data.fileNameTitle = newFileNameTitle;
}

const QString &ConvKernelSetting::fileNameFilter() const {
    return m_data.fileNameFilter;
}

void ConvKernelSetting::setFileNameFilter(const QString &newFileNameFilter) {
    m_data.fileNameFilter = newFileNameFilter;
}

void ConvKernelSetting::setVal(const QVariant &val) {
    m_data.val = val;
}
