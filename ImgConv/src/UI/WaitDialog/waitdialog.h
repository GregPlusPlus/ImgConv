#ifndef WAITDIALOG_H
#define WAITDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QMovie>

class WaitDialog : public QDialog
{
    Q_OBJECT
public:
    WaitDialog(const QString &text);

    QString text() const;

public slots:
    void setText(const QString &text);

private:
    QHBoxLayout *m_layout;
    QLabel *mw_spinnerLabel;
    QLabel *mw_textLabel;

private:
    QMovie *m_spinner;
};

#endif // WAITDIALOG_H
