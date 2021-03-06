#ifndef SCRIPTTHREAD_H_INCLUDED
#define SCRIPTTHREAD_H_INCLUDED

#include "../threads/threads.h"

class ScriptThread : public Threads::ExThread
{
    private:
        bool firstRun;
        std::string mainScriptData;
        //ScriptEngine::Executor *mainScript;
        ScriptEngine::InterpreterThread * mainScript;
        //ScriptEngine::SubInterpreter * mainScript;
    public:
        ScriptThread();
        ScriptThread(bool);
        ~ScriptThread();

        volatile bool running;

        void run();

        void FirstRun();
        void MainRun();

        void SingleCall();
};

void ScriptCallFunction();

#endif // SCRIPTTHREAD_H_INCLUDED
