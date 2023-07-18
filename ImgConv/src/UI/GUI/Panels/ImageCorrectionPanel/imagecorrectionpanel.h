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

#ifndef IMAGECORRECTIONPANEL_H
#define IMAGECORRECTIONPANEL_H

#include <QDockWidget>
#include <QPushButton>
#include <QRadioButton>

#include <QGridLayout>

#include "Core/Processing/processing.h"
#include "UI/GUI/Components/HistogramWidget/histogramwidget.h"

namespace UI::GUI::Panels {
class ImageCorrectionPanel : public QDockWidget
{
    Q_OBJECT

public:
    enum HistogramRole {
        OriginalImageHistogram,
        ProcessedImageHistogram
    };

public:
    ImageCorrectionPanel(QWidget *parent = nullptr);

    Core::Processing::Algorithms::Histogram originalImageHistogram();
    Core::Processing::Algorithms::Histogram processedImageHistogram();

public slots:
    void displayHistogram(const Core::Processing::Algorithms::Histogram &histogram, ImageCorrectionPanel::HistogramRole role);
    void setOriginalImageHistogram(const Core::Processing::Algorithms::Histogram &histogram);
    void setProcessedImageHistogram(const Core::Processing::Algorithms::Histogram &histogram);
    void clearOriginalImageHistogram();
    void clearProcessedImageHistogram();

signals:
    void convertToGrayscale();
    void invertColors();
    void equalizeHistogram();

private slots:
    void displayHistCDF();

private:
    QGridLayout *m_layout;
    QWidget *mw_container;

    QRadioButton *mw_radioHistogram;
    QRadioButton *mw_radioCDF;

    QPushButton *mw_convertGrayscaleButton;
    QPushButton *mw_invertColorsButton;
    QPushButton *mw_histogramEqualizationButton;

    Components::HistogramWidget *mw_originalImageHistogram;
    Components::HistogramWidget *mw_processedImageHistogram;
    Components::HistogramWidget *mw_originalImageCDF;
    Components::HistogramWidget *mw_processedImageCDF;
};
}

#endif // IMAGECORRECTIONPANEL_H
