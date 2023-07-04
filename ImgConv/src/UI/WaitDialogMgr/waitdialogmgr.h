
#ifndef WAITDIALOGMGR_H
#define WAITDIALOGMGR_H

#include <QObject>
#include <QMap>
#include <QUuid>

#include "UI/Dialogs/WaitDialog/waitdialog.h"

namespace UI {
class WaitDialogMgr : public QObject
{
    Q_OBJECT
public:
    explicit WaitDialogMgr(QObject *parent = nullptr);
    ~WaitDialogMgr();

public slots:
    void createWaitDialog(const QUuid &uuid, const QString &msg, Dialogs::WaitDialog::Flags flags = Dialogs::WaitDialog::Flags::None);
    void closeDialog(const QUuid &uuid);
    void updateDialogProgress(const QUuid &uuid, size_t percentage);

signals:

private:
    QMap<QUuid, Dialogs::WaitDialog*> m_waitDialogs;

};
}

#endif // WAITDIALOGMGR_H
