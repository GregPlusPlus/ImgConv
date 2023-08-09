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

using namespace UI::GUI::Components;

ImageViewer::ImageViewer(const QString &title, QWidget *parent)
    : QWidget{parent} {

    m_layout = new QVBoxLayout;

    mw_status = new QStatusBar(this);
    mw_status->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    mw_status->setSizeGripEnabled(false);

    mw_viewer = new ImageDisplay(title, this);

    mw_fitButton = new QPushButton(QIcon(":/icons/magnifier-zoom-fit.png"), QString(), this);
    mw_fitButton->setToolTip(tr("Fit image"));
    connect(mw_fitButton, &QPushButton::clicked, mw_viewer, &ImageDisplay::fitImage);

    mw_status->addPermanentWidget(mw_fitButton);

    m_layout->addWidget(mw_viewer);
    m_layout->addWidget(mw_status);

    setLayout(m_layout);
}

QPixmap ImageViewer::pixmap() const {
    return mw_viewer->pixmap();
}

QString ImageViewer::title() const {
    return mw_viewer->title();
}

void ImageViewer::setPixmap(const QPixmap &pixmap) {
    mw_viewer->setPixmap(pixmap);
}

void ImageViewer::setTitle(const QString &title) {
    mw_viewer->setTitle(title);
}
