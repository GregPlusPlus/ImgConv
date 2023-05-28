#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QWidget>

#include "src/Core/Processing/processing.h"

class HistogramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistogramWidget(QWidget *parent = nullptr);

public slots:
    void setHistogram(const Processing::Algorithms::Histogram &histogram);

signals:

private:
    Processing::Algorithms::Histogram m_histogram;

};

#endif // HISTOGRAMWIDGET_H
