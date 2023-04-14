#ifndef UTILSUI_H
#define UTILSUI_H

#include <QApplication>
#include <QAction>
#include <QToolTip>

namespace UtilsUI {
    QString strippedActionText(QString s);
    void addShortcutToToolTip(QAction *action);
}

#endif // UTILSUI_H
