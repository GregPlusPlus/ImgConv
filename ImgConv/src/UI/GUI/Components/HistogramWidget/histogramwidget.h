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

#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QWidget>

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPolygon>
#include <QFontMetrics>

#include <QMouseEvent>
#include <QEnterEvent>

#include "src/Core/Processing/processing.h"

namespace UI::GUI::Components {
class HistogramWidget : public QWidget {
    Q_OBJECT

public:
    explicit HistogramWidget(const QString &title, QWidget *parent = nullptr);

    Core::Processing::Algorithms::Histogram histogram() const;

    QString title() const;

public slots:
    void setHistogram(const Core::Processing::Algorithms::Histogram &newHistogram);
    void setTitle(const QString &title);
    void clear();

signals:

private:
    void plot(QPainter &p, const QVector<size_t> &v, size_t max, const QColor &penColor, const QColor &brushColor);
    void plotCursor(QPainter &p, size_t max);
    void drawCursorValues(QPainter &p);
    void drawTitle(QPainter &p);
    void drawDefaultText(QPainter &p);

    int bottomMargin();
    int plottingHeight();
    int val2Y(size_t val, size_t max);
    int val2X(size_t val);
    size_t X2Val(int X);

private:
    Core::Processing::Algorithms::Histogram m_histogram;
    QString m_title;

    QVector<size_t> m_RGBmax;

    bool m_mouseIn;
    QPoint m_mousePos;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
};
}

#endif // HISTOGRAMWIDGET_H
