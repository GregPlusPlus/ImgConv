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

void OCLWrapper::createProgramFromSource(const QString &s, const QString &kname) {
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

    m_ret = clBuildProgram(m_program, 1, &m_device_id, NULL, NULL, NULL);
    if(m_ret != CL_SUCCESS) {
        return;
    }

    m_kernel = clCreateKernel(m_program, kname.toStdString().c_str(), &m_ret);
    if(m_ret != CL_SUCCESS) {
        return;
    }
}

QFileDevice::FileError OCLWrapper::createProgramFromFile(const QString &fn, const QString &kname) {
    QFile f(fn);

    if(!f.open(QFile::ReadOnly)) {
        return f.error();
    }

    createProgramFromSource(QString::fromUtf8(f.readAll()), kname);

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

void OCLWrapper::runKernel(size_t w, size_t h) {
    size_t global_item_size[2] = {w, h};

    m_ret = clEnqueueNDRangeKernel(m_command_queue, m_kernel, 2, NULL,
            global_item_size, NULL, 0, NULL, NULL);

    if(m_ret != CL_SUCCESS) {
        return;
    }

    m_ret = clFinish(m_command_queue);
}

cl_int OCLWrapper::ret() const {
    return m_ret;
}
