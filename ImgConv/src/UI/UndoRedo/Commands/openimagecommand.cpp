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
