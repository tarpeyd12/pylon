#include "exthread.h"

namespace Threads
{

    THREADTYPE _exThreadFunction(THREADARGS thread)
    {
        try
        {
            ((Threads::ExThread*)thread)->run();
        }
        catch(...)
        {
            std::cout << "*** THREAD EXCEPTION ***" << std::endl;
            throw;
        }
        pthread_exit(NULL);
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

    void ExThread::cancelThread()
    {
        Threads::Thread::cancelThread();
    }

    void ExThread::cancel()
    {
        Threads::Thread::cancelThread();
    }

}
