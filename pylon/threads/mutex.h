#ifndef MUTEX_H_INCLUDED
#define MUTEX_H_INCLUDED

#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

namespace Threads
{
    class Mutex
    {
        private:
            pthread_mutex_t mutex;
        public:
            Mutex();
            ~Mutex();
            void Lock();
            void Unlock();

            int TryLock();

    };
}


#endif // MUTEX_H_INCLUDED
