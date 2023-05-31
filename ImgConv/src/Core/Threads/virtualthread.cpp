#include "virtualthread.h"

Threads::VirtualThread::VirtualThread()
    : QObject(), QRunnable() {

    m_uuid = QUuid::createUuid();
}

QUuid Threads::VirtualThread::getUUID() {
    return m_uuid;
}
