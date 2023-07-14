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

#include "oclwrapper.h"

using namespace Core;

OCLWrapper::OCLWrapper(const Device &d, QObject *parent)
    : QObject{parent}, m_device{d} {

    m_ret = CL_SUCCESS;

    m_context = clCreateContext(NULL, 1, &m_device.device, NULL, NULL, &m_ret);
    if(m_ret != CL_SUCCESS) {
        return;
    }

    m_command_queue = clCreateCommandQueue(m_context, m_device.device, 0, &m_ret);
    if(m_ret != CL_SUCCESS) {
        return;
    }
}

OCLWrapper::~OCLWrapper() {
    if(m_command_queue) {
        clFlush(m_command_queue);
        clFinish(m_command_queue);
    }

    releaseKernel();
    releaseProgram();

    releaseAll();

    if(m_command_queue) {
        clReleaseCommandQueue(m_command_queue);
    }

    if(m_context) {
        clReleaseContext(m_context);
    }
}

QString OCLWrapper::getDeviceName() {
    size_t buffSize = 0;
    QString str;

    m_ret = clGetDeviceInfo(m_device.device, CL_DEVICE_NAME,
                            0, NULL, &buffSize);
    if(m_ret != CL_SUCCESS) {
        return QString();
    }

    char *buff = new char[buffSize];

    m_ret = clGetDeviceInfo(m_device.device, CL_DEVICE_NAME,
                            buffSize, buff, NULL);

    str = QString(buff);
    delete[] buff;

    return str;
}

QString OCLWrapper::getBuildLog() {
    size_t buffSize = 0;
    QString str;

    m_ret = clGetProgramBuildInfo(m_program, m_device.device, CL_PROGRAM_BUILD_LOG,
                                  0, NULL, &buffSize);

    if(m_ret != CL_SUCCESS) {
        return QString();
    }

    char *buff = new char[buffSize];

    m_ret = clGetProgramBuildInfo(m_program, m_device.device, CL_PROGRAM_BUILD_LOG,
                                  buffSize, buff, NULL);

    str = QString(buff);
    delete[] buff;

    return str;
}

size_t OCLWrapper::getNumberOfBuffers() const {
    return m_buffers.size();
}

void OCLWrapper::createProgramFromSource(const QString &s, const QString &kname, const QString &options) {
    m_ret = CL_SUCCESS;

    if(releaseKernel() != CL_SUCCESS) {
        return;
    }

    if(releaseProgram() != CL_SUCCESS) {
        return;
    }

    size_t size = s.size();
    char *source = new char[size];

    memcpy(source, (const char *)s.toStdString().c_str(), size);

    m_program = clCreateProgramWithSource(m_context, 1, (const char **)&source, (const size_t *)&size, &m_ret);
    delete[] source;

    if(m_ret != CL_SUCCESS) {
        return;
    }

    m_ret = clBuildProgram(m_program, 1, &m_device.device, options.toStdString().c_str(), NULL, NULL);
    if(m_ret != CL_SUCCESS) {
        return;
    }

    m_kernel = clCreateKernel(m_program, kname.toStdString().c_str(), &m_ret);
    if(m_ret != CL_SUCCESS) {
        return;
    }
}

QFileDevice::FileError OCLWrapper::createProgramFromFile(const QString &fn, const QString &kname, const QString &options) {
    QFile f(fn);

    if(!f.open(QFile::ReadOnly)) {
        f.close();
        return f.error();
    }

    createProgramFromSource(QString::fromUtf8(f.readAll()), kname, options);

    f.close();

    return f.error();
}

qint64 OCLWrapper::addBuffer(size_t size, cl_mem_flags flags) {
    cl_mem mem = clCreateBuffer(m_context, flags, size, NULL, &m_ret);

    if(m_ret != CL_SUCCESS) {
        return -1;
    }

    m_buffers.append(mem);

    return m_buffers.size() - 1;
}

bool OCLWrapper::writeBuffer(size_t i, const uint8_t *b, size_t s) {
    if(i > (size_t)m_buffers.size()) {
        return false;
    }

    m_ret = clEnqueueWriteBuffer(m_command_queue, m_buffers.at(i), CL_TRUE, 0, s, b, 0, NULL, NULL);

    return true;
}

bool OCLWrapper::readBuffer(size_t i, uint8_t **b, size_t *s) {
    if(i > (size_t)m_buffers.size()) {
        return false;
    }

    m_ret = clGetMemObjectInfo(m_buffers.at(i), CL_MEM_SIZE, sizeof(size_t), (size_t*)s, NULL);

    if(m_ret != CL_SUCCESS) {
        return false;
    }

    *b = new uint8_t[(*s)];

    m_ret = clEnqueueReadBuffer(m_command_queue, m_buffers.at(i), CL_TRUE, 0,
                                (*s), (*b), 0, NULL, NULL);

    if(m_ret != CL_SUCCESS) {
        delete[] (*b);

        return false;
    }

    return true;
}

void OCLWrapper::releaseBuffer(size_t i) {
    m_ret = clReleaseMemObject(m_buffers.at(i));

    m_buffers.removeAt(i);
}

void OCLWrapper::releaseAll() {
    while(m_buffers.size()) {
        releaseBuffer(0);
    }
}

cl_int OCLWrapper::releaseKernel() {
    m_ret = CL_SUCCESS;

    if(m_kernel) {
        m_ret = clReleaseKernel(m_kernel);

        m_kernel = nullptr;
    }

    return m_ret;
}

cl_int OCLWrapper::releaseProgram() {
    m_ret = CL_SUCCESS;

    if(m_program) {
        m_ret = clReleaseProgram(m_program);

        m_program = nullptr;
    }

    return m_ret;
}

void OCLWrapper::setKernelArg(size_t i, size_t bi) {
    m_ret = clSetKernelArg(m_kernel, i, sizeof(cl_mem), (void*)&m_buffers.at(bi));
}

void OCLWrapper::setKernelArg(size_t i, size_t bs, const uint8_t *b) {
    m_ret = clSetKernelArg(m_kernel, i, bs, b);
}

void OCLWrapper::runKernel(QSize s) {
    size_t global_item_size[2] = {(size_t)s.width() / getChunkFactor(),
                                  (size_t)s.height() / getChunkFactor()};
    size_t global_item_offset[2] = {0, 0};

    m_isRunning = true;

    for(size_t i = 0; i < getChunkFactor(); i ++) {
        global_item_offset[1] = i * ((size_t)s.height() / getChunkFactor());

        if(i == (getChunkFactor() - 1)) {
            global_item_size[1] += ((size_t)s.height() % getChunkFactor());
        }

        for(size_t j = 0; j < getChunkFactor(); j ++) {
            global_item_offset[0] = j * ((size_t)s.width() / getChunkFactor());

            if(j == (getChunkFactor() - 1)) {
                global_item_size[0] += ((size_t)s.width() % getChunkFactor());
            } else {
                global_item_size[0] = ((size_t)s.width() / getChunkFactor());
            }

            m_ret = clEnqueueNDRangeKernel(m_command_queue, m_kernel, 2, global_item_offset,
                                           global_item_size, NULL, 0, NULL, NULL);

            if(m_ret != CL_SUCCESS) {
                m_isRunning = false;

                return;
            }

            m_ret = clFinish(m_command_queue);

            if(m_ret != CL_SUCCESS) {
                m_isRunning = false;

                return;
            }

            emit progress(100 * (((i * getChunkFactor()) + j + 1) / (float)(getChunkFactor() * getChunkFactor())));

            if(m_cancelRequested) {
                m_cancelRequested = false;
                m_isRunning = false;

                emit kernelCanceled();

                return;
            }
        }
    }

    m_isRunning = false;
}

bool OCLWrapper::cancelRequested() const {
    return m_cancelRequested;
}

void OCLWrapper::requestKernelCancelation() {
    if(m_isRunning) {
        m_cancelRequested = true;

        emit kernelCancelationRequested();
    }
}

size_t OCLWrapper::getChunkFactor() const {
    return m_chunkFactor;
}

void OCLWrapper::setChunkFactor(size_t chunkSize) {
    if(!isRunning()) {
        m_chunkFactor = chunkSize;
    }
}

bool OCLWrapper::isRunning() const {
    return m_isRunning;
}

cl_int OCLWrapper::ret() const {
    return m_ret;
}
