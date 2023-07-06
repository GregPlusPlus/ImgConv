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

WaitDialog::WaitDialog(const QString &text, int flags)
    : QDialog{}, m_flags{flags} {

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint |
                   Qt::WindowTitleHint | Qt::Tool |
                   Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    setWindowTitle(tr("Work in progress"));
    setWindowIcon(QIcon(":/icons/hourglass.png"));

    m_layout = new QGridLayout;

    mw_spinnerLabel = new QLabel(this);
    mw_textLabel = new QLabel(this);

    m_layout->addWidget(mw_spinnerLabel, 0, 0);

    QMovie *mv = new QMovie(":/icons/spinner.gif", "gif", this);
    mv->setScaledSize(QSize(30, 30));
    mv->start();
    mw_spinnerLabel->setMovie(mv);

    m_layout->addWidget(mw_textLabel, 0, 1);

    mw_cancelButton = new QPushButton(QIcon(":/icons/control-stop-square-red.png"), QString(), this);
    mw_cancelButton->setToolTip(tr("Cancel process"));
    mw_cancelButton->setFlat(true);
    mw_cancelButton->hide();

    mw_progressBar = new QProgressBar(this);
    mw_progressBar->setRange(0, 100);
    mw_progressBar->setValue(0);
    mw_progressBar->hide();

    connect(mw_cancelButton, &QPushButton::clicked, this, &WaitDialog::cancelProcess);

    if(m_flags & Flags::ShowProgress) {
        mw_progressBar->show();

        if(m_flags & Flags::Cancelable) {
            mw_cancelButton->show();

            m_layout->addWidget(mw_cancelButton, 1, 0, 1, 1);
            m_layout->addWidget(mw_progressBar, 1, 1, 1, 1);
        } else {
            m_layout->addWidget(mw_progressBar, 1, 0, 1, 2);
        }
    } else {
        if(m_flags & Flags::Cancelable) {
            mw_cancelButton->show();

            m_layout->addWidget(mw_cancelButton, 0, 2);
        }
    }

    setText(text);

    setLayout(m_layout);
}

QString WaitDialog::text() const {
    return mw_textLabel->text();
}

void WaitDialog::setText(const QString &text) {
    mw_textLabel->setText(text);
}

void WaitDialog::updateProgress(size_t percentage) {
    mw_progressBar->setValue(percentage);
}

void WaitDialog::cancelProgressPending() {
    mw_cancelButton->setEnabled(false);
    mw_cancelButton->setToolTip(tr("Canceling process..."));
}
