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
    setVal((uint32_t)0);
}

ConvKenrelSetting::ConvKenrelSetting(const QString &name, SettingType type, bool hasMin, uint32_t min, bool hasMax, uint32_t max, uint32_t val, QObject *parent)
    : QObject{parent}, m_name{name}, m_hasMin{hasMin}, m_hasMax{hasMax}, m_type{type} {
    if(hasMin) {
        setMin(min);
    } else {
        setVal((uint32_t)0);
    }

    if(hasMax) {
        setMax(max);
    }

    setVal(val);
}

ConvKenrelSetting::ConvKenrelSetting(const QString &name, SettingType type, bool hasMin, float min, bool hasMax, float max, float val, QObject *parent)
    : QObject{parent}, m_name{name}, m_hasMin{hasMin}, m_hasMax{hasMax}, m_type{type} {
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

void ConvKenrelSetting::setVal(uint32_t val) {
    m_val = val;

    emit valueChanged(this);
}

void ConvKenrelSetting::setVal(float val) {
    m_val = floatToUint32(val);

    emit valueChanged(this);
}

uint32_t ConvKenrelSetting::max() const{
    return m_max;
}

uint32_t ConvKenrelSetting::minF() const {
    return uint32ToFloat(m_min);
}

uint32_t ConvKenrelSetting::maxF() const {
    return uint32ToFloat(m_max);
}

void ConvKenrelSetting::setMax(uint32_t max) {
    m_max = max;
}

void ConvKenrelSetting::setMax(float max) {
    m_max = floatToUint32(max);
}

uint32_t ConvKenrelSetting::min() const {
    return m_min;
}

void ConvKenrelSetting::setMin(uint32_t min) {
    m_min = min;
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

