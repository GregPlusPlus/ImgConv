#include "keycompletion.h"

KeyCompletion::KeyCompletion(InteractiveTextEdit *parent)
    : QObject{parent}, m_textEdit{parent} {

}

QString KeyCompletion::buildTabs(int level) {
    if(m_textEdit->useSpacesAsTab()) {
        return QString(" ").repeated(level * m_textEdit->tabSpaceCount());
    }

    return QString("\t").repeated(level);
}

void KeyCompletion::buildBrackets() {
    int indentLvl = m_textEdit->getCurrentLineIndentationLevel();

    m_textEdit->insertPlainText(QString("{\n%1\n%2}")
                                .arg(buildTabs(indentLvl + 1))
                                .arg(buildTabs(indentLvl)));
    m_textEdit->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    m_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
}

bool KeyCompletion::autocomplete(QKeyEvent *e) {
    int key = e->key();

    if(key == Qt::Key_Return) {
        m_textEdit->insertPlainText("\n" + buildTabs(m_textEdit->getCurrentLineIndentationLevel()));
    } else if(key == Qt::Key_Tab) {
        if(m_textEdit->useSpacesAsTab()) {
            m_textEdit->insertPlainText(buildTabs(1));
        } else {
            return false;
        }
    } else if(key == Qt::Key_BraceLeft) {
        buildBrackets();
    } else if(key == Qt::Key_BraceRight) {
        if(m_textEdit->charAfterCursor() == '}') {
            m_textEdit->moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    }  else if(key == Qt::Key_ParenLeft) {
        m_textEdit->insertPlainText("()");
        m_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
    } else if(key == Qt::Key_ParenRight) {
        if(m_textEdit->charAfterCursor() == ')') {
            m_textEdit->moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_BracketLeft) {
        m_textEdit->insertPlainText("[]");
        m_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
    } else if(key == Qt::Key_BracketRight) {
        if(m_textEdit->charAfterCursor() == ']') {
            m_textEdit->moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_QuoteDbl) {
        if(m_textEdit->charAfterCursor() == '"' && m_textEdit->charBeforeCursor() != '\\') {
            m_textEdit->moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else if(m_textEdit->charBeforeCursor() != '\\') {
            m_textEdit->insertPlainText("\"\"");
            m_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
        } else {
            return false;
        }
    } else if(key == Qt::Key_Apostrophe) {
        if(m_textEdit->charAfterCursor() == '\'' && m_textEdit->charBeforeCursor() != '\\') {
            m_textEdit->moveCursor(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        } else if(m_textEdit->charBeforeCursor() != '\\') {
            m_textEdit->insertPlainText("''");
            m_textEdit->moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
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

        if(charCouples.contains(m_textEdit->charAroundCursor())) {
            m_textEdit->removeCharAroundCursor();
        } else {
            return false;
        }
    } else {
        return false;
    }

    return true;
}
