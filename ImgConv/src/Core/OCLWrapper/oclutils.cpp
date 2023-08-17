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

#include "oclutils.h"

QString Core::OCLUtils::getDevicesInfoStr() {
    QString str;

    char* value;
    size_t valueSize;
    cl_uint platformCount;
    cl_platform_id* platforms;
    cl_uint deviceCount;
    cl_device_id* devices;
    cl_uint maxComputeUnits;

    clGetPlatformIDs(0, NULL, &platformCount);
    platforms = new cl_platform_id[platformCount];
    clGetPlatformIDs(platformCount, platforms, NULL);

    for(cl_uint i = 0; i < platformCount; i ++) {

        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &valueSize);
        value = new char[valueSize];
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, valueSize, value, NULL);
        str += QObject::tr("%1. Platform: %2\n").arg(i+1).arg(value);
        delete[] value;

        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
        devices = new cl_device_id[deviceCount];
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

        for(cl_uint j = 0; j < deviceCount; j ++) {

            // Print device name
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
            value = new char[valueSize];
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
            str += QObject::tr("  %1. Device: %2\n").arg(j+1).arg(value);
            delete[] value;

            // Print hardware device version
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
            value = new char[valueSize];
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
            str += QObject::tr("    %1.1 Hardware version: %2\n").arg(j+1).arg(value);
            delete[] value;

            // Print software driver version
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
            value = new char[valueSize];
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
            str += QObject::tr("    %1.2 Software version: %2\n").arg(j+1).arg(value);
            delete[] value;

            // Print c version supported by compiler for device
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
            value = new char[valueSize];
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
            str += QObject::tr("    %1.3 OpenCL C version: %2\n").arg(j+1).arg(value);
            delete[] value;

            // Print parallel compute units
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
                    sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            str += QObject::tr("    %1.4 Parallel compute units: %2\n").arg(j+1).arg(maxComputeUnits);

        }

        str += '\n';

        delete[] devices;
    }

    delete[] platforms;

    return str;
}

QList<Core::OCLWrapper::Device> Core::OCLUtils::getDevices() {
    QList<OCLWrapper::Device> list;

    char* value;
    size_t valueSize;
    cl_uint platformCount;
    cl_platform_id* platforms;
    cl_uint deviceCount;
    cl_device_id* devices;

    clGetPlatformIDs(0, NULL, &platformCount);
    platforms = new cl_platform_id[platformCount];
    clGetPlatformIDs(platformCount, platforms, NULL);

    for(cl_uint i = 0; i < platformCount; i ++) {

        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
        devices = new cl_device_id[deviceCount];
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

        for(cl_uint j = 0; j < deviceCount; j ++) {

            OCLWrapper::Device device;

            device.device = devices[j];
            device.platform = platforms[i];

            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
            value = new char[valueSize];
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
            device.name = QString("%1.%2. %3").arg(i + 1).arg(j + 1).arg(value);
            delete[] value;

            list.append(device);
        }

        delete[] devices;
    }

    delete[] platforms;

    return list;
}
