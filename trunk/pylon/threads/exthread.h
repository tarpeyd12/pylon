#ifndef EXTHREAD_H_INCLUDED
#define EXTHREAD_H_INCLUDED

#ifndef THREADS_H_INCLUDED
#include "threads.h"
#endif

THREADTYPE _exThreadFunction(THREADARGS);

class ExThread : private Thread
{
    public:
        ExThread();
        ~ExThread();

        void startThread();
        void joinThread();

        virtual void run();

        friend THREADTYPE _exThreadFunction(THREADARGS);
};

#endif // EXTHREAD_H_INCLUDED
