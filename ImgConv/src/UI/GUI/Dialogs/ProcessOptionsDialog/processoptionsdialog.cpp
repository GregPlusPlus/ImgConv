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

#include "processoptionsdialog.h"

using namespace UI::GUI::Dialogs;

UI::GUI::Dialogs::ProcessOptionsDialog::ProcessOptionsDialog(Core::Processing::Options *options, QWidget *parent)
    : QDialog{parent}, m_options{options} {
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    setWindowTitle(tr("Process options"));
    setWindowIcon(QIcon(":/icons/gear.png"));

    m_layout = new QFormLayout;

    mw_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(mw_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(mw_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    mw_chunkFactor = new QSpinBox(this);
    mw_chunkFactor->setMinimum(1);
    mw_chunkFactor->setMaximum(10);
    mw_chunkFactor->setValue(m_options->chunkFactor);

    connect(mw_chunkFactor, &QSpinBox::valueChanged, this, [this](int val) {
        m_options->chunkFactor = val;
    });

    mw_boundModeSelection = new QComboBox(this);
    mw_boundModeSelection->insertItem(Core::Processing::Options::Fixed_Color,   tr("Fixed color"));
    mw_boundModeSelection->insertItem(Core::Processing::Options::Clamp,         tr("Clamp coordinates"));
    mw_boundModeSelection->insertItem(Core::Processing::Options::Wrap,          tr("Wrap coordinates"));
    mw_boundModeSelection->setCurrentIndex((int)options->boundaryMode);

    connect(mw_boundModeSelection, &QComboBox::currentIndexChanged, this, &ProcessOptionsDialog::boundModeSelectionChanged);

    mw_buttonColorPicker = new Components::ButtonColorPicker(options->fixedColor, this);
    boundModeSelectionChanged(m_options->boundaryMode);

    connect(mw_buttonColorPicker, &Components::ButtonColorPicker::colorSelected, this, [this] (const QColor &color){
        m_options->fixedColor = color;
    });

    m_layout->addRow(tr("Chunk size factor"), mw_chunkFactor);
    m_layout->addRow(tr("Boundary mode"), mw_boundModeSelection);
    m_layout->addRow(tr("Boundary fixed color"), mw_buttonColorPicker);
    m_layout->addWidget(mw_buttonBox);

    setLayout(m_layout);
}

void ProcessOptionsDialog::boundModeSelectionChanged(int index) {
    m_options->boundaryMode = (Core::Processing::Options::BoundaryMode)index;
    mw_buttonColorPicker->setEnabled(m_options->boundaryMode == Core::Processing::Options::Fixed_Color);
}
