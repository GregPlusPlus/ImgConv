#ifndef CONVKERNEL_H
#define CONVKERNEL_H

#include <QObject>
#include <QVector>

namespace ConvKernels {
class ConvKernel : public QObject
{
    Q_OBJECT
public:
    explicit ConvKernel(QObject *parent = nullptr);

    virtual QVector<QVector<float>> getMat() const = 0;
    virtual float getScalar() const = 0;
    virtual QString getName() const = 0;

public slots:
    virtual void reset() {}

signals:

};
}

#endif // CONVKERNEL_H
