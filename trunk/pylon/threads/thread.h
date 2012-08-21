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
            THREADTYPE (*thread_function)(THREADARGS arg);
            void* data;

            pthread_t thread;
            pthread_attr_t attr;
            sched_param sched;
        public:

            Thread();
            Thread(THREADTYPE (*func)(THREADARGS arg));
            Thread(THREADTYPE (*func)(THREADARGS arg), void* dat);
            ~Thread();

            void setPriority(int);
            void setAffinity(int);

            void setThread(THREADTYPE (*func)(THREADARGS arg));
            void setData(void * dat);
            void * getData();

            void startThread();
            void start();
            void joinThread();
            void join();
            void cancelThread();
            void cancel();

            //void detachThread();
    };

}

#endif // THREAD_H_INCLUDED
