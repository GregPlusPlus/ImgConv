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
