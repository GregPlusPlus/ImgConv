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

#include "createimagedialog.h"

using namespace UI::GUI::Dialogs;

CreateImageDialog::CreateImageDialog(QWidget *parent)
    : QDialog{parent} {
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    setWindowTitle(tr("Create image"));
    setWindowIcon(QIcon(":/icons/image-new.png"));

    m_layout = new QFormLayout;

    mw_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(mw_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(mw_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    mw_inputW = new QLineEdit(this);
    mw_inputW->setValidator(new QIntValidator(0, 100E3, this));
    mw_inputW->setFocus();

    mw_inputH = new QLineEdit(this);
    mw_inputH->setValidator(new QIntValidator(0, 100E3, this));

    mw_buttonColorPicker = new Components::ButtonColorPicker(Qt::white, this);

    m_layout->addRow(tr("Width :"), mw_inputW);
    m_layout->addRow(tr("Height :"), mw_inputH);
    m_layout->addRow(tr("Fill color :"), mw_buttonColorPicker);

    m_layout->addWidget(mw_buttonBox);

    setLayout(m_layout);
}

CreateImageDialog::ImageSettings_t CreateImageDialog::getImageSettings() const {
    CreateImageDialog::ImageSettings_t settings;

    settings.width = mw_inputW->text().toInt();
    settings.height = mw_inputH->text().toInt();
    settings.fillColor = mw_buttonColorPicker->selectedColor();

    return settings;
}
