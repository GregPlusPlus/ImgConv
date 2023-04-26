#include "buttoncolorpicker.h"

ButtonColorPicker::ButtonColorPicker(QColor defaultColor, QWidget *parent)
    : QPushButton{parent} {
    setText(tr("Choose color"));

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
