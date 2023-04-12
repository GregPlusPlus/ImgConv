// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

//![codeeditordefinition]

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    bool useSpacesAsTab() const;
    void setUseSpacesAsTab(bool newUseSpaceForTab);

    qsizetype tabSpaceCount() const;
    void setTabSpaceCount(qsizetype newTabSpaceCount);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
    bool autocomplete(QKeyEvent *e);

private:
    QString buildTabs(int level);
    char charBeforeCursor();
    char charAfterCursor();
    QString charAroundCursor();
    void removeCharAroundCursor();
    int getCurrentLineIndentationLevel();
    void buildBrackets();

private:
    QWidget *lineNumberArea;

private:
    qsizetype m_useSpacesAsTab = false;
    quint8 m_tabSpaceCount = 4;
};

//![codeeditordefinition]
//![extraarea]

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor)
    {}

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

//![extraarea]

#endif
