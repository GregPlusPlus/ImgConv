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

#include "interactivetextedit.h"

using namespace UI::CodeEditorComponents;

InteractiveTextEdit::InteractiveTextEdit(QWidget *parent)
    : QPlainTextEdit{parent} {
}

void InteractiveTextEdit::keyPressEvent(QKeyEvent *e) {
    if(m_keyCompletion && !m_keyCompletion->autocomplete(e)) {
        QPlainTextEdit::keyPressEvent(e);
    }
}

KeyCompletion *InteractiveTextEdit::keyCompletion() const {
    return m_keyCompletion;
}

void InteractiveTextEdit::setKeyCompletion(KeyCompletion *newKeyCompletion) {
    m_keyCompletion = newKeyCompletion;
}

bool InteractiveTextEdit::isWhiteSpace(const QString &str) {
     static QRegularExpression whiteSpace (QStringLiteral("\\s+|\x0"));

     return whiteSpace.match(str).hasMatch();
}

QString InteractiveTextEdit::buildTabs(int level) {
    if(useSpacesAsTab()) {
        return QString(" ").repeated(level * tabSpaceCount());
    }

    return QString("\t").repeated(level);
}

char InteractiveTextEdit::charBeforeCursor() {
    char c = 0;

    int pos = textCursor().position() - 1;

    if(pos >= 0 && pos < toPlainText().size()) {
        c = toPlainText().at(pos).toLatin1();
    }

    return c;
}

char InteractiveTextEdit::charAfterCursor() {
    char c = 0;

    int pos = textCursor().position();

    if(pos >= 0 && pos < toPlainText().size()) {
        c = toPlainText().at(pos).toLatin1();
    }

    return c;
}

QString InteractiveTextEdit::charAroundCursor() {
    return QString(charBeforeCursor()) + QString(charAfterCursor());
}

void InteractiveTextEdit::removeCharAroundCursor() {
    moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
    moveCursor(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    moveCursor(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    textCursor().removeSelectedText();
}

void InteractiveTextEdit::unindentLine() {
    int l = getCursorIndentationLevel();

    if(l < 1) {
        return;
    }

    moveCursor(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);

    QString startOfLine = textCursor().selectedText();

    textCursor().insertText(startOfLine.trimmed());
}

bool InteractiveTextEdit::isBetweenMatchingChars(qsizetype index, char opening, char closing, char escape) {
    typedef enum {
        Unknown,
        Opened,
        Closed,
    } State_t;

    State_t state = Unknown;

    bool escaped = false;

    for(qsizetype i = 0; i < index; i ++) {
        char c = toPlainText().at(i).toLatin1();

        if((state == Unknown || state == Closed) &&
            c == opening) {
            state = Opened;
        } else if(state == Opened) {
            if(c == escape) {
                escaped = true;

                continue;
            }

            if(c == closing && !escaped) {
                state = Closed;
            }

            escaped = false;
        }
    }

    if(state != Opened) {
        return false;
    }

    if(index == toPlainText().size()) {
        return false;
    }

    for(qsizetype i = index; i < toPlainText().size(); i ++) {
        if(toPlainText().at(i).toLatin1() == closing) {
            return true;
        }
    }

    return false;
}

bool InteractiveTextEdit::isBetweenDblQuotes(qsizetype index) {
    return isBetweenMatchingChars(index, '"', '"', '\\');
}

bool InteractiveTextEdit::isBetweenQuotes(qsizetype index) {
    return isBetweenMatchingChars(index, '\'', '\'', '\\');
}

int InteractiveTextEdit::getIndentationLevel(qsizetype index) {
    if(toPlainText().isEmpty()) {
        return 0;
    }

    QStringList lines = toPlainText().left(index).split("\n");

    if(lines.count() == 0) {
        return 0;
    }

    QString line = lines.last();

    int spacesCount = 0;

    for(int i = 0; i < line.size(); i ++) {
        if(m_useSpacesAsTab) {
            if(line[i] != ' ') {
                break;
            }
        } else {
            if(line[i] != '\t') {
                break;
            }
        }

        spacesCount ++;
    }

    if(m_useSpacesAsTab) {
        spacesCount /= m_tabSpaceCount;
    }

    return spacesCount;
}

int InteractiveTextEdit::getCursorIndentationLevel() {
    return getIndentationLevel(textCursor().selectionStart());
}

qsizetype InteractiveTextEdit::tabSpaceCount() const {
    return m_tabSpaceCount;
}

void InteractiveTextEdit::setTabSpaceCount(qsizetype newTabSpaceCount) {
    m_tabSpaceCount = newTabSpaceCount;
}

bool InteractiveTextEdit::useSpacesAsTab() const {
    return m_useSpacesAsTab;
}

void InteractiveTextEdit::setUseSpacesAsTab(bool newUseSpacesAsTab) {
    m_useSpacesAsTab = newUseSpacesAsTab;
}
