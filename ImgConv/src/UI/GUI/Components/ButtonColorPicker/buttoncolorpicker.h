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

#ifndef BUTTONCOLORPICKER_H
#define BUTTONCOLORPICKER_H

#include <QPushButton>

#include <QColorDialog>

#include <QPixmap>
#include <QPainter>

namespace UI::GUI::Components {
class ButtonColorPicker : public QPushButton {
    Q_OBJECT

public:
    ButtonColorPicker(QColor defaultColor = Qt::white, QWidget *parent = nullptr);

    QColor selectedColor() const;

signals:
    void colorSelected(const QColor &color);

private:
    void updateColor(const QColor &color);
    QIcon makeIcon(const QColor &color);

private:
    QColor m_selectedColor;
};
}

#endif // BUTTONCOLORPICKER_H
