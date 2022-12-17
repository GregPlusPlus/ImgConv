#include "imageviewer.h"

ImageViewer::ImageViewer(const QString &title, QWidget *parent)
    : QWidget{parent}, m_title{title} {
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
    p.setPen(Qt::black);

    if(!m_pixmap.isNull()) {
        QPixmap pix = m_pixmap.scaled(size(), Qt::KeepAspectRatio);

        p.drawPixmap(QPoint(width() / 2 - pix.width() / 2,
                            height() / 2 - pix.height() / 2),
                     pix);
    }

    p.drawRect(0, 0, width() - 1, height() - 1);
}
