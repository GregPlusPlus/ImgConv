#ifndef UTILSUI_H
#define UTILSUI_H

#include "Core/Settings/SettingsMgr/settingsmgr.h"

#include <QApplication>
#include <QTranslator>
#include <QDirIterator>

namespace UI::Utils
{
    void setLanguage(QTranslator *translator, Core::Settings::SettingsMgr *settingsMgr, QApplication *app);
    QStringList listLanguages();
}

#endif // UTILSUI_H
