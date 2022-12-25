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

#include "convkernel.h"

using namespace ConvKernels;

ConvKernel::ConvKernel(QObject *parent)
    : QObject{parent} {

}

QSize ConvKernel::getMatSize() const {
    QSize s(0, 0);

    s.setHeight(getMat().size());

    if(s.height()) {
        s.setWidth(getMat()[0].size());
    }

    return s;
}

const QList<ConvKenrelSetting *> &ConvKernel::settings() const {
    return m_settings;
}

void ConvKernel::addSetting(ConvKenrelSetting *s) {
    m_settings.append(s);
}

ConvKenrelSetting::ConvKenrelSetting(const QString &name, SettingType type, QObject *parent)
    : QObject{parent}, m_name{name}, m_type{type} {
    setVal((int)0);
}

ConvKenrelSetting::ConvKenrelSetting(const QString &name, bool hasMin, int min, bool hasMax, int max, int val, QObject *parent)
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
}

ConvKenrelSetting::ConvKenrelSetting(const QString &name, bool hasMin, float min, bool hasMax, float max, float val, QObject *parent)
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
}


QString ConvKenrelSetting::name() const {
    return m_name;
}

void ConvKenrelSetting::setName(const QString &name) {
    m_name = name;
}

bool ConvKenrelSetting::hasMax() const {
    return m_hasMax;
}

void ConvKenrelSetting::setHasMax(bool hasMax) {
    m_hasMax = hasMax;
}

ConvKenrelSetting::SettingType ConvKenrelSetting::type() const {
    return m_type;
}

void ConvKenrelSetting::setType(SettingType type) {
    m_type = type;
}

int ConvKenrelSetting::val() const {
    return m_val.toInt();
}

float ConvKenrelSetting::valF() const {
    return m_val.toFloat();
}

void ConvKenrelSetting::setVal(int val) {
    m_val = QVariant(val);

    emit valueChanged(this);
}

void ConvKenrelSetting::setVal(float val) {
    m_val = QVariant(val);

    emit valueChanged(this);
}

int ConvKenrelSetting::max() const{
    return m_max.toInt();
}

int ConvKenrelSetting::min() const {
    return m_min.toInt();
}

float ConvKenrelSetting::minF() const {
    return m_min.toFloat();
}

float ConvKenrelSetting::maxF() const {
    return m_max.toFloat();
}

void ConvKenrelSetting::setMax(int max) {
    m_max = QVariant(max);
}

void ConvKenrelSetting::setMax(float max) {
    m_max = QVariant(max);
}

void ConvKenrelSetting::setMin(int min) {
    m_min = QVariant(min);
}

void ConvKenrelSetting::setMin(float min) {
    m_min = QVariant(min);
}

bool ConvKenrelSetting::hasMin() const {
    return m_hasMin;
}

void ConvKenrelSetting::setHasMin(bool hasMin) {
    m_hasMin = hasMin;
}

