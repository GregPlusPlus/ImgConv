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

#ifndef SETTING_H
#define SETTING_H

#include <QObject>
#include <QVariant>

namespace Core::Settings {
class Setting : public QObject {
    Q_OBJECT

public:
    explicit Setting(const QString &key, const QVariant &defaultValue, bool liveUpdate = false);
    virtual ~Setting();

    const QString &key() const;

    const QVariant &value() const;

    void setValue(const QVariant &value);

    bool liveUpdate() const;
    void setLiveUpdate(bool liveUpdate);

signals:
    void valueChanged(const QString &key, const QVariant &value);
    void saveValue(const QString &key, const QVariant &value);

private:
    QString m_key;
    QVariant m_value;

    bool m_liveUpdate = false;

};
}

#endif // SETTING_H
