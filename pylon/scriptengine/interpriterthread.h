#ifndef INTERPRITER_THREAD_H_INCLUDED
#define INTERPRITER_THREAD_H_INCLUDED

#ifndef SCRIPTENGINE_H_INCLUDED
#include "scriptengine.h"
#endif // SCRIPTENGINE_H_INCLUDED

namespace ScriptEngine
{
    class InterpreterThread
    {
        protected:
            InterpreterState * mainInterpreterState;
            ThreadState * threadState;
            Executor * instructions;
        public:
            InterpreterThread();
            InterpreterThread(Executor*);
            ~InterpreterThread();

            Executor * getInstructions() const;

            void Execute();
    };
}

#endif // INTERPRITER_THREAD_H_INCLUDED
