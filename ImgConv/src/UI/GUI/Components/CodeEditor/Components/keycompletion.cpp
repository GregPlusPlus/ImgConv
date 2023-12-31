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

#include "keycompletion.h"

using namespace UI::GUI::Components::CodeEditorComponents;

KeyCompletion::KeyCompletion(InteractiveTextEdit *parent)
    : QObject{parent}, mw_textEdit{parent} {

    mw_textEdit->setKeyCompletion(this);
}

void KeyCompletion::buildBrackets() {
    int indentLvl = mw_textEdit->getCursorIndentationLevel();

    mw_textEdit->insertPlainText(QString("{\n%1\n%2}")
                                .arg(mw_textEdit->buildTabs(indentLvl + 1),
                                     mw_textEdit->buildTabs(indentLvl)));
    mw_textEdit->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    mw_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
}

bool KeyCompletion::autocomplete(QKeyEvent *e) {
    QString selectedText = mw_textEdit->textCursor().selection().toPlainText();

    if(mw_textEdit->isBetweenDblQuotes(mw_textEdit->textCursor().position()) ||
        mw_textEdit->isBetweenQuotes(mw_textEdit->textCursor().position())) {
        return autocompleteInQuotes(e);
    } else if(selectedText.isEmpty()) {
        return autocompleteNotSelected(e);
    } else {
        return autocompleteSelected(e, selectedText);
    }
}

bool KeyCompletion::autocompleteInQuotes(QKeyEvent *e) {
    int key = e->key();

    if(key == Qt::Key_Tab) {
        if(mw_textEdit->useSpacesAsTab()) {
            mw_textEdit->insertPlainText(mw_textEdit->buildTabs(1));
        } else {
            return false;
        }
    } else if(key == Qt::Key_Backspace) {
        QString quotes;

        if(mw_textEdit->textCursor().position() > 2) {
            if(mw_textEdit->toPlainText().at(mw_textEdit->textCursor().position() - 2) == '\\') {
                return false;
            }
        }

        if(mw_textEdit->isBetweenDblQuotes(mw_textEdit->textCursor().position())) {
            quotes = "\"\"";
        } else if(mw_textEdit->isBetweenQuotes(mw_textEdit->textCursor().position())) {
            quotes = "''";
        }

        if(mw_textEdit->charAroundCursor() == quotes) {
            mw_textEdit->removeCharAroundCursor();
        } else {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

bool KeyCompletion::autocompleteNotSelected(QKeyEvent *e) {
    int key = e->key();

    if(key == Qt::Key_Return) {
        if((e->modifiers() & Qt::ControlModifier) && (e->modifiers() & Qt::ShiftModifier)) {
            int l = mw_textEdit->getCursorIndentationLevel();
            mw_textEdit->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
            mw_textEdit->insertPlainText(mw_textEdit->buildTabs(l) + "\n");
            mw_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
        } else {
            mw_textEdit->insertPlainText("\n" + mw_textEdit->buildTabs(mw_textEdit->getCursorIndentationLevel()));
        }
    } else if(key == Qt::Key_Tab) {
        if(mw_textEdit->useSpacesAsTab()) {
            mw_textEdit->insertPlainText(mw_textEdit->buildTabs(1));
        } else {
            return false;
        }
    } else if(key == Qt::Key_Backtab) {
        int l = mw_textEdit->getCursorIndentationLevel();

        if(l > 0) {
            mw_textEdit->unindentLine();
            mw_textEdit->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
            mw_textEdit->insertPlainText(mw_textEdit->buildTabs(l - 1));
        }
    } else if(key == Qt::Key_BraceLeft) {
        buildBrackets();
    } else if(key == Qt::Key_BraceRight) {
        if(mw_textEdit->charAfterCursor() == '}') {
            mw_textEdit->moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    }  else if(key == Qt::Key_ParenLeft) {
        mw_textEdit->insertPlainText("()");
        mw_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
    } else if(key == Qt::Key_ParenRight) {
        if(mw_textEdit->charAfterCursor() == ')') {
            mw_textEdit->moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_BracketLeft) {
        mw_textEdit->insertPlainText("[]");
        mw_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
    } else if(key == Qt::Key_BracketRight) {
        if(mw_textEdit->charAfterCursor() == ']') {
            mw_textEdit->moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_QuoteDbl) {
        if(mw_textEdit->charAfterCursor() == '"' && mw_textEdit->charBeforeCursor() != '\\') {
            mw_textEdit->moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else if(mw_textEdit->charBeforeCursor() != '\\') {
            mw_textEdit->insertPlainText("\"\"");
            mw_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_Apostrophe) {
        if(mw_textEdit->charAfterCursor() == '\'' && mw_textEdit->charBeforeCursor() != '\\') {
            mw_textEdit->moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else if(mw_textEdit->charBeforeCursor() != '\\') {
            mw_textEdit->insertPlainText("''");
            mw_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_Backspace) {
        if(mw_textEdit->textCursor().position() > 0) {
            if(mw_textEdit->isBetweenDblQuotes(mw_textEdit->textCursor().position() - 1) ||
                    mw_textEdit->isBetweenQuotes(mw_textEdit->textCursor().position() - 1)) {
                return false;
            }
        }

        QList<QString> charCouples;
        charCouples.append("{}");
        charCouples.append("()");
        charCouples.append("[]");
        charCouples.append("\"\"");
        charCouples.append("''");

        if(charCouples.contains(mw_textEdit->charAroundCursor())) {
            mw_textEdit->removeCharAroundCursor();
        } else {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

bool KeyCompletion::autocompleteSelected(QKeyEvent *e, const QString &selectedText) {
    int key = e->key();

    if(key == Qt::Key_ParenLeft) {
        mw_textEdit->insertPlainText(QString("(%1)").arg(selectedText));
    } else if(key == Qt::Key_BraceLeft) {
        QString s = selectedText;
        int l = mw_textEdit->getCursorIndentationLevel() + 1;
        QString contents = s.replace("\n", "\n" + mw_textEdit->buildTabs(l)).trimmed();

        buildBrackets();
        mw_textEdit->insertPlainText(contents);
    } else if(key == Qt::Key_BracketLeft) {
        mw_textEdit->insertPlainText(QString("[%1]").arg(selectedText));
    } else if(key == Qt::Key_QuoteDbl) {
        mw_textEdit->insertPlainText(QString("\"%1\"").arg(selectedText));
    } else if(key == Qt::Key_Apostrophe) {
        mw_textEdit->insertPlainText(QString("'%1'").arg(selectedText));
    } else {
        return false;
    }

    return true;
}
