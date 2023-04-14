#ifndef KEYCOMPLETION_H
#define KEYCOMPLETION_H

#include <QTextDocumentFragment>

#include "interactivetextedit.h"

class InteractiveTextEdit;

class KeyCompletion : public QObject {
    Q_OBJECT
public:
    explicit KeyCompletion(InteractiveTextEdit *parent = nullptr);

    bool autocomplete(QKeyEvent *e);

signals:

private:
    bool autocompleteInQuotes(QKeyEvent *e);
    bool autocompleteNotSelected(QKeyEvent *e);
    bool autocompleteSelected(QKeyEvent *e, const QString &selectedText);
    void buildBrackets();

private:
    InteractiveTextEdit *mw_textEdit;
};

#endif // KEYCOMPLETION_H
