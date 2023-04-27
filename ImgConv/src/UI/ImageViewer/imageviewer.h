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

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>

#include <QPixmap>
#include <QImage>
#include <QPainter>

#include <QMouseEvent>
#include <QWheelEvent>

class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(const QString &title = QString(), QWidget *parent = nullptr);

    QPixmap pixmap() const;

    QString title() const;

public slots:
    void setPixmap(const QPixmap &newPixmap);
    void setTitle(const QString &newTitle);
    void fitImage();

signals:

private:
    QString m_title;
    QPixmap m_pixmap;

    QPoint m_mousePos;
    QSize m_scale;
    QPoint m_imgPos;

    QPoint m_initialImgPosPress;
    QPoint m_initialMousePosPress;
    bool m_mousePressed = false;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent * event) override;

};

#endif // IMAGEVIEWER_H
