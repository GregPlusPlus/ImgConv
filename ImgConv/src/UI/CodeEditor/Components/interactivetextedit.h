#ifndef INTERACTIVETEXTEDIT_H
#define INTERACTIVETEXTEDIT_H

#include <QPlainTextEdit>
#include <QWidget>

class InteractiveTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    InteractiveTextEdit(QWidget *parent = nullptr);

    bool useSpacesAsTab() const;
    void setUseSpacesAsTab(bool newUseSpaceForTab);

    qsizetype tabSpaceCount() const;
    void setTabSpaceCount(qsizetype newTabSpaceCount);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    QString buildTabs(int level);
    char charBeforeCursor();
    char charAfterCursor();
    QString charAroundCursor();
    void removeCharAroundCursor();
    int getCurrentLineIndentationLevel();
    void buildBrackets();
    bool autocomplete(QKeyEvent *e);

private:
    qsizetype m_useSpacesAsTab = false;
    quint8 m_tabSpaceCount = 4;
};

#endif // INTERACTIVETEXTEDIT_H
