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

#ifndef CONVKERNEL_H
#define CONVKERNEL_H

#include <QObject>
#include <QSize>
#include <QVector>
#include <QList>
#include <QVariant>

#include <QDebug>

namespace Core::Processing::ConvKernels {
class ConvKenrelSetting : public QObject
{
    Q_OBJECT

public:
    enum SettingType {
        SettingType_Float,
        SettingType_Int,
        SettingsType_Bool,
        SettingsType_String,
        SettingsType_FileName
    };

public:
    explicit ConvKenrelSetting(const QString &name, SettingType type, QObject *parent = nullptr);
    explicit ConvKenrelSetting(const QString &name, bool hasMin, int min, bool hasMax, int max, int val = 0, QObject *parent = nullptr);
    explicit ConvKenrelSetting(const QString &name, bool hasMin, float min, bool hasMax, float max, float val = 0, QObject *parent = nullptr);
    explicit ConvKenrelSetting(const QString &name, bool val, QObject *parent = nullptr);
    explicit ConvKenrelSetting(const QString &name, QString val, QObject *parent = nullptr);
    explicit ConvKenrelSetting(const QString &name, QString title, QString filter, QString fileName, QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    bool hasMin() const;
    void setHasMin(bool hasMin);
    bool hasMax() const;
    void setHasMax(bool hasMax);
    SettingType type() const;
    void setType(SettingType type);
    int val() const;
    float valF() const;
    bool valB() const;
    QString valS() const;
    int min() const;
    int max() const;
    float minF() const;
    float maxF() const;

    const QString &fileNameTitle() const;
    void setFileNameTitle(const QString &newFileNameTitle);

    const QString &fileNameFilter() const;
    void setFileNameFilter(const QString &newFileNameFilter);

    const QVariant &defaultVal() const;

public slots:
    void setVal(const QVariant &val);
    void setVal(int val);
    void setVal(float val);
    void setVal(bool val);
    void setVal(QString val);
    void setMin(int min);
    void setMin(float min);
    void setMax(int max);
    void setMax(float max);
    virtual void settingChanged() {}
    void reset();

signals:
    void valueChanged(const ConvKernels::ConvKenrelSetting *s);

private:
    void setDefault();

private:
    QString m_name;
    bool m_hasMin = false;
    bool m_hasMax = false;
    SettingType m_type;
    QVariant m_val;
    QVariant m_min;
    QVariant m_max;
    QVariant m_default;

    QString m_fileNameTitle;
    QString m_fileNameFilter;
};

class ConvKernel : public QObject
{
    Q_OBJECT

public:
    explicit ConvKernel(QObject *parent = nullptr);

    virtual QVector<QVector<float>> getMat() const = 0;
    virtual float getScalar() const = 0;
    virtual QString getName() const = 0;
    virtual QString getDescription() {return QString();}
    QSize getMatSize() const;

    const QList<ConvKenrelSetting *> &settings() const;
    ConvKenrelSetting *getSettingByName(const QString &name) const;

    void addSetting(ConvKenrelSetting *s);

    QString getSourceFilePath() const;
    void setSourceFilePath(const QString &path);

public slots:
    void reset();
    virtual void select() {}

signals:

private:
    QList<ConvKenrelSetting *> m_settings;

};
}

#endif // CONVKERNEL_H
