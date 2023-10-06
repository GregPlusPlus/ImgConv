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

#ifndef CONVKERNELSETTING_H
#define CONVKERNELSETTING_H

#include <QObject>
#include <QVariant>

namespace Core::Processing {
class ConvKernelSetting : public QObject {
    Q_OBJECT

public:
    class Data {
    public:
        enum ValueType {
            SettingType_Float,
            SettingType_Int,
            SettingType_Bool,
            SettingType_String,
            SettingType_FileName
        };

    public:
        QString key;
        QString name;
        bool hasMin = false;
        bool hasMax = false;
        ValueType type;
        QVariant val;
        QVariant min;
        QVariant max;
        QVariant defaultValue;

        QString fileNameTitle;
        QString fileNameFilter;
    };

public:
    explicit ConvKernelSetting(const QString &key, Data::ValueType type, QObject *parent = nullptr);
    explicit ConvKernelSetting(const QString &key, bool hasMin, int min, bool hasMax, int max, int val = 0, QObject *parent = nullptr);
    explicit ConvKernelSetting(const QString &key, bool hasMin, float min, bool hasMax, float max, float val = 0, QObject *parent = nullptr);
    explicit ConvKernelSetting(const QString &key, bool val, QObject *parent = nullptr);
    explicit ConvKernelSetting(const QString &key, QString val, QObject *parent = nullptr);
    explicit ConvKernelSetting(const QString &key, QString title, QString filter, QString fileName, QObject *parent = nullptr);

    QString key() const;
    void setKey(const QString &key);

    QString name() const;
    void setName(const QString &name);

    bool hasMin() const;
    void setHasMin(bool hasMin);
    bool hasMax() const;
    void setHasMax(bool hasMax);
    Data::ValueType type() const;
    void setType(Data::ValueType type);
    QVariant val() const;
    int valInt() const;
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

    Data data() const;
    void setData(const Data &data);

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
    void valueChanged(const Core::Processing::ConvKernelSetting *s);

private:
    void setDefault();

private:
    Data m_data;
};
}

#endif // CONVKERNELSETTING_H
