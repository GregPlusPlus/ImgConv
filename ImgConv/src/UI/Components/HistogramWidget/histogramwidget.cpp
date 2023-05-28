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

#include "histogramwidget.h"

HistogramWidget::HistogramWidget(QWidget *parent)
    : QWidget{parent} {

    setMaximumHeight(300);
    setMinimumWidth(200);
}

Processing::Algorithms::Histogram HistogramWidget::histogram() const {
    return m_histogram;
}

void HistogramWidget::setHistogram(const Processing::Algorithms::Histogram &histogram) {
    m_histogram = histogram;

    m_RGBmax = m_histogram.getMax();

    update();
}

void HistogramWidget::plot(QPainter &p, const QVector<size_t> &v, size_t max, const QColor &penColor, const QColor &brushColor) {
    p.setPen(QPen(penColor, 2));
    p.setBrush(brushColor);

    QPolygon poly;
    poly << rect().bottomLeft();

    for(qsizetype i = 0; i < m_histogram.r.size(); i ++) {
        poly << QPoint(i / 256.f * width(), 2 + height() - v[i] / (float)max * height());
    }

    poly << rect().bottomRight();

    p.drawPolygon(poly);
}

void HistogramWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(QPen(Qt::black, 2));
    p.setBrush(Qt::NoBrush);

    p.drawRect(rect());

    if(m_histogram.r.isEmpty() || m_histogram.g.isEmpty() || m_histogram.b.isEmpty()) {
        return;
    }

    size_t max = qMax(m_RGBmax[0], qMax(m_RGBmax[1], m_RGBmax[2]));

    plot(p, m_histogram.r, max, QColor(180, 0, 0, 200), QColor(180, 0, 0, 150));
    plot(p, m_histogram.g, max, QColor(0, 180, 0, 200), QColor(0, 180, 0, 150));
    plot(p, m_histogram.b, max, QColor(0, 0, 180, 200), QColor(0, 0, 180, 150));
}
