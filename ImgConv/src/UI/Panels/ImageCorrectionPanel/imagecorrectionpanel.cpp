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

    mw_convertGrayscaleButton = new QPushButton(tr("Convert to grayscale"), this);
    connect(mw_convertGrayscaleButton, &QPushButton::clicked, this, &ImageCorrectionPanel::convertToGrayscale);
    m_layout->addWidget(mw_convertGrayscaleButton, 2, 0, 1, 1);

    mw_invertColorsButton = new QPushButton(tr("Invert colors"), this);
    connect(mw_invertColorsButton, &QPushButton::clicked, this, &ImageCorrectionPanel::invertColors);
    m_layout->addWidget(mw_invertColorsButton, 2, 1, 1, 1);

    mw_histogramEqualizationButton = new QPushButton(tr("Histogram equalization"), this);
    connect(mw_histogramEqualizationButton, &QPushButton::clicked, this, &ImageCorrectionPanel::equalizeHistogram);
    m_layout->addWidget(mw_histogramEqualizationButton, 3, 0, 1, 2);

    mw_container->setLayout(m_layout);
    setWidget(mw_container);
}

Processing::Algorithms::Histogram ImageCorrectionPanel::originalImageHistogram() {
    return mw_originalImageHistogram->histogram();
}

Processing::Algorithms::Histogram ImageCorrectionPanel::processedImageHistogram() {
    return mw_processedImageHistogram->histogram();
}

void ImageCorrectionPanel::displayHistogram(const Processing::Algorithms::Histogram &histogram, ImageCorrectionPanel::HistogramRole role) {
    switch(role) {
    case OriginalImageHistogram:
        mw_originalImageHistogram->setHistogram(histogram);
        break;
    case ProcessedImageHistogram:
        mw_processedImageHistogram->setHistogram(histogram);
        break;
    default:
        break;
    }
}

void ImageCorrectionPanel::setOriginalImageHistogram(const Processing::Algorithms::Histogram &histtogram) {
    mw_originalImageHistogram->setHistogram(histtogram);
}

void ImageCorrectionPanel::setProcessedImageHistogram(const Processing::Algorithms::Histogram &histogram) {
    mw_originalImageHistogram->setHistogram(histogram);
}

void ImageCorrectionPanel::clearOriginalImageHistogram() {
    mw_originalImageHistogram->clear();
}

void ImageCorrectionPanel::clearProcessedImageHistogram()
{
    mw_processedImageHistogram->clear();
}
