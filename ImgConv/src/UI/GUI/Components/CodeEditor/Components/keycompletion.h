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

#ifndef KEYCOMPLETION_H
#define KEYCOMPLETION_H

#include <QTextDocumentFragment>

#include "interactivetextedit.h"

namespace UI::GUI::Components::CodeEditorComponents {
class InteractiveTextEdit;

class KeyCompletion : public QObject {
    Q_OBJECT

public:
    explicit KeyCompletion(InteractiveTextEdit *parent = nullptr);

    bool autocomplete(QKeyEvent *e);

signals:

private:
    bool autocompleteInQuotes(QKeyEvent *e);
    bool autocompleteNotSelected(QKeyEvent *e);
    bool autocompleteSelected(QKeyEvent *e, const QString &selectedText);
    void buildBrackets();

private:
    InteractiveTextEdit *mw_textEdit;
};
}

#endif // KEYCOMPLETION_H
