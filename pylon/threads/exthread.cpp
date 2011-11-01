#include "exthread.h"

namespace Threads
{

    THREADTYPE _exThreadFunction(THREADARGS thread)
    {
        ((Threads::ExThread*)thread)->run();
        return NULL;
    }

    ExThread::ExThread() : Threads::Thread(Threads::_exThreadFunction, (void*)this)
    {

    }

    ExThread::~ExThread()
    {

    }

    void ExThread::run()
    {

    }

    void ExThread::setPriority(int p)
    {
        Threads::Thread::setPriority(p);
    }

    void ExThread::setAffinity(int a)
    {
        Threads::Thread::setAffinity(a);
    }

    void ExThread::startThread()
    {
        Threads::Thread::startThread();
    }

    void ExThread::start()
    {
        Threads::Thread::startThread();
    }

    void ExThread::joinThread()
    {
        Threads::Thread::joinThread();
    }

    void ExThread::join()
    {
        Threads::Thread::joinThread();
    }

}
