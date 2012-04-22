#include "thread.h"

namespace Threads
{

    Thread::Thread()
    {
        thread_function = NULL;
        data = NULL;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        //setPriority(0);
    }

    Thread::Thread(void* (*func)(void* arg))
    {
        thread_function = func;
        data = NULL;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        //setPriority(0);
    }

    Thread::Thread(void* (*func)(void* arg), void* dat)
    {
        thread_function = func;
        data = dat;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        //setPriority(0);
    }

    Thread::~Thread()
    {
        // I do not know if this line works on windows or not because it
        //  usuall never gets called, see "Threads::Thread::joinThread()"
        int ret = pthread_attr_destroy(&attr);
        if ( ret )
        {
            throw ret;
        }
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
        priority = 0;
    }

    void Thread::setAffinity(int affinity)
    {
        #if !(defined(WINDOWS) || defined(_WIN32) || defined(_WIN64)) // quickfix
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(affinity, &cpuset);
        if ( pthread_setaffinity_np( thread, sizeof(cpu_set_t), &cpuset ) )
            std::cout << "pthread_setaffinity_np failed" << std::endl;
        int s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
        int j;
        if (s != 0)
            std::cout << "pthread_getaffinity_np " << s << std::endl;

        std::cout << "Set Thread Affinity to: " << std::endl;
        for (j = 0; j < CPU_SETSIZE; j++)
            if (CPU_ISSET(j, &cpuset))
                std::cout << "    CPU " << j << std::endl;
        #endif
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
        // this line fails on windows, no clue why, it just forces the program
        //  to exit abruptly
        int ret = pthread_join(thread, NULL);
        if( ret )
        {
            //std::cout << "*** THREAD JOIN FAILURE: " << ret << " ***" << std::endl;
            throw ret;
            //exit(-1);
        }
    }

    void Thread::join()
    {
        this->joinThread();
    }

    void Thread::cancelThread()
    {
        int ret = pthread_cancel(thread);
        if( ret )
        {
            //std::cout << "*** THREAD CANCEL FAILURE: " << ret << " ***" << std::endl;
            throw ret;
            //exit(-1);
        }
    }

    void Thread::cancel()
    {
        this->cancelThread();
    }

}

