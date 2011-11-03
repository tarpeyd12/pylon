#ifndef EXTHREAD_H_INCLUDED
#define EXTHREAD_H_INCLUDED

#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include "thread.h"

namespace Threads
{

    THREADTYPE _exThreadFunction(THREADARGS);

    class ExThread : private Threads::Thread
    {
        public:
            ExThread();
            ~ExThread();

            void setPriority(int);
            void setAffinity(int);

            void startThread();
            void start();
            void joinThread();
            void join();
            void cancelThread();
            void cancel();

            virtual void run();

            friend THREADTYPE Threads::_exThreadFunction(THREADARGS);
    };

}

#endif // EXTHREAD_H_INCLUDED
