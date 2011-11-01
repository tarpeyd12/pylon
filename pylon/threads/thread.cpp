#include "thread.h"

namespace Threads
{

    Thread::Thread()
    {
        thread_function = NULL;
        data = NULL;
        setPriority(0);
    }

    Thread::Thread(void* (*func)(void* arg))
    {
        thread_function = func;
        data = NULL;
        setPriority(0);
    }

    Thread::Thread(void* (*func)(void* arg), void* dat)
    {
        thread_function = func;
        data = dat;
        setPriority(0);
    }

    Thread::~Thread()
    {
        pthread_attr_destroy(&attr);
        thread_function = NULL;
        //data = NULL;
    }

    void Thread::setPriority(int priority)
    {
        //int ret = pthread_setschedprio(thread,priority);
        /*sched_param param;
        param.__sched_priority = priority;
        int ret = pthread_setschedparam(thread, SCHED_FIFO, &param);*/
        //if( ret ) std::cout << "Failed to set Thread priority, err: " << ret << std::endl;
    }

    void Thread::setAffinity(int affinity)
    {
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(affinity, &cpuset);
        if ( pthread_setaffinity_np( thread, sizeof(cpu_set_t), &cpuset ) )
            std::cout << "pthread_setaffinity_np failed" << std::endl;
        int s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
        int j;
        if (s != 0)
            std::cout << "pthread_getaffinity_np " << s << std::endl;

        std::cout << "Set returned by pthread_getaffinity_np() contained: " << std::endl;
        for (j = 0; j < CPU_SETSIZE; j++)
            if (CPU_ISSET(j, &cpuset))
                std::cout << "    CPU " << j << std::endl;
    }

    void Thread::setThread(void* (*func)(void* arg))
    {
        thread_function = func;
    }

    void Thread::setData(void * dat)
    {
        data = dat;
    }

    void Thread::startThread()
    {
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        int ret = pthread_create( &thread, &attr, thread_function, data);
        if( ret )
        {
            //std::cout << "*** THREAD START FAILURE: " << ret << " ***" << std::endl;
            throw ret;//"*** THREAD START FAILURE:  ***";
            //exit(-1);
        }
    }

    void Thread::start()
    {
        this->startThread();
    }

    void Thread::joinThread()
    {
        int ret = pthread_join(thread, NULL);
        if( ret )
        {
            //std::cout << "*** THREAD JOIN FAILURE: " << ret << " ***" << std::endl;
            throw ret; return;
            //exit(-1);
        }
    }

    void Thread::join()
    {
        this->joinThread();
    }

}

