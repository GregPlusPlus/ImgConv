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

#include "imagecorrectionpanel.h"

ImageCorrectionPanel::ImageCorrectionPanel(QWidget *parent)
    : QDockWidget{parent} {

    setWindowTitle(tr("Image correction"));

    mw_container = new QWidget(this);

    m_layout = new QGridLayout;

    mw_originalImageHistogram = new HistogramWidget(tr("Original image histogram"), this);
    m_layout->addWidget(mw_originalImageHistogram, 0, 0, 1, 2);

    mw_processedImageHistogram = new HistogramWidget(tr("Processed image histogram"), this);
    m_layout->addWidget(mw_processedImageHistogram, 1, 0, 1, 2);

    mw_container->setLayout(m_layout);
    setWidget(mw_container);
}

HistogramWidget *ImageCorrectionPanel::originalImageHistogramWidget() {
    return mw_originalImageHistogram;
}

HistogramWidget *ImageCorrectionPanel::processedImageHistogramWidget() {
    return mw_processedImageHistogram;
}
