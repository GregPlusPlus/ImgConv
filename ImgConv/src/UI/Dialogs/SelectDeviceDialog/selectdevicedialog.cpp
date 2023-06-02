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

#include "selectdevicedialog.h"

using namespace UI::Dialogs;

SelectDeviceDialog::SelectDeviceDialog(QList<Core::OCLWrapper::Device> devices)
    : m_devices{devices} {
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    setWindowTitle(tr("Select device"));
    setWindowIcon(QIcon(":/icons/graphic-card.png"));

    m_layout = new QFormLayout;

    mw_combo = new QComboBox(this);
    for(const Core::OCLWrapper::Device &d : m_devices) {
        mw_combo->addItem(d.name);
    }

    m_layout->addRow(tr("Device :"), mw_combo);

    mw_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                        QDialogButtonBox::Cancel,
                                        this);

    connect(mw_buttonBox, &QDialogButtonBox::accepted, this, &SelectDeviceDialog::accept);
    connect(mw_buttonBox, &QDialogButtonBox::rejected, this, &SelectDeviceDialog::reject);

    m_layout->addWidget(mw_buttonBox);

    setLayout(m_layout);
}

Core::OCLWrapper::Device SelectDeviceDialog::getDevice() {
    return m_devices.at(mw_combo->currentIndex());
}
