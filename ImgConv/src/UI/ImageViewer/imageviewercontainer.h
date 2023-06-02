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

#ifndef IMAGEVIEWERCONTAINER_H
#define IMAGEVIEWERCONTAINER_H

#include <QWidget>
#include <QPushButton>
#include <QStatusBar>

#include <QVBoxLayout>

#include "imageviewer.h"

namespace UI {
class ImageViewerContainer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewerContainer(const QString &title = QString(), QWidget *parent = nullptr);

    QPixmap pixmap() const;
    QString title() const;

public slots:
    void setPixmap(const QPixmap &pixmap);
    void setTitle(const QString &title);

signals:

private:
    QVBoxLayout *m_layout;

    QStatusBar *mw_status;
    QPushButton *mw_fitButton;

    ImageViewer *mw_viewer;

};
}

#endif // IMAGEVIEWERCONTAINER_H
