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
            static unsigned int numBlocks;
            static unsigned int numMutexes;
            unsigned int mutexIDnum;
            pthread_mutex_t mutex;
            volatile bool locked;
        public:
            Mutex();
            ~Mutex();
            void Lock();
            void Unlock();

            int TryLock();

            bool isLocked() const;

            inline unsigned int getID() { return mutexIDnum; }
            static inline unsigned int getNumBlocks() { return numBlocks; }
    };
}


#endif // MUTEX_H_INCLUDED
