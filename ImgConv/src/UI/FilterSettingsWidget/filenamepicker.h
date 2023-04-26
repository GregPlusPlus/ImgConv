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

#ifndef FILENAMEPICKER_H
#define FILENAMEPICKER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include <QFileDialog>

#include <QHBoxLayout>

class FileNamePicker : public QWidget
{
    Q_OBJECT
public:
    explicit FileNamePicker(const QString &title, const QString &filters, QWidget *parent = nullptr);

    QString getFileName() const;

public slots:
    void setFileName(const QString &fn);

signals:
    void fileNameChanged(const QString &fn);

private:
    QHBoxLayout *m_layout;

    QLineEdit *mw_fileName;
    QPushButton *mw_browse;

};

#endif // FILENAMEPICKER_H
