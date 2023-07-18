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
    } else {
        bool ok = translator->load("", "");
        Q_UNUSED(ok)

        app->installTranslator(translator);
    }
}

QStringList listLanguages() {
    QStringList list;

    QDirIterator it(":translations", QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString file = it.next();

        file = file.split("_")[1];
        file = file.split(".")[0];

        list.append(file);
    }

    return list;
}

}
