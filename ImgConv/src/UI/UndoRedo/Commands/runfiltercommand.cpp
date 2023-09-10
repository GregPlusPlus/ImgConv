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
    : QObject(), QUndoCommand(parent), m_coreApp(coreApp) {

    m_previousProcessedImage = m_coreApp->processedImage();
    m_previousConvKernelState = m_coreApp->lastConvKernelState();
    m_newConvKernelState.setConvKernel(convKernel);
    m_newConvKernelState.saveSettings();

    setText(QObject::tr("Run %1 filter").arg(convKernel->getName()));
}

void RunFilterCommand::undo() {
    if(m_previousProcessedImage.isNull()) {
        m_coreApp->setOriginalImage(m_coreApp->originalImage());
    } else {
        m_coreApp->setProcessedImage(m_previousProcessedImage);
    }
    m_previousConvKernelState.restoreSettings();
    emit restoreConvKernel(m_previousConvKernelState.getConvKernel());
}

void RunFilterCommand::redo() {
    m_newConvKernelState.restoreSettings();
    emit restoreConvKernel(m_newConvKernelState.getConvKernel());
    emit processStarted(m_coreApp->startConv2DProcess(m_newConvKernelState.getConvKernel()));
}
