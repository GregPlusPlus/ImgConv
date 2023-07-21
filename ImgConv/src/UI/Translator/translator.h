#ifndef UI_UTILS_TRANSLATOR_H
#define UI_UTILS_TRANSLATOR_H

#include <QApplication>
#include <QTranslator>
#include <QDirIterator>

#include "Core/Settings/SettingsMgr/settingsmgr.h"

namespace UI::Utils {

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(Core::Settings::SettingsMgr *settingsMgr, QObject *parent = nullptr);

    static QStringList listLanguages();

public slots:
    void updateLanguage();

signals:

private:
    Core::Settings::SettingsMgr *m_settingsMgr;
    QTranslator m_translator;

};

}

#endif // UI_UTILS_TRANSLATOR_H
