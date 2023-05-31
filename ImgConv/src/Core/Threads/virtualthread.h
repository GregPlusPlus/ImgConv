#ifndef VIRTUALTHREAD_H
#define VIRTUALTHREAD_H

#include <QRunnable>

namespace Threads {
class VirtualThread : public QRunnable
{
public:
    VirtualThread();
};
}

#endif // VIRTUALTHREAD_H
