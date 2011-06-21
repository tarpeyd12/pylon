#ifndef CALCTHREAD_H_INCLUDED
#define CALCTHREAD_H_INCLUDED

#include "../threads/threads.h"

class CalcThread : public ExThread
{
    public:
        CalcThread();
        ~CalcThread();
        void run();
};

#endif // CALCTHREAD_H_INCLUDED
