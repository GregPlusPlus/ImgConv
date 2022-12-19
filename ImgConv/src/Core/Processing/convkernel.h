#ifndef CONVKERNEL_H
#define CONVKERNEL_H

#include <QObject>
#include <QSize>
#include <QVector>
#include <QList>

#include <QDebug>

namespace ConvKernels {
class ConvKenrelSetting : public QObject
{
    Q_OBJECT

public:
    enum SettingType {
        SettingType_Float,
        SettingType_Int
    };

public:
    explicit ConvKenrelSetting(const QString &name, SettingType type, QObject *parent = nullptr);
    explicit ConvKenrelSetting(const QString &name, bool hasMin, int min, bool hasMax, int max, int val = 0, QObject *parent = nullptr);
    explicit ConvKenrelSetting(const QString &name, bool hasMin, float min, bool hasMax, float max, float val = 0, QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);
    bool hasMin() const;
    void setHasMin(bool hasMin);
    bool hasMax() const;
    void setHasMax(bool hasMax);
    SettingType type() const;
    void setType(SettingType type);
    uint32_t val() const;
    float valF() const;
    int min() const;
    int max() const;
    float minF() const;
    float maxF() const;

    static uint32_t floatToUint32(float v);
    static float uint32ToFloat(uint32_t v);
    static uint32_t intToUint32(int v);
    static float uint32ToInt(uint32_t v);

public slots:
    void setVal(int val);
    void setVal(float val);
    void setMin(int min);
    void setMin(float min);
    void setMax(int max);
    void setMax(float max);
    virtual void settingChanged() {}

signals:
    void valueChanged(const ConvKernels::ConvKenrelSetting *s);

private:
    QString m_name;
    bool m_hasMin = false;
    bool m_hasMax = false;
    SettingType m_type;
    uint32_t m_val;
    uint32_t m_min;
    uint32_t m_max;
};

class ConvKernel : public QObject
{
    Q_OBJECT

public:
    explicit ConvKernel(QObject *parent = nullptr);

    virtual QVector<QVector<float>> getMat() const = 0;
    virtual float getScalar() const = 0;
    virtual QString getName() const = 0;
    QSize getMatSize() const;

    const QList<ConvKenrelSetting *> &settings() const;

    void addSetting(ConvKenrelSetting *s);

public slots:
    virtual void reset() {}
    virtual void setSettingValue(const ConvKernels::ConvKenrelSetting *s) {Q_UNUSED(s)};

signals:

private:
    QList<ConvKenrelSetting *> m_settings;

};
}

#endif // CONVKERNEL_H
