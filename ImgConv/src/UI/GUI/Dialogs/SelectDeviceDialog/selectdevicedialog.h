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

#ifndef SELECTDEVICEDIALOG_H
#define SELECTDEVICEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QList>
#include <QLabel>

#include "Core/OCLWrapper/oclwrapper.h"

namespace UI::GUI::Dialogs {
class SelectDeviceDialog : public QDialog
{
    Q_OBJECT
public:
    SelectDeviceDialog(QList<Core::OCLWrapper::Device> devices);

    Core::OCLWrapper::Device getDevice();

signals:
    void listOpenCLDevices();

private:
    QFormLayout *m_layout;
    QDialogButtonBox *mw_buttonBox;
    QComboBox *mw_combo;
    QLabel *mw_linkLabel;

private:
    QList<Core::OCLWrapper::Device> m_devices;
};
}

#endif // SELECTDEVICEDIALOG_H
