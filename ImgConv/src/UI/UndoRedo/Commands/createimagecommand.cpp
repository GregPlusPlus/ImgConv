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

#include "createimagecommand.h"

using namespace UndoRedo::Commands;

CreateImageCommand::CreateImageCommand(Core::App *coreApp, UI::GUI::Dialogs::CreateImageDialog::ImageSettings_t settings, QUndoCommand *parent)
    : QUndoCommand(parent), m_coreApp(coreApp) {

    QImage img(settings.width, settings.height, QImage::Format_RGB888);
    img.fill(settings.fillColor);

    m_newImage = img;
    m_previousImage = m_coreApp->originalImage();

    m_coreApp->logInfo(QObject::tr("Created image of size %1x%2.").arg(settings.width).arg(settings.height));

    setText(QObject::tr("Create %1x%2 image").arg(settings.width).arg(settings.height));
}

void CreateImageCommand::undo() {
    m_coreApp->setOriginalImage(m_previousImage);
}

void CreateImageCommand::redo() {
    m_coreApp->setOriginalImage(m_newImage);
}
