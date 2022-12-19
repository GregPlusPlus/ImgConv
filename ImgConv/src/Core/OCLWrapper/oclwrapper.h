#ifndef OCLWRAPPER_H
#define OCLWRAPPER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QSize>

#include <QDebug>

#include <CL/cl.h>

class OCLWrapper : public QObject {
    Q_OBJECT
public:
    explicit OCLWrapper(QObject *parent = nullptr);
    virtual ~OCLWrapper();

    QString getDeviceName();
    QString getBuildLog();
    size_t getNumberOfBuffers() const;

    cl_int ret() const;

public slots:
    void createProgramFromSource(const QString &s, const QString &kname, const QString &options);
    QFileDevice::FileError createProgramFromFile(const QString &fn, const QString &kname, const QString &options);
    qint64 addBuffer(size_t size, cl_mem_flags flags);
    bool writeBuffer(size_t i, const uint8_t *b, size_t s);
    bool readBuffer(size_t i, uint8_t **b, size_t *s);
    void releaseBuffer(size_t i);
    void releaseAll();
    void setKernelArg(size_t i, size_t bi);
    void setKernelArg(size_t i, size_t bs, const uint8_t *b);
    void runKernel(QSize s);

signals:

private:
    cl_int m_ret = CL_SUCCESS;
    cl_platform_id m_platform_id = NULL;
    cl_device_id m_device_id = NULL;
    cl_uint m_ret_num_devices = 0;
    cl_uint m_ret_num_platforms = 0;
    cl_context m_context = NULL;
    cl_command_queue m_command_queue = NULL;
    cl_program m_program = NULL;
    cl_kernel m_kernel = NULL;

    QList<cl_mem> m_buffers;
};

#endif // OCLWRAPPER_H
