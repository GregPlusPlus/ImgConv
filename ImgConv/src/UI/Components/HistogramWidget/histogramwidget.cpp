#include "histogramwidget.h"

HistogramWidget::HistogramWidget(QWidget *parent)
    : QWidget{parent} {

}

Processing::Algorithms::Histogram HistogramWidget::histogram() const {
    return m_histogram;
}

void HistogramWidget::setHistogram(const Processing::Algorithms::Histogram &histogram) {
    m_histogram = histogram;
}
