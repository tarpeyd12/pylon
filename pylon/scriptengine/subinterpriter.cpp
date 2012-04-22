#include "subinterpriter.h"

namespace ScriptEngine
{
    SubInterpreter::SubInterpreter()
    {
        instructions = NULL;
        // get the global lock
        PyEval_AcquireLock();
        // create a thread state object for this thread
        threadState = Py_NewInterpreter();
        // free the lock
        PyEval_ReleaseLock();
    }

    SubInterpreter::SubInterpreter( Executor * inst )
    {
        instructions = inst;
        // get the global lock
        PyEval_AcquireLock();
        // create a thread state object for this thread
        threadState = Py_NewInterpreter();
        // free the lock
        PyEval_ReleaseLock();
    }

    SubInterpreter::~SubInterpreter()
    {
        if( instructions )
        {
            delete instructions;
        }
        instructions = NULL;

        // grab the lock
        PyEval_AcquireLock();
        // swap my thread state out of the interpreter
        PyThreadState_Swap(threadState);
        Py_EndInterpreter(threadState);
        // release the lock
        PyEval_ReleaseLock();
    }

    Executor * SubInterpreter::getInstructions() const
    {
        return instructions;
    }

    void SubInterpreter::Execute()
    {
        if( !instructions )
        {
            return;
        }

        // grab the global interpreter lock
        PyEval_AcquireLock();
        // swap in my thread state
        PyThreadState_Swap(threadState);
        // execute some python code
        instructions->Execute();
        // clear the thread state
        PyThreadState_Swap(NULL);
        // release our hold on the global interpreter
        PyEval_ReleaseLock();
    }

    void SubInterpreter::ExecuteOther( Executor * other )
    {
        if( !other )
        {
            return;
        }

        // grab the global interpreter lock
        PyEval_AcquireLock();
        // swap in my thread state
        PyThreadState_Swap(threadState);
        // execute some python code
        other->Execute();
        // clear the thread state
        PyThreadState_Swap(NULL);
        // release our hold on the global interpreter
        PyEval_ReleaseLock();
    }
}
