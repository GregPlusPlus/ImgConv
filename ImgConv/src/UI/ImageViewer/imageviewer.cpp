/**
 ** This file is part of the ImgConv project.
 ** Copyright 2022-2023 Grégoire BOST <bostgregoire@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include "imageviewer.h"

ImageViewer::ImageViewer(const QString &title, QWidget *parent)
    : QWidget{parent}, m_title{title} {
    setMouseTracking(true);
    setCursor(Qt::OpenHandCursor);
}

QPixmap ImageViewer::pixmap() const {
    return m_pixmap;
}

void ImageViewer::setPixmap(const QPixmap &newPixmap) {
    m_pixmap = newPixmap;

    fitImage();
}

QString ImageViewer::title() const {
    return m_title;
}

void ImageViewer::setTitle(const QString &newTitle) {
    m_title = newTitle;
}

void ImageViewer::fitImage() {
    m_scale = m_pixmap.scaled(size(), Qt::KeepAspectRatio).size();

    if(m_scale.width() >= width()) {
        m_imgPos.setX(0);
        m_imgPos.setY((height() / 2) - (m_scale.height() / 2));
    } else if(m_scale.height() >= height()) {
        m_imgPos.setX((width() / 2) - (m_scale.width() / 2));
        m_imgPos.setY(0);
    }

    update();
}

void ImageViewer::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    QPainter p(this);
    p.setPen(Qt::black);

    if(!m_pixmap.isNull()) {
        QPixmap pix = m_pixmap.scaled(m_scale);

        p.drawPixmap(m_imgPos, pix);
    }
}

void ImageViewer::mouseMoveEvent(QMouseEvent *event) {
    m_mousePos = event->pos();

    if(m_mousePressed) {
        m_imgPos = m_initialImgPosPress + (event->pos() - m_initialMousePosPress);

        update();
    }
}

void ImageViewer::mousePressEvent(QMouseEvent *event) {
    setCursor(Qt::ClosedHandCursor);

    if(event->button() == Qt::LeftButton) {
        m_mousePressed = true;

        m_initialImgPosPress = m_imgPos;
        m_initialMousePosPress = event->pos();
    }
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event) {
    setCursor(Qt::OpenHandCursor);

    if(event->button() == Qt::LeftButton) {
        m_mousePressed = false;
    }
}

void ImageViewer::wheelEvent(QWheelEvent *event) {
    float factor = 0.8;
    if (event->angleDelta().y() < 0) {
        factor = 1 / factor;
    }

    QPoint dP((m_mousePos.x() - m_imgPos.x()) * (factor - 1),
              (m_mousePos.y() - m_imgPos.y()) * (factor - 1));

    if((event->angleDelta().y() > 0) && ((m_scale.width() < 100) || (m_scale.height() < 100))) {
        return;
    }

    m_scale = QSize(m_scale.width() * factor, m_scale.height() * factor);
    m_imgPos = m_imgPos - dP;

    m_initialImgPosPress = m_imgPos;
    m_initialMousePosPress = mapFromGlobal(QCursor::pos());

    update();
}
