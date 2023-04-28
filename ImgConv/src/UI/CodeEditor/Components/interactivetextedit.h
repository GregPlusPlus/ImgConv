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

#ifndef INTERACTIVETEXTEDIT_H
#define INTERACTIVETEXTEDIT_H

#include <QPlainTextEdit>
#include <QWidget>

#include <QRegularExpression>
#include <QStringLiteral>

#include "keycompletion.h"

class KeyCompletion;

class InteractiveTextEdit : public QPlainTextEdit {
    Q_OBJECT
public:
    InteractiveTextEdit(QWidget *parent = nullptr);

    bool useSpacesAsTab() const;
    void setUseSpacesAsTab(bool newUseSpaceForTab);

    qsizetype tabSpaceCount() const;
    void setTabSpaceCount(qsizetype newTabSpaceCount);

    int getIndentationLevel(qsizetype index);
    int getCursorIndentationLevel();
    char charBeforeCursor();
    char charAfterCursor();
    QString charAroundCursor();
    void removeCharAroundCursor();
    void unindentLine();
    bool isBetweenMatchingChars(qsizetype index, char opening, char closing, char escape);
    bool isBetweenDblQuotes(qsizetype index);
    bool isBetweenQuotes(qsizetype index);

    QString buildTabs(int level);

    KeyCompletion *keyCompletion() const;
    void setKeyCompletion(KeyCompletion *newKeyCompletion);

    static bool isWhiteSpace(const QString &str);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    KeyCompletion *m_keyCompletion = nullptr;

    qsizetype m_useSpacesAsTab = false;
    quint8 m_tabSpaceCount = 4;
};

#endif // INTERACTIVETEXTEDIT_H
