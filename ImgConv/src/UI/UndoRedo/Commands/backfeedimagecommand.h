#ifndef BACKFEEDIMAGECOMMAND_H
#define BACKFEEDIMAGECOMMAND_H

#include <QUndoCommand>

#include "Core/App/app.h"

namespace UndoRedo::Commands {
class BackfeedImageCommand : public QUndoCommand {
public:
    explicit BackfeedImageCommand(Core::App *coreApp, QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    Core::App *m_coreApp;
    QImage m_newImage;
    QImage m_previousImage;
};
}

#endif // BACKFEEDIMAGECOMMAND_H
