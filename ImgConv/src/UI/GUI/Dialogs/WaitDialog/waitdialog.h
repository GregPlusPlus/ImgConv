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

#ifndef WAITDIALOG_H
#define WAITDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

#include <QGridLayout>

#include <QMovie>

namespace UI::GUI::Dialogs {
class WaitDialog : public QDialog
{
public:
    enum Flags {
        None            = 0x00,
        ShowProgress    = 0x01,
        Cancelable      = 0x02
    };

    Q_OBJECT
public:
    WaitDialog(const QString &text, int flags = None);

    QString text() const;

public slots:
    void setText(const QString &text);
    void updateProgress(size_t percentage);
    void cancelProgressPending();

signals:
    void cancelProcess();

private:
    QGridLayout *m_layout;
    QLabel *mw_spinnerLabel;
    QLabel *mw_textLabel;
    QPushButton *mw_cancelButton;
    QProgressBar *mw_progressBar;

private:
    int m_flags;
    QMovie *m_spinner;
};
}

#endif // WAITDIALOG_H
