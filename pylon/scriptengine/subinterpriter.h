#ifndef SUBINTERPRITER_H_INCLUDED
#define SUBINTERPRITER_H_INCLUDED

#ifndef SCRIPTENGINE_H_INCLUDED
#include "scriptengine.h"
#endif // SCRIPTENGINE_H_INCLUDED

namespace ScriptEngine
{
    class SubInterpreter
    {
        protected:
            ThreadState * threadState;
            Executor * instructions;
        public:
            SubInterpreter();
            SubInterpreter( Executor * );
            ~SubInterpreter();

            Executor * getInstructions() const;

            void Execute();

            void ExecuteOther( Executor * );
    };
}

#endif // SUBINTERPRITER_H_INCLUDED
