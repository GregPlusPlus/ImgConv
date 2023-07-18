#include "utilsui.h"

namespace UI::Utils {
void setLanguage(QTranslator *translator,
                 Core::Settings::SettingsMgr *settingsMgr,
                 QApplication *app) {
    QString lang = settingsMgr->getLang();

    if(lang == "system") {
        if(translator->load(QLocale::system(), "ImgConv", "_", ":/translations")) {
            app->installTranslator(translator);
        }
    } else if(lang != "default") {
        if(translator->load("ImgConv_" + lang, ":/translations/")) {
            app->installTranslator(translator);
        }
    }
}
}
