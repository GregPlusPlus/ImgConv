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

    mw_toolBar = new QToolBar(this);

    mw_generateTemplateButton = new QToolButton(mw_toolBar);
    mw_generateTemplateButton->setIcon(QIcon(":/icons/wand.png"));
    mw_generateTemplateButton->setPopupMode(QToolButton::InstantPopup);
    mw_generateTemplateMenu = new QMenu(tr("Generate code template"), mw_generateTemplateButton);
    mw_generateTemplateButton->setMenu(mw_generateTemplateMenu);
    mw_generateTemplateMenu->addAction(QIcon(":/icons/wand.png"), tr("Basic template"), this, [=]() {
        generateTemplate(":/ocl/basic_template.cl");
    });
    mw_generateTemplateMenu->addAction(QIcon(":/icons/wand.png"), tr("Convolution template"), this, [=]() {
        generateTemplate(":/ocl/conv2D.cl");
    });

    m_apply = new QAction(QIcon(":/icons/tick-button.png"), tr("Apply"), mw_toolBar);
    connect(m_apply, &QAction::triggered, this, &CodeEditorContainter::applyFile);

    m_openFile = new QAction(QIcon(":/icons/folder-horizontal-open.png"), tr("Open file"), mw_toolBar);
    connect(m_openFile, &QAction::triggered, this, &CodeEditorContainter::openFile);

    m_saveFile = new QAction(QIcon(":/icons/disk.png"), tr("Save file"), mw_toolBar);
    connect(m_saveFile, &QAction::triggered, this, &CodeEditorContainter::saveFile);

    mw_toolBar->addWidget(mw_generateTemplateButton);
    mw_toolBar->addAction(m_apply);
    mw_toolBar->addSeparator();
    mw_toolBar->addAction(m_openFile);
    mw_toolBar->addAction(m_saveFile);

    mw_editor = new CodeEditor(this);
    mw_editor->setUseSpacesAsTab(true);
    connect(mw_editor, &CodeEditor::textChanged, [=]() {
        m_saved = false;
    });

    m_layout = new QVBoxLayout;
    m_layout->addWidget(mw_toolBar);
    m_layout->addWidget(mw_editor);

    setLayout(m_layout);
}

CodeEditorContainter::~CodeEditorContainter() {

}

void CodeEditorContainter::generateTemplate(const QString &fn) {
    confirmSave();

    QFile f(fn);

    if(!f.open(QFile::ReadOnly)) {
        f.close();
        return;
    }

    mw_editor->setPlainText(f.readAll());
    m_saved = false;
    m_fileName = QString();

    f.close();
}

void CodeEditorContainter::openFile() {
    confirmSave();

    QString fn = QFileDialog::getOpenFileName(this, tr("Open OpenCL source file"),
                                              QString(), tr("OpenCL source (*.cl *.c);;All files (*.*)"));

    if(fn.isEmpty()) {
        return;
    }

    m_fileName = fn;

    QFile f(fn);

    if(!f.open(QFile::ReadOnly)) {
        f.close();
        return;
    }

    mw_editor->setPlainText(f.readAll());
    m_saved = true;

    f.close();
}

void CodeEditorContainter::saveFile() {
    if(m_saved) {
        return;
    }

    QString fn;

    if(m_fileName.isEmpty()) {
        fn = QFileDialog::getSaveFileName(this, tr("Save OpenCL source file"),
                                          QString(), tr("OpenCL source (*.cl *.c);;All files (*.*)"));
    } else {
        fn = m_fileName;
    }

    if(fn.isEmpty()) {
        m_saved = false;

        return;
    }

    QFile f(fn);

    if(!f.open(QFile::WriteOnly)) {
        f.close();
        m_saved = false;

        return;
    }

    if(f.write(mw_editor->toPlainText().toLatin1()) != -1) {
        m_fileName = fn;
        m_saved = true;
    }

    f.close();
}

void CodeEditorContainter::applyFile() {
    saveFile();

    emit useFile(m_fileName);
}

void CodeEditorContainter::confirmSave() {
    if(!m_saved) {
        if(QMessageBox::question(this, tr("Unsaved file"), tr("Save file before proceeding ?"),
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            saveFile();
        }
    }
}
