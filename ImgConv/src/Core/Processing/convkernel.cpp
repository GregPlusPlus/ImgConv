#include "convkernel.h"

using namespace ConvKernels;

ConvKernel::ConvKernel(QObject *parent)
    : QObject{parent} {

}

QSize ConvKernel::getMatSize() const {
    return QSize(getMat()[0].size(), getMat().size());
}

const QList<ConvKenrelSetting *> &ConvKernel::settings() const {
    return m_settings;
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

uint32_t ConvKenrelSetting::val() const {
    return m_val;
}

float ConvKenrelSetting::valF() const {
    return uint32ToFloat(m_val);
}

uint32_t ConvKenrelSetting::floatToUint32(float v) {
    return *(uint32_t*)((float*)&(v));
}

float ConvKenrelSetting::uint32ToFloat(uint32_t v) {
    return *(float*)((uint32_t*)&(v));
}

uint32_t ConvKenrelSetting::intToUint32(int v) {
    return *(uint32_t*)((int*)&(v));
}

float ConvKenrelSetting::uint32ToInt(uint32_t v) {
    return *(int*)((uint32_t*)&(v));
}

void ConvKenrelSetting::setVal(int val) {
    m_val = intToUint32(val);

    emit valueChanged(this);
}

void ConvKenrelSetting::setVal(float val) {
    m_val = floatToUint32(val);

    emit valueChanged(this);
}

int ConvKenrelSetting::max() const{
    return uint32ToInt(m_max);
}

int ConvKenrelSetting::min() const {
    return uint32ToInt(m_min);
}

float ConvKenrelSetting::minF() const {
    return uint32ToFloat(m_min);
}

float ConvKenrelSetting::maxF() const {
    return uint32ToFloat(m_max);
}

void ConvKenrelSetting::setMax(int max) {
    m_max = intToUint32(max);
}

void ConvKenrelSetting::setMax(float max) {
    m_max = floatToUint32(max);
}

void ConvKenrelSetting::setMin(int min) {
    m_min = intToUint32(min);
}

void ConvKenrelSetting::setMin(float min) {
    m_min = floatToUint32(min);
}

bool ConvKenrelSetting::hasMin() const {
    return m_hasMin;
}

void ConvKenrelSetting::setHasMin(bool hasMin) {
    m_hasMin = hasMin;
}

