#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QWidget>

class CodeEditor : public QWidget {
    Q_OBJECT
public:
    CodeEditor(QWidget *parent = nullptr);
    ~CodeEditor();
};

#endif // CODEEDITOR_H
