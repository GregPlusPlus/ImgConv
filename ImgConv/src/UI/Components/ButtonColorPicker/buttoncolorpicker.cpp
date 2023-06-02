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

#include "buttoncolorpicker.h"

using namespace UI::Components;

ButtonColorPicker::ButtonColorPicker(QColor defaultColor, QWidget *parent)
    : QPushButton{parent} {
    setText(tr("Pick color"));

    updateColor(QColor(defaultColor));

    connect(this, &QPushButton::clicked, this, [=]() {
        QColor color = QColorDialog::getColor(defaultColor, this);

        if(color.isValid()) {
            updateColor(color);
        }
    });
}

void ButtonColorPicker::updateColor(const QColor &color) {
    m_selectedColor = color;

    setIcon(makeIcon(color));

    emit colorSelected(color);
}

QIcon ButtonColorPicker::makeIcon(const QColor &color) {
    QPixmap pix(height() * 0.66, height() * 0.66);

    QPainter p(&pix);
    p.setBrush(color);
    p.setPen(QPen(Qt::black, 1));

    p.drawRect(0, 0, pix.width() - 1, pix.height() - 1);

    return QIcon(pix);
}

QColor ButtonColorPicker::selectedColor() const {
    return m_selectedColor;
}
