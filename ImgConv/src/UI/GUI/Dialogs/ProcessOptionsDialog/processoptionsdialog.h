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


#ifndef PROCESSOPTIONSDIALOG_H
#define PROCESSOPTIONSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QComboBox>

#include <QFormLayout>

#include "Core/Settings/SettingsMgr/settingsmgr.h"
#include "Core/Processing/processing.h"
#include "UI/GUI/Components/ButtonColorPicker/buttoncolorpicker.h"
#include "UI/GUI/Components/FilenamePicker/filenamepicker.h"
#include "UI/GUI/UtilsGUI/utilsgui.h"

namespace UI::GUI::Dialogs {
class ProcessOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    ProcessOptionsDialog(Core::Settings::SettingsMgr *settingsMgr, Core::Processing::Options *options, QWidget *parent = nullptr);

private slots:
    void boundModeSelectionChanged(int index);

private:
    QFormLayout *m_layout;

    QDialogButtonBox *mw_buttonBox;

    QSpinBox *mw_chunkFactor;
    QComboBox *mw_boundModeSelection;
    Components::ButtonColorPicker *mw_buttonColorPicker;
    Components::FilenamePicker *mw_userIncludePathPicker;

private:
    Core::Processing::Options *m_options = nullptr;
};
}

#endif // PROCESSOPTIONSDIALOG_H
