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

#include "filenamepicker.h"

using namespace UI::GUI;

FileNamePicker::FileNamePicker(const QString &title, const QString &filters, QWidget *parent)
    : QWidget{parent} {
    setContentsMargins(0, 0, 0, 0);

    m_layout = new QHBoxLayout;
    m_layout->setSpacing(0);

    mw_fileName = new QLineEdit(this);
    connect(mw_fileName, &QLineEdit::textChanged, this, &FileNamePicker::fileNameChanged);

    mw_browse = new QPushButton(tr("..."), this);
    mw_browse->setMaximumWidth(40);
    connect(mw_browse, &QPushButton::clicked, this, [=]() {
        QString fn = QFileDialog::getOpenFileName(this, title, QString(), filters);
        if(!fn.isEmpty()) {
            setFileName(fn);
        }
    });

    m_layout->addWidget(mw_fileName);
    m_layout->addWidget(mw_browse);

    setLayout(m_layout);
}

QString FileNamePicker::getFileName() const {
    return mw_fileName->text();
}

void FileNamePicker::setFileName(const QString &fn) {
    mw_fileName->setText(fn);
}
