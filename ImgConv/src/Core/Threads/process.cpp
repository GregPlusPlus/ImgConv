#include "process.h"

Threads::Process::Process(OCLWrapper *ocl, const QImage &original, const QVector<QVector<float> > &mat)
    : QObject(), QRunnable(), m_ocl{ocl}, m_original{original}, m_mat{mat} {

}

void Threads::Process::run() {
    QImage processed;

    QElapsedTimer tm;
    tm.start();

    bool res = Processing::processImg(m_ocl, m_original, processed, m_mat);

    emit finished(processed, tm.elapsed(), res);
}
