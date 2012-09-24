#ifndef INTERPRITER_THREAD_H_INCLUDED
#define INTERPRITER_THREAD_H_INCLUDED

#ifndef SCRIPTENGINE_H_INCLUDED
#include "scriptengine.h"
#endif // SCRIPTENGINE_H_INCLUDED

namespace ScriptEngine
{
    class InterpreterThread
    {
        private:
            static unsigned int numInterpreterThreads;
            static Threads::Mutex * threadLock;
            unsigned int myNumInterpreterThreads;
        protected:
            InterpreterState * mainInterpreterState;
            ThreadState * threadState;
            Executor * instructions;
        public:
            InterpreterThread();
            InterpreterThread(Executor*);
            ~InterpreterThread();

            Executor * getInstructions() const;

            static void GetLock();
            static void ReleaseLock();

            void Execute();
    };
}

#endif // INTERPRITER_THREAD_H_INCLUDED
