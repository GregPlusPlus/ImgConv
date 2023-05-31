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

    mw_radioHistogram = new QRadioButton(tr("Histogram"), this);
    connect(mw_radioHistogram, &QRadioButton::toggled, this, &ImageCorrectionPanel::displayHistCDF);
    m_layout->addWidget(mw_radioHistogram, 0, 0, 1, 1);

    mw_radioCDF = new QRadioButton("CDF", this);
    mw_radioCDF->setToolTip(tr("Cumulative Distribution Frequency"));
    m_layout->addWidget(mw_radioCDF, 0, 1, 1, 1);
    connect(mw_radioCDF, &QRadioButton::toggled, this, &ImageCorrectionPanel::displayHistCDF);

    mw_originalImageHistogram = new HistogramWidget(tr("Original image histogram"), this);
    mw_processedImageHistogram = new HistogramWidget(tr("Processed image histogram"), this);
    mw_originalImageCDF = new HistogramWidget(tr("Original image CDF"), this);
    mw_processedImageCDF = new HistogramWidget(tr("Processed image CDF"), this);

    mw_convertGrayscaleButton = new QPushButton(tr("Convert to grayscale"), this);
    connect(mw_convertGrayscaleButton, &QPushButton::clicked, this, &ImageCorrectionPanel::convertToGrayscale);
    m_layout->addWidget(mw_convertGrayscaleButton, 4, 0, 1, 1);

    mw_invertColorsButton = new QPushButton(tr("Invert colors"), this);
    connect(mw_invertColorsButton, &QPushButton::clicked, this, &ImageCorrectionPanel::invertColors);
    m_layout->addWidget(mw_invertColorsButton, 4, 1, 1, 1);

    mw_histogramEqualizationButton = new QPushButton(tr("Histogram equalization"), this);
    connect(mw_histogramEqualizationButton, &QPushButton::clicked, this, &ImageCorrectionPanel::equalizeHistogram);
    m_layout->addWidget(mw_histogramEqualizationButton, 5, 0, 1, 2);

    mw_container->setLayout(m_layout);
    setWidget(mw_container);

    mw_radioHistogram->toggle();
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
        setOriginalImageHistogram(histogram);
        break;
    case ProcessedImageHistogram:
        setProcessedImageHistogram(histogram);
        break;
    default:
        break;
    }
}

void ImageCorrectionPanel::setOriginalImageHistogram(const Processing::Algorithms::Histogram &histogram) {
    mw_originalImageHistogram->setHistogram(histogram);
    mw_originalImageCDF->setHistogram(histogram.getCDF());
}

void ImageCorrectionPanel::setProcessedImageHistogram(const Processing::Algorithms::Histogram &histogram) {
    mw_processedImageHistogram->setHistogram(histogram);
    mw_processedImageCDF->setHistogram(histogram.getCDF());
}

void ImageCorrectionPanel::clearOriginalImageHistogram() {
    mw_originalImageHistogram->clear();
    mw_originalImageCDF->clear();
}

void ImageCorrectionPanel::clearProcessedImageHistogram()
{
    mw_processedImageHistogram->clear();
    mw_processedImageCDF->clear();
}

void ImageCorrectionPanel::displayHistCDF() {
    if(mw_radioHistogram->isChecked()) {
        mw_originalImageCDF->hide();
        mw_processedImageCDF->hide();
        m_layout->removeWidget(mw_originalImageCDF);
        m_layout->removeWidget(mw_processedImageCDF);
        m_layout->addWidget(mw_originalImageHistogram, 1, 0, 1, 2);
        m_layout->addWidget(mw_processedImageHistogram, 2, 0, 1, 2);
        mw_originalImageHistogram->show();
        mw_processedImageHistogram->show();
    } else if(mw_radioCDF->isChecked()) {
        mw_originalImageHistogram->hide();
        mw_processedImageHistogram->hide();
        m_layout->removeWidget(mw_originalImageHistogram);
        m_layout->removeWidget(mw_processedImageHistogram);
        m_layout->addWidget(mw_originalImageCDF, 1, 0, 1, 2);
        m_layout->addWidget(mw_processedImageCDF, 2, 0, 1, 2);
        mw_originalImageCDF->show();
        mw_processedImageCDF->show();
    }
}
