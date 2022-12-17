#include "imageviewer.h"

ImageViewer::ImageViewer(const QString &title, QWidget *parent)
    : QWidget{parent}, m_title{title} {
    setMinimumSize(200, 200);
}

QPixmap ImageViewer::pixmap() const {
    return m_pixmap;
}

void ImageViewer::setPixmap(const QPixmap &newPixmap) {
    m_pixmap = newPixmap;

    update();
}

QString ImageViewer::title() const {
    return m_title;
}

void ImageViewer::setTitle(const QString &newTitle) {
    m_title = newTitle;
}

void ImageViewer::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    QPainter p(this);

    if(!m_pixmap.isNull()) {
        p.drawPixmap(QPoint(0, 0),
                     m_pixmap.scaled(size(), Qt::KeepAspectRatio));
    }
}
