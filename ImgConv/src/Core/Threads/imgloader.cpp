#include "imgloader.h"

Threads::ImgLoader::ImgLoader(const QString &fn)
    : QObject(), QRunnable(), m_fn{fn} {

}

void Threads::ImgLoader::run() {
    QElapsedTimer tm;
    tm.start();

    QImageReader r;
    r.setAllocationLimit(0);
    r.setFileName(m_fn);

    QImage img = r.read().convertToFormat(QImage::Format_RGB888);

    emit loaded(img, tm.elapsed());
}
