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

#include "imagecorrectioncommand.h"

UndoRedo::Commands::ImageCorrectionCommand::ImageCorrectionCommand(Core::App *coreApp,
                                                                   const QString &kernelPath,
                                                                   const QString &name,
                                                                   const Core::Processing::Algorithms::Histogram &hist,
                                                                   QUndoCommand *parent)
    : QObject(), QUndoCommand(parent), m_coreApp(coreApp), m_histogram(hist), m_kernelPath(kernelPath) {

    m_previousProcessedImage = m_coreApp->processedImage();

    setText(tr("%1").arg(name));
}

void UndoRedo::Commands::ImageCorrectionCommand::undo() {
    m_coreApp->setProcessedImage(m_previousProcessedImage);
}

void UndoRedo::Commands::ImageCorrectionCommand::redo() {
    emit processStarted(m_coreApp->startImageCorrection(m_kernelPath, m_histogram));
}
