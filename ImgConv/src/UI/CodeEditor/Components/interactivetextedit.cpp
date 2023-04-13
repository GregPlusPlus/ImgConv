#include "interactivetextedit.h"

InteractiveTextEdit::InteractiveTextEdit(QWidget *parent)
    : QPlainTextEdit{parent} {

    m_keyCompletion = new KeyCompletion(this);
}

void InteractiveTextEdit::keyPressEvent(QKeyEvent *e) {
    if(!m_keyCompletion->autocomplete(e)) {
        QPlainTextEdit::keyPressEvent(e);
    }
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

int InteractiveTextEdit::getCursorIndentationLevel() {
    if(toPlainText().isEmpty()) {
        return 0;
    }

    QStringList lines = toPlainText().left(textCursor().position()).split("\n");

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
