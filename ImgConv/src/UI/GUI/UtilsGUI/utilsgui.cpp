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

#include "utilsgui.h"

// FROM : https://stackoverflow.com/questions/42607554/show-shortcut-in-tooltip-of-qtoolbar

namespace UI::GUI::Utils {
/* guesses a descriptive text from a text suited for a menu entry
   This is equivalent to QActions internal qt_strippedText()
*/
QString strippedActionText(QString s) {
    s.remove( QString::fromLatin1("...") );
    for (int i = 0; i < s.size(); ++i) {
        if (s.at(i) == QLatin1Char('&'))
            s.remove(i, 1);
    }
    return s.trimmed();
}


/* Adds possible shortcut information to the tooltip of the action.
   This provides consistent behavior both with default and custom tooltips
   when used in combination with removeShortcutToToolTip()
*/
void addShortcutToToolTip(QAction *action) {
    if (!action->shortcut().isEmpty()) {
        QString tooltip = action->property("tooltipBackup").toString();
        if (tooltip.isEmpty()) {
            tooltip = action->toolTip();
            if (tooltip != strippedActionText(action->text())) {
                action->setProperty("tooltipBackup", action->toolTip());  // action uses a custom tooltip. Backup so that we can restore it later.
            }
        }
        QColor shortcutTextColor = QApplication::palette().color(QPalette::ToolTipText);
        QString shortCutTextColorName;
        if (shortcutTextColor.value() == 0) {
            shortCutTextColorName = "gray";  // special handling for black because lighter() does not work there [QTBUG-9343].
        } else {
            int factor = (shortcutTextColor.value() < 128) ? 150 : 50;
            shortCutTextColorName = shortcutTextColor.lighter(factor).name();
        }
        action->setToolTip(QString("<p style='white-space:pre'>%1&nbsp;&nbsp;<code style='color:%2; font-size:small'>%3</code></p>")
                           .arg(tooltip, shortCutTextColorName, action->shortcut().toString(QKeySequence::NativeText)));
    }
}


/* Removes possible shortcut information from the tooltip of the action.
   This provides consistent behavior both with default and custom tooltips
   when used in combination with addShortcutToToolTip()
*/
void removeShortcutFromToolTip(QAction *action) {
    action->setToolTip(action->property("tooltipBackup").toString());
    action->setProperty("tooltipBackup", QVariant());
}

void showAboutDialog(QWidget *parent) {
    QString str = QObject::tr ("<h1>%1</h1> " \
                               "[Rev. %2]<br>" \
                               "Built with <a href=\"https://qt.io/\">Qt</a> version %3, runtime : %4<br><br>" \
                               "Some icons are provided under a " \
                               "<a href='https://creativecommons.org/licenses/by/3.0/'>Creative Commons Attribution 3.0 License</a> " \
                               "by Yusuke Kamiyamane <a href='https://p.yusukekamiyamane.com/'>(Fugue Icons)</a>.<br><br>"\
                               "%5"\
                               "<hr>%6").arg(APP_NAME,
                                             GIT_VERSION,
                                             QT_VERSION_STR,
                                             qVersion(),
                                             COPYRIGHT,
                                             LGPL_STR);

    QMessageBox *about = new QMessageBox(parent);
    about->setWindowTitle(QObject::tr("About %1...").arg(APP_NAME));
    about->setIconPixmap(QPixmap(":/icons/icon.png"));
    about->setText(str);
    about->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse | Qt::LinksAccessibleByKeyboard);
    about->setStandardButtons(QMessageBox::Close);
    about->setDefaultButton(QMessageBox::Close);

    QFile gpl(":/licenses/COPYING.txt");
    QFile lgpl(":/licenses/COPYING.LESSER.txt");
    QFile CCBY30(":/licenses/CC30.txt");

    if(gpl.open(QIODevice::ReadOnly)){about->setDetailedText(about->detailedText() + gpl.readAll() + "\n\n");}
    if(lgpl.open(QIODevice::ReadOnly)){about->setDetailedText(about->detailedText() + lgpl.readAll() + "\n\n");}
    if(CCBY30.open(QIODevice::ReadOnly)){about->setDetailedText(about->detailedText() + CCBY30.readAll() + "\n\n");}

    about->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    about->exec();
}

}
