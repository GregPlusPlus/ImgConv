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

#include "waitdialog.h"

using namespace UI::Dialogs;

WaitDialog::WaitDialog(const QString &text) {
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint |
                   Qt::WindowTitleHint | Qt::Tool |
                   Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    setWindowTitle(tr("Work in progress"));
    setWindowIcon(QIcon(":/icons/hourglass.png"));

    m_layout = new QHBoxLayout;

    mw_spinnerLabel = new QLabel(this);
    mw_textLabel = new QLabel(this);

    m_layout->addWidget(mw_spinnerLabel);

    QMovie *mv = new QMovie(":/icons/spinner.gif", "gif", this);
    mv->setScaledSize(QSize(30, 30));
    mv->start();
    mw_spinnerLabel->setMovie(mv);

    m_layout->addWidget(mw_textLabel);

    setText(text);

    setLayout(m_layout);
}

QString WaitDialog::text() const {
    return mw_textLabel->text();
}

void WaitDialog::setText(const QString &text) {
    mw_textLabel->setText(text);
}
