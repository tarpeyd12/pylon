#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#define     THREADTYPE      void*
#define     THREADARGS      void*

namespace Threads
{
    class Thread {
        private:
            void* (*thread_function)(void* arg);
            void* data;

            pthread_t thread;
            pthread_attr_t attr;
            sched_param sched;
        public:

            Thread();
            Thread(void* (*func)(void* arg));
            Thread(void* (*func)(void* arg), void* dat);
            ~Thread();

            void setPriority(int);
            void setAffinity(int);

            void setThread(void* (*func)(void* arg));
            void setData(void * dat);

            void startThread();
            void start();
            void joinThread();
            void join();

            //void detachThread();
    };

}

#endif // THREAD_H_INCLUDED
