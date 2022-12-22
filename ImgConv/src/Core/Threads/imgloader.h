#ifndef IMGLOADER_H
#define IMGLOADER_H

#include <QRunnable>
#include <QImage>
#include <QImageReader>
#include <QElapsedTimer>

namespace Threads {
class ImgLoader : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ImgLoader(const QString &fn);

    void run() override;

signals:
    void loaded(const QImage &img, qint64 et);

private:
    QString m_fn;
    QImage *m_img;
};
}

#endif // IMGLOADER_H
