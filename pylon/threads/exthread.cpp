#include "exthread.h"

THREADTYPE _exThreadFunction(THREADARGS thread)
{
    ((ExThread*)thread)->run();
    return NULL;
}

ExThread::ExThread() : Thread(_exThreadFunction, (void*)this)
{

}

ExThread::~ExThread()
{

}

void ExThread::run()
{

}

void ExThread::startThread()
{
    Thread::startThread();
}

void ExThread::start()
{
    Thread::startThread();
}

void ExThread::joinThread()
{
    Thread::joinThread();
}

void ExThread::join()
{
    Thread::joinThread();
}
