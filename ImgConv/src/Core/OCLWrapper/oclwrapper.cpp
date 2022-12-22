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

OCLWrapper::OCLWrapper(QObject *parent)
    : QObject{parent} {

    m_ret = CL_SUCCESS;

    m_ret = clGetPlatformIDs(1, &m_platform_id, &m_ret_num_platforms);
    if(m_ret != CL_SUCCESS) {
        return;
    }

    m_ret = clGetDeviceIDs(m_platform_id, CL_DEVICE_TYPE_ALL, 1, &m_device_id, &m_ret_num_devices);
    if(m_ret != CL_SUCCESS) {
        return;
    }

    m_context = clCreateContext(NULL, 1, &m_device_id, NULL, NULL, &m_ret);
    if(m_ret != CL_SUCCESS) {
        return;
    }

    m_command_queue = clCreateCommandQueue(m_context, m_device_id, 0, &m_ret);
    if(m_ret != CL_SUCCESS) {
        return;
    }
}

OCLWrapper::~OCLWrapper() {
    if(m_command_queue) {
        clFlush(m_command_queue);
        clFinish(m_command_queue);
    }

    if(m_kernel) {
        clReleaseKernel(m_kernel);
    }

    if(m_program) {
        clReleaseProgram(m_program);
    }

    releaseAll();

    if(m_command_queue) {
        clReleaseCommandQueue(m_command_queue);
    }

    if(m_context) {
        clReleaseContext(m_context);
    }
}

QString OCLWrapper::getDeviceName() {
    char device_name_buffer[128] = {0};

    m_ret = clGetDeviceInfo(m_device_id, CL_DEVICE_NAME,
                            sizeof(device_name_buffer), device_name_buffer, NULL);
    if(m_ret != CL_SUCCESS) {
        return QString();
    }

    return QString(device_name_buffer);
}

QString OCLWrapper::getBuildLog() {
    char program_log_buffer[128] = {0};

    m_ret = clGetProgramBuildInfo(m_program, m_device_id, CL_PROGRAM_BUILD_LOG,
                                  sizeof(program_log_buffer), program_log_buffer, NULL);

    if(m_ret != CL_SUCCESS) {
        return QString();
    }

    return QString(program_log_buffer);
}

size_t OCLWrapper::getNumberOfBuffers() const {
    return m_buffers.size();
}

void OCLWrapper::createProgramFromSource(const QString &s, const QString &kname, const QString &options) {
    m_ret = CL_SUCCESS;

    if(m_kernel) {
        m_ret = clReleaseKernel(m_kernel);
        if(m_ret != CL_SUCCESS) {
            return;
        }
    }

    if(m_program) {
        m_ret = clReleaseProgram(m_program);
        if(m_ret != CL_SUCCESS) {
            return;
        }
    }

    size_t size = s.size();
    char *source = new char[size];

    memcpy(source, (const char *)s.toStdString().c_str(), size);

    m_program = clCreateProgramWithSource(m_context, 1, (const char **)&source, (const size_t *)&size, &m_ret);
    delete[] source;

    if(m_ret != CL_SUCCESS) {
        return;
    }

    m_ret = clBuildProgram(m_program, 1, &m_device_id, options.toStdString().c_str(), NULL, NULL);
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
        return f.error();
    }

    createProgramFromSource(QString::fromUtf8(f.readAll()), kname, options);

    return QFileDevice::NoError;
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

void OCLWrapper::setKernelArg(size_t i, size_t bi) {
    m_ret = clSetKernelArg(m_kernel, i, sizeof(cl_mem), (void*)&m_buffers.at(bi));
}

void OCLWrapper::setKernelArg(size_t i, size_t bs, const uint8_t *b) {
    m_ret = clSetKernelArg(m_kernel, i, bs, b);
}

void OCLWrapper::runKernel(QSize s) {
    size_t global_item_size[2] = {(size_t)s.width(), (size_t)s.height()};
    //size_t local_item_size[2] = {1, 1};

    m_ret = clEnqueueNDRangeKernel(m_command_queue, m_kernel, 2, NULL,
            global_item_size, /*local_item_size*/NULL, 0, NULL, NULL);

    if(m_ret != CL_SUCCESS) {
        return;
    }

    m_ret = clFinish(m_command_queue);
}

cl_int OCLWrapper::ret() const {
    return m_ret;
}

QString OCLWrapper::getDevicesInfoStr() {
    QString str;

    char* value;
    size_t valueSize;
    cl_uint platformCount;
    cl_platform_id* platforms;
    cl_uint deviceCount;
    cl_device_id* devices;
    cl_uint maxComputeUnits;

    // get all platforms
    clGetPlatformIDs(0, NULL, &platformCount);
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);

    for(cl_uint i = 0; i < platformCount; i ++) {

        // get all devices
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
        devices = (cl_device_id*) malloc(sizeof(cl_device_id) * deviceCount);
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

        // for each device print critical attributes
        for(cl_uint j = 0; j < deviceCount; j ++) {

            // print device name
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
            str += tr("%1. Device: %2\n").arg(j+1).arg(value);
            free(value);

            // print hardware device version
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
            str += tr(" %1.1 Hardware version: %2\n").arg(j+1).arg(value);
            free(value);

            // print software driver version
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
            str += tr(" %1.2 Software version: %2\n").arg(j+1).arg(value);
            free(value);

            // print c version supported by compiler for device
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
            str += tr(" %1.3 OpenCL C version: %2\n").arg(j+1).arg(value);
            free(value);

            // print parallel compute units
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
                    sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            str += tr(" %1.4 Parallel compute units: %2\n").arg(j+1).arg(maxComputeUnits);

        }

        free(devices);
    }

    free(platforms);

    return str;
}
