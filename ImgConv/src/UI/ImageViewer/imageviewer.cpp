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

using namespace UI;

ImageViewer::ImageViewer(const QString &title, QWidget *parent)
    : QWidget{parent}, m_title{title} {
    setMouseTracking(true);
    setCursor(Qt::OpenHandCursor);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
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
    updateGeometry();

    if(m_pixmap.isNull()) {
        m_imgPos = QPoint(0, 0);
        m_scaledPix = QPixmap();

        return;
    }

    updatePixScale(m_pixmap.scaled(size(), Qt::KeepAspectRatio).size());

    if(m_scaledPix.width() >= width()) {
        m_imgPos.setX(0);
        m_imgPos.setY((height() / 2) - (m_scaledPix.height() / 2));
    } else if(m_scaledPix.height() >= height()) {
        m_imgPos.setX((width() / 2) - (m_scaledPix.width() / 2));
        m_imgPos.setY(0);
    }

    update();
}

void ImageViewer::updatePixScale(const QSize &s) {
    if(m_pixmap.isNull()) {
        return;
    }

    m_scaledPix = m_pixmap.scaled(s, Qt::IgnoreAspectRatio, Qt::FastTransformation);
}

void ImageViewer::drawBackground(QPainter &painter) {
    painter.setPen(Qt::NoPen);

    for(int x = 0; x < (width() + m_checkerboardSize); x += m_checkerboardSize) {
        for(int y = 0; y < (height() + m_checkerboardSize); y += m_checkerboardSize) {
            QPoint p(x, y);

            if(p.x() % (m_checkerboardSize * 2)) {
                painter.setBrush(Qt::lightGray);
            } else {
                painter.setBrush(Qt::NoBrush);
            }

            if(y % (m_checkerboardSize * 2)) {
                p -= QPoint(m_checkerboardSize, 0);
            }

            painter.drawRect(QRect(p, QSize(m_checkerboardSize, m_checkerboardSize)));
        }
    }
}

int ImageViewer::checkerboardSize() const {
    return m_checkerboardSize;
}

void ImageViewer::setCheckerboardSize(int newCheckerboardSize) {
    m_checkerboardSize = newCheckerboardSize;

    update();
}

void ImageViewer::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    QPainter p(this);

    drawBackground(p);

    p.setPen(Qt::black);

    if(!m_pixmap.isNull()) {
        p.drawPixmap(m_imgPos, m_scaledPix);
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
    int delta = -event->angleDelta().y();

    if (delta < 0) {
        factor = 1 / factor;
    }

    QPoint dP((m_mousePos.x() - m_imgPos.x()) * (factor - 1),
              (m_mousePos.y() - m_imgPos.y()) * (factor - 1));

    if((delta > 0) && ((m_scaledPix.width() < 100) || (m_scaledPix.height() < 100))) {
        return;
    }

    updatePixScale(QSize(m_scaledPix.width() * factor, m_scaledPix.height() * factor));
    m_imgPos = m_imgPos - dP;

    m_initialImgPosPress = m_imgPos;
    m_initialMousePosPress = mapFromGlobal(QCursor::pos());

    update();
}

void ImageViewer::resizeEvent(QResizeEvent *event) {
    if( (m_scaledPix.width() == event->oldSize().width()) ||
        (m_scaledPix.height() == event->oldSize().height())) {
        fitImage();
    }

    QWidget::resizeEvent(event);
}
