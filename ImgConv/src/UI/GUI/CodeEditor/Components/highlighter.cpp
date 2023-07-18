/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "highlighter.h"

using namespace UI::GUI::CodeEditorComponents;

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter{parent} {
    HighlightingRule rule;

    numberFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegularExpression(QStringLiteral("(?<![a-zA-Z])[-+]?(?:\\d+(?:\\.\\d*)?|\\.\\d+)(?:[eE][-+]?\\d+)?[fF]?\\b"));
    rule.format = numberFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegularExpression(QStringLiteral("0[xX][0-9a-fA-F]+"));
    rule.format = numberFormat;
    highlightingRules.append(rule);

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\bconst\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\binline\\b"),
        QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"), QStringLiteral("\\btypedef\\b"),
        QStringLiteral("\\btypename\\b"), QStringLiteral("\\bunion\\b"), QStringLiteral("\\bvolatile\\b"),
        QStringLiteral("\\breturn\\b"), QStringLiteral("\\bbreak\\b"), QStringLiteral("\\bcontinue\\b"),
        QStringLiteral("\\bsizeof\\b"), QStringLiteral("\\bcase\\b"), QStringLiteral("\\bdefault\\b"),
        QStringLiteral("\\btrue\\b"), QStringLiteral("\\bfalse\\b")
    };
    for(const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    typeFormat.setForeground(Qt::blue);
    typeFormat.setFontWeight(QFont::Bold);
    const QString typePatterns[] = {
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bdouble\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bbool\\b"),
        QStringLiteral("\\bcl_char\\b"), QStringLiteral("\\buchar\\b"), QStringLiteral("\\bcl_uchar\\b"),
        QStringLiteral("\\bcl_short\\b"), QStringLiteral("\\bushort\\b"), QStringLiteral("\\bcl_ushort\\b"),
        QStringLiteral("\\bcl_int\\b"), QStringLiteral("\\buint\\b"), QStringLiteral("\\bcl_uint\\b"),
        QStringLiteral("\\bcl_long\\b"), QStringLiteral("\\bulong\\b"), QStringLiteral("\\bcl_ulong\\b"),
        QStringLiteral("\\bfloat\\b"), QStringLiteral("\\bsize_t\\b"), QStringLiteral("\\bptrdiff_t\\b"),
        QStringLiteral("\\bintptr_t\\b"), QStringLiteral("\\bhalf\\b"), QStringLiteral("\\bchar([2-4]|8|16)?\\b"),
        QStringLiteral("\\buchar([2-4]|8|16)?\\b"), QStringLiteral("\\bshort([2-4]|8|16)?\\b"), QStringLiteral("\\bushort([2-4]|8|16)?\\b"),
        QStringLiteral("\\bint([2-4]|8|16)?\\b"), QStringLiteral("\\buint([2-4]|8|16)?\\b"), QStringLiteral("\\blong([2-4]|8|16)?\\b"),
        QStringLiteral("\\bulong([2-4]|8|16)?\\b"), QStringLiteral("\\bfloat([2-4]|8|16)?\\b"), QStringLiteral("\\bdouble([2-4]|8|16)?\\b"),
        QStringLiteral("\\bhalf([2-4]|8|16)?\\b"), QStringLiteral("\\bcl_platform_id\\b"), QStringLiteral("\\bcl_device_id\\b"),
        QStringLiteral("\\bcl_context\\b"), QStringLiteral("\\bcl_command_queue\\b"), QStringLiteral("\\bcl_mem\\b"),
        QStringLiteral("\\bcl_program\\b"), QStringLiteral("\\bcl_kernel\\b"), QStringLiteral("\\bcl_event\\b"),
        QStringLiteral("\\bcl_sampler\\b")
    };
    for(const QString &pattern : typePatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = typeFormat;
        highlightingRules.append(rule);
    }

    clkeywordFormat.setFontWeight(QFont::Bold);
    clkeywordFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("__[a-zA-Z0-9_]+?\\s"));
    rule.format = clkeywordFormat;
    highlightingRules.append(rule);

    preprocFormat.setFontWeight(QFont::Bold);
    preprocFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression(QStringLiteral("#[a-zA-Z0-9_]+"));
    rule.format = preprocFormat;
    highlightingRules.append(rule);

    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);

    flowCtrlFormat.setFontItalic(true);
    flowCtrlFormat.setForeground(Qt::blue);
    const QString ctrlPatterns[] = {
        QStringLiteral("\\bif\\b"), QStringLiteral("\\bswitch\\b"), QStringLiteral("\\bwhile\\b"),
        QStringLiteral("\\bdo\\b"), QStringLiteral("\\bfor\\b"), QStringLiteral("\\belse\\b")
    };
    for(const QString &pattern : ctrlPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = flowCtrlFormat;
        highlightingRules.append(rule);
    }

    quoteFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\\\"(?:[^\\\"\\\\]|\\\\.)*\\\"|\\'(?:[^\\'\\\\]|\\\\.)*\\'"));
    rule.format = quoteFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);
    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

void Highlighter::highlightBlock(const QString &text) {
    for(const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while(matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if(previousBlockState() != 1) {
        startIndex = text.indexOf(commentStartExpression);
    }

    while(startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if(endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
