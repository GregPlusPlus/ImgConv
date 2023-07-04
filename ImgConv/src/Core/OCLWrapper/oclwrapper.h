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

#ifndef OCLWRAPPER_H
#define OCLWRAPPER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QList>
#include <QSize>

#include <QDebug>

#include <CL/cl.h>

namespace Core {
class OCLWrapper : public QObject {
    Q_OBJECT

public:
    struct Device {
        cl_platform_id platform;
        cl_device_id device;
        QString name;
    };

public:
    explicit OCLWrapper(const Device &d, QObject *parent = nullptr);
    virtual ~OCLWrapper();

    QString getDeviceName();
    QString getBuildLog();
    size_t getNumberOfBuffers() const;

    cl_int ret() const;

    static QString getDevicesInfoStr();
    static QList<Device> getDevices();

    bool isRunning() const;

public slots:
    void createProgramFromSource(const QString &s, const QString &kname, const QString &options);
    QFileDevice::FileError createProgramFromFile(const QString &fn, const QString &kname, const QString &options);
    qint64 addBuffer(size_t size, cl_mem_flags flags);
    bool writeBuffer(size_t i, const uint8_t *b, size_t s);
    bool readBuffer(size_t i, uint8_t **b, size_t *s);
    void releaseBuffer(size_t i);
    void releaseAll();
    cl_int releaseKernel();
    cl_int releaseProgram();
    void setKernelArg(size_t i, size_t bi);
    void setKernelArg(size_t i, size_t bs, const uint8_t *b);
    void runKernel(QSize s);

signals:
    void progress(size_t percentage);

private:
    Device m_device;
    cl_int m_ret = CL_SUCCESS;
    cl_context m_context = NULL;
    cl_command_queue m_command_queue = NULL;
    cl_program m_program = NULL;
    cl_kernel m_kernel = NULL;

    QList<cl_mem> m_buffers;

    bool m_isRunning = false;
};
}

#endif // OCLWRAPPER_H
