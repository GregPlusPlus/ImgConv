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

#include <QGridLayout>

#include "src/Core/Processing/processing.h"
#include "UI/Components/HistogramWidget/histogramwidget.h"

class ImageCorrectionPanel : public QDockWidget
{
    Q_OBJECT
public:
    ImageCorrectionPanel(QWidget *parent = nullptr);

public slots:
    void setOriginalImageHistogram(const Processing::Algorithms::Histogram &hist);

signals:

private:
    QGridLayout *m_layout;

    HistogramWidget *mw_hist;
};

#endif // IMAGECORRECTIONPANEL_H
