#include "translator.h"

using namespace UI::Utils;

Translator::Translator(Core::Settings::SettingsMgr *settingsMgr, QObject *parent)
    : QObject{parent}, m_settingsMgr{settingsMgr} {
    connect(m_settingsMgr, &Core::Settings::SettingsMgr::langChanged, this, &Translator::updateLanguage);
}

void Translator::updateLanguage() {
    QString lang = m_settingsMgr->getLang();

    qApp->removeTranslator(&m_translator);

    if(lang == "system") {
        if(m_translator.load(QLocale::system(), "ImgConv", "_", ":/translations")) {
            qApp->installTranslator(&m_translator);
        }
    } else if(lang != "default") {
        if(m_translator.load("ImgConv_" + lang, ":/translations/")) {
            qApp->installTranslator(&m_translator);
        }
    } else {
        bool ok = m_translator.load("", "");
        Q_UNUSED(ok)

        qApp->installTranslator(&m_translator);
    }
}


QStringList Translator::listLanguages() {
    QStringList list;

    QDirIterator it(":translations", QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString file = it.next();

        file.truncate(file.lastIndexOf('.'));
        file.remove(0, file.lastIndexOf('_') + 1);

        list.append(file);
    }

    return list;
}
