#ifndef INTERACTIVETEXTEDIT_H
#define INTERACTIVETEXTEDIT_H

#include <QPlainTextEdit>
#include <QWidget>

#include "keycompletion.h"

class KeyCompletion;

class InteractiveTextEdit : public QPlainTextEdit {
    Q_OBJECT
public:
    InteractiveTextEdit(QWidget *parent = nullptr);

    bool useSpacesAsTab() const;
    void setUseSpacesAsTab(bool newUseSpaceForTab);

    qsizetype tabSpaceCount() const;
    void setTabSpaceCount(qsizetype newTabSpaceCount);

    int getCursorIndentationLevel();
    char charBeforeCursor();
    char charAfterCursor();
    QString charAroundCursor();
    void removeCharAroundCursor();
    void unindentLine();

    QString buildTabs(int level);

    KeyCompletion *keyCompletion() const;
    void setKeyCompletion(KeyCompletion *newKeyCompletion);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    KeyCompletion *m_keyCompletion = nullptr;

    qsizetype m_useSpacesAsTab = false;
    quint8 m_tabSpaceCount = 4;
};

#endif // INTERACTIVETEXTEDIT_H
