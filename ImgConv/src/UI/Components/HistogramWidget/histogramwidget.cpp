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

HistogramWidget::HistogramWidget(const QString &title, QWidget *parent)
    : QWidget{parent} {

    setMaximumHeight(300);
    setMinimumWidth(200);

    setMouseTracking(true);

    setTitle(title);
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
    poly << (rect().bottomLeft() - QPoint(0, bottomMargin()));

    for(qsizetype i = 0; i < m_histogram.r.size(); i ++) {
        poly << QPoint(val2X(i), val2Y(v[i], max));
    }

    poly << (rect().bottomRight() - QPoint(0, bottomMargin()));

    p.drawPolygon(poly);
}

void HistogramWidget::plotCursor(QPainter &p, size_t max) {
    p.setPen(QPen(Qt::black, 1));
    p.setBrush(QColor(100, 100, 100, 100));

    size_t curVal = X2Val(m_mousePos.x());
    int curX = val2X(curVal);

    p.drawLine(curX, 0, curX, plottingHeight());

    p.setPen(QPen(QColor(100, 0, 0), 1));
    p.drawEllipse(QPoint(curX, val2Y(m_histogram.r[curVal], max)), 5, 5);
    p.setPen(QPen(QColor(0, 100, 0), 1));
    p.drawEllipse(QPoint(curX, val2Y(m_histogram.g[curVal], max)), 5, 5);
    p.setPen(QPen(QColor(0, 0, 100), 1));
    p.drawEllipse(QPoint(curX, val2Y(m_histogram.b[curVal], max)), 5, 5);

    drawCursorValues(p);
}

void HistogramWidget::drawCursorValues(QPainter &p) {
    size_t curVal = X2Val(m_mousePos.x());

    p.setPen(QPen(Qt::black, 1));
    p.drawText(QPoint(5, height() - 5), tr("X : %1 R : %2 G : %3 B : %4")
                                    .arg(curVal)
                                    .arg(m_histogram.r[curVal])
                                    .arg(m_histogram.g[curVal])
                                    .arg(m_histogram.b[curVal]));
}

void HistogramWidget::drawTitle(QPainter &p) {
    QFontMetrics fm(p.font());
    int textW = fm.horizontalAdvance(title());

    p.setPen(QPen(Qt::black, 1));
    p.drawText(QPoint(width() / 2 - textW / 2, height() - 5), title());
}

int HistogramWidget::bottomMargin() {
    return 20;
}

int HistogramWidget::plottingHeight() {
    return height() - bottomMargin();
}

int HistogramWidget::val2Y(size_t val, size_t max) {
    return plottingHeight() - val / (float)max * (plottingHeight() - 5);
}

int HistogramWidget::val2X(size_t val) {
    return val / 256.f * width();
}

size_t HistogramWidget::X2Val(int X) {
    return X / (float)width() * 256.f;
}

QString HistogramWidget::title() const {
    return m_title;
}

void HistogramWidget::setTitle(const QString &title) {
    m_title = title;

    update();
}

void HistogramWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(QPen(Qt::black, 2));
    p.setBrush(QColor(200, 200, 200, 128));

    p.drawRect(rect());
    p.drawLine(0, plottingHeight(), width(), plottingHeight());

    if(m_histogram.r.isEmpty() || m_histogram.g.isEmpty() || m_histogram.b.isEmpty()) {
        drawTitle(p);
        return;
    }

    size_t max = qMax(m_RGBmax[0], qMax(m_RGBmax[1], m_RGBmax[2]));

    plot(p, m_histogram.r, max, QColor(180, 0, 0, 200), QColor(180, 0, 0, 150));
    plot(p, m_histogram.g, max, QColor(0, 180, 0, 200), QColor(0, 180, 0, 150));
    plot(p, m_histogram.b, max, QColor(0, 0, 180, 200), QColor(0, 0, 180, 150));

    if(m_mouseIn) {
        plotCursor(p, max);
    } else {
        drawTitle(p);
    }
}

void HistogramWidget::mouseMoveEvent(QMouseEvent *event) {
    m_mousePos = event->pos();

    update();
}

void HistogramWidget::enterEvent(QEnterEvent *event) {
    Q_UNUSED(event);

    m_mouseIn = true;

    update();
}

void HistogramWidget::leaveEvent(QEvent *event) {
    Q_UNUSED(event);

    m_mouseIn = false;

    update();
}
