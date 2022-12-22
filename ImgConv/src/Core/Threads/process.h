#ifndef PROCESS_H
#define PROCESS_H

#include <QRunnable>
#include <QImage>
#include <QElapsedTimer>
#include <QVector>

#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/Processing/processing.h"

namespace Threads {
class Process : public QObject, public QRunnable
{
    Q_OBJECT

public:
    Process(OCLWrapper *ocl, const QImage &original, const QVector<QVector<float>> &mat);

    void run() override;

signals:
    void finished(const QImage &img, qint64 et, bool res);

private:
    OCLWrapper *m_ocl;
    QImage m_original;
    QVector<QVector<float>> m_mat;
};
}

#endif // PROCESS_H
