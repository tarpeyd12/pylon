#include "interpriterthread.h"

namespace ScriptEngine
{
    InterpreterThread::InterpreterThread()
    {
        instructions = NULL;
        // get the global lock
        //PyEval_AcquireLock();
        // get a reference to the PyInterpreterState
        mainInterpreterState = ScriptEngine::mainThreadState->interp;
        // create a thread state object for this thread
        threadState = PyThreadState_New(mainInterpreterState);
        // free the lock
        //PyEval_ReleaseLock();
    }

    InterpreterThread::InterpreterThread( Executor * inst )
    {
        instructions = inst;
        // get the global lock
        //PyEval_AcquireLock();
        // get a reference to the PyInterpreterState
        mainInterpreterState = ScriptEngine::mainThreadState->interp;
        // create a thread state object for this thread
        threadState = PyThreadState_New(mainInterpreterState);
        // free the lock
        //PyEval_ReleaseLock();
    }

    InterpreterThread::~InterpreterThread()
    {
        if( instructions )
        {
            delete instructions;
        }
        instructions = NULL;

        // grab the lock
        PyEval_AcquireLock();
        // swap my thread state out of the interpreter
        PyThreadState_Swap(NULL);
        // clear out any cruft from thread state object
        PyThreadState_Clear(threadState);
        // delete my thread state object
        PyThreadState_Delete(threadState);
        // release the lock
        PyEval_ReleaseLock();
    }

    Executor * InterpreterThread::getInstructions() const
    {
        return instructions;
    }

    void InterpreterThread::Execute()
    {
        if( !instructions )
        {
            throw -10;
            //return;
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
}
