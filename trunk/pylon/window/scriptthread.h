#ifndef SCRIPTTHREAD_H_INCLUDED
#define SCRIPTTHREAD_H_INCLUDED

#include "../threads/threads.h"

class ScriptThread : public ExThread
{
    private:
        bool firstRun;
        std::string mainScriptData;
        ScriptEngine::Executor *mainScript;
    public:
        ScriptThread();
        ScriptThread(bool);
        ~ScriptThread();

        bool running;

        void run();

        void FirstRun();
        void MainRun();

        void SingleCall();
};

void ScriptCallFunction();

#endif // SCRIPTTHREAD_H_INCLUDED
