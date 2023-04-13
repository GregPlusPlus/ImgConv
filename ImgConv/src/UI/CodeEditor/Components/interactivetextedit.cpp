#include "interactivetextedit.h"

InteractiveTextEdit::InteractiveTextEdit(QWidget *parent)
    : QPlainTextEdit{parent} {

}

void InteractiveTextEdit::keyPressEvent(QKeyEvent *e)
{
    if(!autocomplete(e)) {
        QPlainTextEdit::keyPressEvent(e);
    }
}

bool InteractiveTextEdit::autocomplete(QKeyEvent *e)
{
    int key = e->key();
    if(key == Qt::Key_Return) {
        insertPlainText("\n" + buildTabs(getCurrentLineIndentationLevel()));
    } else if(key == Qt::Key_Tab) {
        if(m_useSpacesAsTab) {
            insertPlainText(buildTabs(1));
        } else {
            return false;
        }
    } else if(key == Qt::Key_BraceLeft) {
        buildBrackets();
    } else if(key == Qt::Key_BraceRight) {
        if(charAfterCursor() == '}') {
            moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    }  else if(key == Qt::Key_ParenLeft) {
        insertPlainText("()");
        moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
    } else if(key == Qt::Key_ParenRight) {
        if(charAfterCursor() == ')') {
            moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_BracketLeft) {
        insertPlainText("[]");
        moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
    } else if(key == Qt::Key_BracketRight) {
        if(charAfterCursor() == ']') {
            moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_QuoteDbl) {
        if(charAfterCursor() == '"' && charBeforeCursor() != '\\') {
            moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else if(charBeforeCursor() != '\\') {
            insertPlainText("\"\"");
            moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_Apostrophe) {
        if(charAfterCursor() == '\'' && charBeforeCursor() != '\\') {
            moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else if(charBeforeCursor() != '\\') {
            insertPlainText("''");
            moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_Backspace) {
        QList<QString> charCouples;
        charCouples.append("{}");
        charCouples.append("()");
        charCouples.append("[]");
        charCouples.append("\"\"");
        charCouples.append("''");

        if(charCouples.contains(charAroundCursor())) {
            removeCharAroundCursor();
        } else {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

QString InteractiveTextEdit::buildTabs(int level)
{
    if(useSpacesAsTab()) {
        return QString(" ").repeated(level * tabSpaceCount());
    }

    return QString("\t").repeated(level);
}

char InteractiveTextEdit::charBeforeCursor()
{
    char c = 0;

    int pos = textCursor().position() - 1;

    if(pos >= 0 && pos < toPlainText().size()) {
        c = toPlainText().at(pos).toLatin1();
    }

    return c;
}

char InteractiveTextEdit::charAfterCursor()
{
    char c = 0;

    int pos = textCursor().position();

    if(pos >= 0 && pos < toPlainText().size()) {
        c = toPlainText().at(pos).toLatin1();
    }

    return c;
}

QString InteractiveTextEdit::charAroundCursor()
{
    return QString(charBeforeCursor()) + QString(charAfterCursor());
}

void InteractiveTextEdit::removeCharAroundCursor()
{
    moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
    moveCursor(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    moveCursor(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    textCursor().removeSelectedText();
}

int InteractiveTextEdit::getCurrentLineIndentationLevel()
{
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

void InteractiveTextEdit::buildBrackets()
{
    int indentLvl = getCurrentLineIndentationLevel();

    insertPlainText(QString("{\n%1\n%2}")
                    .arg(buildTabs(indentLvl + 1))
                    .arg(buildTabs(indentLvl)));
    moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
}

qsizetype InteractiveTextEdit::tabSpaceCount() const
{
    return m_tabSpaceCount;
}

void InteractiveTextEdit::setTabSpaceCount(qsizetype newTabSpaceCount)
{
    m_tabSpaceCount = newTabSpaceCount;
}

bool InteractiveTextEdit::useSpacesAsTab() const
{
    return m_useSpacesAsTab;
}

void InteractiveTextEdit::setUseSpacesAsTab(bool newUseSpacesAsTab)
{
    m_useSpacesAsTab = newUseSpacesAsTab;
}
