// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "codeeditor.h"

#include <QPainter>
#include <QTextBlock>

//![constructor]

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    int id = QFontDatabase::addApplicationFont(":/fonts/SourceCodePro-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont code(family);
    setFont(code);
    setTabStopDistance(40);
    setWordWrapMode(QTextOption::NoWrap);

    lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

//![constructor]

//![extraAreaWidth]

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 20 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

//![extraAreaWidth]

//![slotUpdateExtraAreaWidth]

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

//![slotUpdateExtraAreaWidth]

//![slotUpdateRequest]

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

bool CodeEditor::autocomplete(QKeyEvent *e)
{
    int key = e->key();
    if(key == Qt::Key_Return) {
        insertPlainText("\n" + buildTabs(getCurrentLineIndentationLevel()));
    } else if(key == Qt::Key_Tab && m_useSpacesAsTab) {
        insertPlainText(buildTabs(1));
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

QString CodeEditor::buildTabs(int level)
{
    if(useSpacesAsTab()) {
        return QString(" ").repeated(level * tabSpaceCount());
    }

    return QString("\t").repeated(level);
}

char CodeEditor::charBeforeCursor()
{
    char c = 0;

    int pos = textCursor().position() - 1;

    if(pos >= 0 && pos < toPlainText().size()) {
        c = toPlainText().at(pos).toLatin1();
    }

    return c;
}

char CodeEditor::charAfterCursor()
{
    char c = 0;

    int pos = textCursor().position();

    if(pos >= 0 && pos < toPlainText().size()) {
        c = toPlainText().at(pos).toLatin1();
    }

    return c;
}

QString CodeEditor::charAroundCursor()
{
    return QString(charBeforeCursor()) + QString(charAfterCursor());
}

void CodeEditor::removeCharAroundCursor()
{
    moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
    moveCursor(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    moveCursor(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    textCursor().removeSelectedText();
}

int CodeEditor::getCurrentLineIndentationLevel()
{
    int lineBeginIndex = textCursor().position() - 1;

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

void CodeEditor::buildBrackets()
{
    int indentLvl = getCurrentLineIndentationLevel();

    insertPlainText(QString("{\n%1\n%2}")
                    .arg(buildTabs(indentLvl + 1))
                    .arg(buildTabs(indentLvl)));
    moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    moveCursor(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
}

qsizetype CodeEditor::tabSpaceCount() const
{
    return m_tabSpaceCount;
}

void CodeEditor::setTabSpaceCount(qsizetype newTabSpaceCount)
{
    m_tabSpaceCount = newTabSpaceCount;
}

bool CodeEditor::useSpacesAsTab() const
{
    return m_useSpacesAsTab;
}

void CodeEditor::setUseSpacesAsTab(bool newUseSpacesAsTab)
{
    m_useSpacesAsTab = newUseSpacesAsTab;
}

//![slotUpdateRequest]

//![resizeEvent]

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::keyPressEvent(QKeyEvent *e)
{
    if(!autocomplete(e)) {
        QPlainTextEdit::keyPressEvent(e);
    }
}

//![resizeEvent]

//![cursorPositionChanged]

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor("#CBEEF7");

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QFont f = font();

//![extraAreaPaintEvent_0]

//![extraAreaPaintEvent_1]
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());
//![extraAreaPaintEvent_1]

//![extraAreaPaintEvent_2]
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);

            if(textCursor().blockNumber() == blockNumber) {
                painter.setPen(Qt::black);
                f.setBold(true);
            } else {
                painter.setPen(QColor("#202020"));
                f.setBold(false);
            }

            painter.setFont(f);
            painter.drawText(-10, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}
//![extraAreaPaintEvent_2]

