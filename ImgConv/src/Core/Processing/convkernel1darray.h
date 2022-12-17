#ifndef CONVKERNEL1DARRAY_H
#define CONVKERNEL1DARRAY_H

#include <QObject>
#include <QSize>

#include <QDebug>

class ConvKernel1DArray : public QObject
{
    Q_OBJECT
public:
    explicit ConvKernel1DArray(const QVector<QVector<float>> &k);
    virtual ~ConvKernel1DArray();

    size_t size() const;
    size_t buffSize() const;

    float *getKArray() const;

signals:

private:
    float *m_k = nullptr;
    size_t m_s;

};

#endif // CONVKERNEL1DARRAY_H
