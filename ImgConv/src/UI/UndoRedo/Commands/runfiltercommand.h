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

#ifndef RUNFILTERCOMMAND_H
#define RUNFILTERCOMMAND_H

#include <QUndoCommand>

#include <QList>
#include <QUuid>

#include "Core/App/app.h"
#include "Core/Processing/convkernel.h"
#include "Core/Processing/convkernelsetting.h"

namespace UndoRedo::Commands {
class RunFilterCommand : public QObject, public QUndoCommand {
    Q_OBJECT
public:
    explicit RunFilterCommand(Core::App *coreApp, Core::Processing::ConvKernels::ConvKernel *convKernel, QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

signals:
    void processStarted(const QUuid &pid);
    void restoreConvKernel(Core::Processing::ConvKernels::ConvKernel *convKernel);

private:
    void saveSettings();
    void restoreSettings();

private:
    Core::App *m_coreApp;
    Core::Processing::ConvKernels::ConvKernel *m_convKernel;
    QList<Core::Processing::ConvKernelSetting::Data> m_settings;

    QImage m_previousProcessedImage;
};
}

#endif // RUNFILTERCOMMAND_H
