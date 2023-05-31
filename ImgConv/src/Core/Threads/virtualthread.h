#ifndef VIRTUALTHREAD_H
#define VIRTUALTHREAD_H

#include <QObject>
#include <QRunnable>
#include <QUuid>

namespace Threads {
class VirtualThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    VirtualThread();

    QUuid getUUID();

private:
    QUuid m_uuid;
};
}

#endif // VIRTUALTHREAD_H
