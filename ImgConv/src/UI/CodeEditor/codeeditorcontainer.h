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


#ifndef CODEEDITORCONTAINER_H
#define CODEEDITORCONTAINER_H

#include <QWidget>
#include <QToolBar>
#include <QLabel>
#include <QToolButton>
#include <QAction>
#include <QMenu>

#include <QVBoxLayout>

#include <QMessageBox>
#include <QFileDialog>

#include <QFile>

#include "Components/codeeditor.h"
#include "Components/keycompletion.h"
#include "Components/highlighter.h"

class CodeEditorContainter : public QWidget {
    Q_OBJECT
public:
    CodeEditorContainter(QWidget *parent = nullptr);
    ~CodeEditorContainter();

    QString getFileName();
    bool isSaved() const;

signals:
    void useFile(const QString &fn);
    void setSaved(bool newSaved);

private slots:
    void generateTemplate(const QString &fn);
    void openFile();
    void saveFile();
    void saveAsFile();
    void applyFile();
    void confirmSave();
    void setFileName(const QString &fn);

private:
    QToolBar *mw_toolBar;
    QToolButton *mw_generateTemplateButton;
    QMenu *mw_generateTemplateMenu;
    QAction *m_apply;
    QAction *m_openFile;
    QToolButton *mw_saveButton;
    QMenu *mw_saveMenu;
    QAction *m_undo;
    QAction *m_redo;
    QLabel *mw_fileName;

    CodeEditor *mw_editor;
    KeyCompletion *m_keyCompletion;
    Highlighter *m_highlighter;

    QVBoxLayout *m_layout;

    QString m_fileName;
    bool m_saved = true;
};

#endif // CODEEDITORCONTAINER_H
