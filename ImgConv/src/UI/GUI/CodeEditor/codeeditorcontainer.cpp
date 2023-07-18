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

using namespace UI::GUI;

CodeEditorContainter::CodeEditorContainter(QWidget *parent) :
    QWidget{parent} {

    mw_editor = new CodeEditorComponents::CodeEditor(this);
    mw_editor->setUseSpacesAsTab(true);
    m_keyCompletion = new CodeEditorComponents::KeyCompletion(mw_editor);
    m_highlighter = new CodeEditorComponents::Highlighter(mw_editor->document());
    connect(mw_editor, &CodeEditorComponents::CodeEditor::textChanged, [=]() {
        setSaved(false);
    });

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

    mw_saveButton = new QToolButton(mw_toolBar);
    mw_saveButton->setIcon(QIcon(":/icons/disk.png"));
    mw_saveButton->setPopupMode(QToolButton::InstantPopup);
    mw_saveMenu = new QMenu(tr("Save file"), mw_saveButton);
    mw_saveButton->setMenu(mw_saveMenu);
    mw_saveMenu->addAction(QIcon(":/icons/disk.png"), tr("Save"), tr("Ctrl+S"), this, &CodeEditorContainter::saveFile);
    mw_saveMenu->addAction(QIcon(":/icons/disk-rename.png"), tr("Save as"), tr("Ctrl+Shift+S"), this, &CodeEditorContainter::saveAsFile);

    mw_toolBar->addWidget(mw_generateTemplateButton);
    UI::GUI::Utils::addShortcutToToolTip(mw_toolBar->addAction(QIcon(":/icons/tick-button.png"), tr("Apply"), tr("F9"), this, &CodeEditorContainter::applyFile));
    mw_toolBar->addSeparator();
    UI::GUI::Utils::addShortcutToToolTip(mw_toolBar->addAction(QIcon(":/icons/folder-horizontal-open.png"), tr("Open file"), tr("Ctrl+Shift+O"), this, &CodeEditorContainter::openFile));
    mw_toolBar->addWidget(mw_saveButton);
    mw_toolBar->addSeparator();
    mw_toolBar->addAction(QIcon(":/icons/arrow-curve-180-left.png"), tr("Undo"), mw_editor, &QPlainTextEdit::undo);
    mw_toolBar->addAction(QIcon(":/icons/arrow-curve.png"), tr("Redo"), mw_editor, &QPlainTextEdit::redo);

    mw_statusBar = new QStatusBar(this);
    mw_statusBar->setSizeGripEnabled(false);

    mw_saved = new QLabel(this);
    mw_saved->setPixmap(QPixmap(":/icons/disk-small-black.png"));

    mw_fileName = new QLabel(tr("Untitled"), this);

    m_layout = new QVBoxLayout;
    m_layout->addWidget(mw_toolBar);
    m_layout->addWidget(mw_editor);
    m_layout->addWidget(mw_statusBar);

    mw_statusBar->addWidget(mw_saved);
    mw_statusBar->addWidget(mw_fileName);

    setLayout(m_layout);
}

CodeEditorContainter::~CodeEditorContainter() {

}

QString CodeEditorContainter::getFileName() {
    return m_fileName;
}

void CodeEditorContainter::setFileName(const QString &fn) {
    m_fileName = fn;

    mw_fileName->setText((m_fileName.isEmpty())? tr("Untitled"): m_fileName);
}

bool CodeEditorContainter::isSaved() const {
    return m_saved;
}

void CodeEditorContainter::setSaved(bool s) {
    m_saved = s;

    if(m_saved) {
        mw_saved->setPixmap(QPixmap(":/icons/disk-small.png"));
        mw_saved->setToolTip(tr("File is saved"));
    } else {
        mw_saved->setPixmap(QPixmap(":/icons/disk-small-black.png"));
        mw_saved->setToolTip(tr("File is not saved"));
    }
}

void CodeEditorContainter::generateTemplate(const QString &fn) {
    confirmSave();

    QFile f(fn);

    if(!f.open(QFile::ReadOnly)) {
        f.close();
        return;
    }

    mw_editor->setPlainText(f.readAll());
    setSaved(false);
    setFileName(QString());

    f.close();
}

void CodeEditorContainter::openFile() {
    confirmSave();

    QString fn = QFileDialog::getOpenFileName(this, tr("Open OpenCL source file"),
                                              QString(), tr("OpenCL source (*.cl *.c);;All files (*.*)"));

    if(fn.isEmpty()) {
        return;
    }

    setFileName(fn);

    QFile f(fn);

    if(!f.open(QFile::ReadOnly)) {
        f.close();
        return;
    }

    mw_editor->setPlainText(f.readAll());
    setSaved(true);

    f.close();
}

void CodeEditorContainter::saveFile() {
    if(isSaved()) {
        return;
    }

    QString fn;

    if(getFileName().isEmpty()) {
        fn = QFileDialog::getSaveFileName(this, tr("Save OpenCL source file"),
                                          QString(), tr("OpenCL source (*.cl *.c);;All files (*.*)"));
    } else {
        fn = getFileName();
    }

    if(fn.isEmpty()) {
        setSaved(false);

        return;
    }

    QFile f(fn);

    if(!f.open(QFile::WriteOnly)) {
        f.close();
        setSaved(false);

        return;
    }

    if(f.write(mw_editor->toPlainText().toLatin1()) != -1) {
        setFileName(fn);
        setSaved(true);
    }

    f.close();
}

void CodeEditorContainter::saveAsFile() {
    QString fn = QFileDialog::getSaveFileName(this, tr("Save OpenCL source file as..."),
                                      QString(), tr("OpenCL source (*.cl *.c);;All files (*.*)"));

    if(fn.isEmpty()) {
        return;
    }

    QFile f(fn);

    if(!f.open(QFile::WriteOnly)) {
        f.close();

        return;
    }

    if(f.write(mw_editor->toPlainText().toLatin1()) != -1) {
        setFileName(fn);
        setSaved(true);
    }

    f.close();
}

void CodeEditorContainter::applyFile() {
    saveFile();

    if(!getFileName().isEmpty()) {
        emit useFile(getFileName());
    }
}

void CodeEditorContainter::confirmSave() {
    if(!isSaved()) {
        if(QMessageBox::question(this, tr("Unsaved file"), tr("Save file before proceeding ?"),
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            saveFile();
        }
    }
}
