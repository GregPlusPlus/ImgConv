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

#include "runfiltercommand.h"

using namespace UndoRedo::Commands;

RunFilterCommand::RunFilterCommand(Core::App *coreApp, Core::Processing::ConvKernels::ConvKernel *convKernel, QUndoCommand *parent)
    : QObject(), QUndoCommand(parent), m_coreApp(coreApp), m_convKernel(convKernel) {

    saveSettings();
    m_previousProcessedImage = m_coreApp->processedImage();

    setText(QObject::tr("Run filter %1").arg(convKernel->getName()));
}

void RunFilterCommand::undo() {
    m_coreApp->setProcessedImage(m_previousProcessedImage);
}

void RunFilterCommand::redo() {
    restoreSettings();
    emit processStarted(m_coreApp->startConv2DProcess(m_convKernel));
}

void RunFilterCommand::saveSettings() {
    QList<Core::Processing::ConvKernelSetting*> settings = m_convKernel->settings();

    for(Core::Processing::ConvKernelSetting *s : settings) {
        m_settings.append(s->data());
    }
}

void RunFilterCommand::restoreSettings() {
    for(const Core::Processing::ConvKernelSetting::Data &d : m_settings) {
        m_convKernel->getSettingByName(d.name)->setData(d);
    }

    emit restoreConvKernel(m_convKernel);
}
