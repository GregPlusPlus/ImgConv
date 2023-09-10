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

#include "openimagecommand.h"

using namespace UndoRedo::Commands;

OpenImageCommand::OpenImageCommand(Core::App *coreApp, const QImage &newImage, const QString &fileName, QUndoCommand *parent)
    : QUndoCommand(parent), m_coreApp(coreApp) {

    m_newImage = newImage;
    m_previousImage = m_coreApp->originalImage();

    setText(QObject::tr("Open image %1").arg(QFileInfo(fileName).fileName()));
}

void OpenImageCommand::undo() {
    m_coreApp->setOriginalImage(m_previousImage);
}

void OpenImageCommand::redo() {
    m_coreApp->setOriginalImage(m_newImage);
}
