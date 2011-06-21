#ifndef SCRIPTTHREAD_H_INCLUDED
#define SCRIPTTHREAD_H_INCLUDED

#include "../threads/threads.h"

class ScriptThread : public ExThread
{
    private:
        bool firstRun;
    public:
        ScriptThread();
        ~ScriptThread();
        void run();
};

#endif // SCRIPTTHREAD_H_INCLUDED
