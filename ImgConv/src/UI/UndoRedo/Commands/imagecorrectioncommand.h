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

#ifndef IMAGECORRECTIONCOMMAND_H
#define IMAGECORRECTIONCOMMAND_H

#include <QUndoCommand>

#include "Core/App/app.h"

namespace UndoRedo::Commands {
class ImageCorrectionCommand : public QObject, public QUndoCommand{
    Q_OBJECT

public:
    ImageCorrectionCommand(Core::App *coreApp,
                           const QString &kernelPath,
                           const QString &name,
                           const Core::Processing::Algorithms::Histogram &hist,
                           QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

signals:
    void processStarted(const QUuid &pid);

private:
    Core::App *m_coreApp;
    Core::Processing::Algorithms::Histogram m_histogram;

    QString m_kernelPath;

    QImage m_previousProcessedImage;
};
}

#endif // IMAGECORRECTIONCOMMAND_H
