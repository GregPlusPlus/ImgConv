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


#include "codeeditorcontainer.h"

CodeEditorContainter::CodeEditorContainter(QWidget *parent) :
    QWidget{parent} {

    mw_editor = new CodeEditor(this);

    int id = QFontDatabase::addApplicationFont(":/fonts/SourceCodePro-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont code(family);
    mw_editor->setFont(code);

    m_layout = new QVBoxLayout;
    m_layout->addWidget(mw_editor);

    setLayout(m_layout);
}

CodeEditorContainter::~CodeEditorContainter() {

}
