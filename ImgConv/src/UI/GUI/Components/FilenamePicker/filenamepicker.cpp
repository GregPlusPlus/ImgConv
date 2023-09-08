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

using namespace UI::GUI::Components;

FilenamePicker::FilenamePicker(const QString &title, const QString &filters, Mode mode, QWidget *parent)
    : QWidget{parent} {
    setContentsMargins(0, 0, 0, 0);

    m_layout = new QHBoxLayout;
    m_layout->setSpacing(0);

    mw_fileName = new QLineEdit(this);
    connect(mw_fileName, &QLineEdit::textChanged, this, &FilenamePicker::fileNameChanged);

    mw_browse = new QPushButton(tr("..."), this);
    mw_browse->setMaximumWidth(40);
    connect(mw_browse, &QPushButton::clicked, this, [=]() {
        QString fn;

        switch (mode) {
        case Mode::Files:
            fn = QFileDialog::getOpenFileName(this, title, QString(), filters);
            break;
        case Mode::Directories:
            fn = QFileDialog::getExistingDirectory(this, title,
                                                   QString(),
                                                   QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
            break;
        }

        if(!fn.isEmpty()) {
            setFileName(fn);
        }
    });

    m_layout->addWidget(mw_fileName);
    m_layout->addWidget(mw_browse);

    setLayout(m_layout);
}

QString FilenamePicker::getFileName() const {
    return mw_fileName->text();
}

void FilenamePicker::setFileName(const QString &fn) {
    mw_fileName->setText(fn);

    emit fileNameChanged(fn);
}

void FilenamePicker::setPlaceHolder(const QString &placeholder) {
    mw_fileName->setPlaceholderText(placeholder);
}
