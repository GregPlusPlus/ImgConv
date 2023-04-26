#ifndef BUTTONCOLORPICKER_H
#define BUTTONCOLORPICKER_H

#include <QPushButton>

#include <QColorDialog>

#include <QPixmap>
#include <QPainter>

class ButtonColorPicker : public QPushButton
{
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

#endif // BUTTONCOLORPICKER_H
