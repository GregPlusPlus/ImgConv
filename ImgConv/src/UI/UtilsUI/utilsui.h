#ifndef UTILSUI_H
#define UTILSUI_H

#include "Core/Settings/SettingsMgr/settingsmgr.h"

#include <QApplication>
#include <QTranslator>

namespace UI::Utils
{
    void setLanguage(QTranslator *translator, Core::Settings::SettingsMgr *settingsMgr, QApplication *app);
}

#endif // UTILSUI_H
