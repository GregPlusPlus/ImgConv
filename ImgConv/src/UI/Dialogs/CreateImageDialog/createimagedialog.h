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

#ifndef CREATEIMAGEDIALOG_H
#define CREATEIMAGEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>

#include <QFormLayout>

#include <QIntValidator>

#include "UI/Components/ButtonColorPicker/buttoncolorpicker.h"

namespace UI::Dialogs {
class CreateImageDialog : public QDialog
{
    Q_OBJECT

public:
    struct ImageSettings_t {
        int width;
        int height;
        QColor fillColor;
    };

public:
    CreateImageDialog(QWidget *parent = nullptr);

    ImageSettings_t getImageSettings() const;

public slots:

private:
    QFormLayout *m_layout;

    QDialogButtonBox *mw_buttonBox;

    QLineEdit *mw_inputW;
    QLineEdit *mw_inputH;
    Components::ButtonColorPicker*mw_buttonColorPicker;

};
}

#endif // CREATEIMAGEDIALOG_H
