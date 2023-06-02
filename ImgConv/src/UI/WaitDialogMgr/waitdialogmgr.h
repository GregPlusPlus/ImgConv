
#ifndef WAITDIALOGMGR_H
#define WAITDIALOGMGR_H

#include <QObject>
#include <QMap>
#include <QUuid>

#include "UI/Dialogs/WaitDialog/waitdialog.h"

class WaitDialogMgr : public QObject
{
    Q_OBJECT
public:
    explicit WaitDialogMgr(QObject *parent = nullptr);
    ~WaitDialogMgr();

public slots:
    void createWaitDialog(const QUuid &uuid, const QString &msg);
    void closeDialog(const QUuid &uuid);

signals:

private:
    QMap<QUuid, WaitDialog*> m_waitDialogs;

};

#endif // WAITDIALOGMGR_H
