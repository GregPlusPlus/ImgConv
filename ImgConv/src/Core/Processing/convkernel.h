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

#include "convkernelsetting.h"

namespace Core::Processing::ConvKernels {
class ConvKernel : public QObject {
    Q_OBJECT

public:
    explicit ConvKernel(QObject *parent = nullptr);

    virtual QVector<QVector<float>> getMat() const = 0;
    virtual float getScalar() const = 0;
    virtual QString getName() const = 0;
    virtual void updateSettingsNames() = 0;
    virtual QString getDescription() {return QString();}
    QSize getMatSize() const;

    const QList<ConvKernelSetting *> &settings() const;
    ConvKernelSetting *getSettingByKey(const QString &key) const;

    void addSetting(ConvKernelSetting *s);

    QString getSourceFilePath() const;
    void setSourceFilePath(const QString &path);

public slots:
    void reset();
    virtual void select() {}
    virtual void refreshSettingsNames();

signals:

private:
    ConvKernelSetting *m_sourcePathSetting;

    QList<ConvKernelSetting *> m_settings;

};
}

#endif // CONVKERNEL_H
