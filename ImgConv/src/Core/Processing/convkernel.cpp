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
    ConvKenrelSetting *sourcePath = new ConvKenrelSetting(tr("Source file"), tr("Open source file"),
                                                          tr("OpenCL source (*.cl *.c);;All files (*.*)"),
                                                          QString(":/ocl/conv2D.cl"), this);
    addSetting(sourcePath);
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

ConvKenrelSetting *ConvKernel::getSettingByName(const QString &name) const {
    for(ConvKenrelSetting *s : settings()) {
        if(s->name() == name) {
            return s;
        }
    }

    return nullptr;
}

void ConvKernel::addSetting(ConvKenrelSetting *s) {
    m_settings.append(s);
}

QString ConvKernel::getSourceFilePath() const {
    return getSettingByName(tr("Source file"))->valS();
}

void ConvKernel::setSourceFilePath(const QString &path) {
    getSettingByName(tr("Source file"))->setVal(path);
}

void ConvKernel::reset() {
    for(ConvKenrelSetting *s : m_settings) {
        s->reset();
    }
}

ConvKenrelSetting::ConvKenrelSetting(const QString &name, SettingType type, QObject *parent)
    : QObject{parent}, m_name{name}, m_type{type} {
    setVal((int)0);
    setDefault();
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
    setDefault();
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
    setDefault();
}

ConvKenrelSetting::ConvKenrelSetting(const QString &name, bool val, QObject *parent)
: QObject{parent}, m_name{name}, m_type{SettingsType_Bool} {
    setVal(val);
    setDefault();
}

ConvKenrelSetting::ConvKenrelSetting(const QString &name, QString val, QObject *parent)
    : QObject{parent}, m_name{name}, m_type{SettingsType_String} {
    setVal(val);
    setDefault();
}

ConvKenrelSetting::ConvKenrelSetting(const QString &name, QString title, QString filter, QString fileName, QObject *parent)
    : QObject{parent}, m_name{name}, m_type{SettingsType_FileName} {
    setVal(fileName);
    setDefault();

    setFileNameTitle(title);
    setFileNameFilter(filter);
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

bool ConvKenrelSetting::valB() const {
    return m_val.toBool();
}

QString ConvKenrelSetting::valS() const {
    return m_val.toString();
}

void ConvKenrelSetting::setVal(int val) {
    m_val = QVariant(val);

    emit valueChanged(this);
}

void ConvKenrelSetting::setVal(float val) {
    m_val = QVariant(val);

    emit valueChanged(this);
}

void ConvKenrelSetting::setVal(bool val) {
    m_val = QVariant(val);

    emit valueChanged(this);
}

void ConvKenrelSetting::setVal(QString val) {
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

void ConvKenrelSetting::reset() {
    m_val = m_default;
}

void ConvKenrelSetting::setDefault() {
    m_default = m_val;
}

const QVariant &ConvKenrelSetting::defaultVal() const {
    return m_default;
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

const QString &ConvKenrelSetting::fileNameTitle() const {
    return m_fileNameTitle;
}

void ConvKenrelSetting::setFileNameTitle(const QString &newFileNameTitle) {
    m_fileNameTitle = newFileNameTitle;
}

const QString &ConvKenrelSetting::fileNameFilter() const {
    return m_fileNameFilter;
}

void ConvKenrelSetting::setFileNameFilter(const QString &newFileNameFilter) {
    m_fileNameFilter = newFileNameFilter;
}

void ConvKenrelSetting::setVal(const QVariant &val) {
    m_val = val;
}

