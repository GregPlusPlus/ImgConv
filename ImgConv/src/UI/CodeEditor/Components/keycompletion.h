#ifndef KEYCOMPLETION_H
#define KEYCOMPLETION_H

#include "interactivetextedit.h"

class InteractiveTextEdit;

class KeyCompletion : public QObject {
    Q_OBJECT
public:
    explicit KeyCompletion(InteractiveTextEdit *parent = nullptr);

    bool autocomplete(QKeyEvent *e);

signals:

private:
    QString buildTabs(int level);
    void buildBrackets();

private:
    InteractiveTextEdit *m_textEdit;
};

#endif // KEYCOMPLETION_H
