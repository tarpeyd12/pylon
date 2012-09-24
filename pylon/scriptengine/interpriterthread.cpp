#include "interpriterthread.h"

namespace ScriptEngine
{
    int PythonTrace( PyObject * obj, int * frame, int what, PyObject * arg )
    {
        if( !POGEL::hasproperty( POGEL_DEBUG ) && what != PyTrace_EXCEPTION && what != PyTrace_C_EXCEPTION )
        {
            return 0;
        }
        cout << "PythonInterpriterTrace(";
        PyObject* reslt1 = PyObject_Str( obj );
        char* sres1 = PyString_AsString( reslt1 );
        cout << sres1 << "): ";
        sres1 = NULL;
        reslt1 = NULL;
        switch( what )
        {
            case PyTrace_CALL: cout << "PyTrace_CALL"; break;
            case PyTrace_EXCEPTION: cout << "PyTrace_EXCEPTION"; break;
            case PyTrace_LINE: cout << "PyTrace_LINE"; break;
            case PyTrace_RETURN: cout << "PyTrace_RETURN"; break;
            case PyTrace_C_CALL: cout << "PyTrace_C_CALL"; break;
            case PyTrace_C_EXCEPTION: cout << "PyTrace_C_EXCEPTION"; break;
            case PyTrace_C_RETURN: cout << "PyTrace_C_RETURN"; break;
            default: cout << "Unknown Code: " << what; break;
        }
        PyObject* reslt = PyObject_Str( arg );
        char* sres = PyString_AsString( reslt );
        cout << " " << sres;
        sres = NULL;
        reslt = NULL;
        cout << endl;
        return 0;
    }

    unsigned int InterpreterThread::numInterpreterThreads = 0;
    Threads::Mutex * InterpreterThread::threadLock = NULL;

    InterpreterThread::InterpreterThread()
    {
        if( !threadLock )
        {
            threadLock = new Threads::Mutex();
        }
        cout << "Creating InterpriterThread(" << numInterpreterThreads << ")" << endl;
        instructions = NULL;
        // get a reference to the PyInterpreterState
        mainInterpreterState = ScriptEngine::mainThreadState->interp;
        //mainInterpreterState = PyThreadState_Get()->interp;//ScriptEngine::mainThreadState->interp;
        // create a thread state object for this thread
        threadState = PyThreadState_New(mainInterpreterState);

        //PyEval_RestoreThread(threadState);
        //PyEval_ReleaseThread(threadState);

        myNumInterpreterThreads = numInterpreterThreads;
        ++numInterpreterThreads;
    }

    InterpreterThread::InterpreterThread( Executor * inst )
    {
        if( !threadLock )
        {
            threadLock = new Threads::Mutex();
        }
        cout << "Creating InterpriterThread(" << numInterpreterThreads << ") with Executor(" << inst->getExecutorIdNum() << ")" << endl;
        instructions = inst;
        // get a reference to the PyInterpreterState
        mainInterpreterState = ScriptEngine::mainThreadState->interp;
        //mainInterpreterState = PyThreadState_Get()->interp;//ScriptEngine::mainThreadState->interp;
        // create a thread state object for this thread
        threadState = PyThreadState_New(mainInterpreterState);

        //PyEval_RestoreThread(threadState);
        //PyEval_ReleaseThread(threadState);

        myNumInterpreterThreads = numInterpreterThreads;
        ++numInterpreterThreads;
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
        --numInterpreterThreads;
    }

    Executor * InterpreterThread::getInstructions() const
    {
        return instructions;
    }

    void InterpreterThread::GetLock()
    {
        threadLock->TryLock();

        //usleep(1000);
        PyEval_AcquireLock();
    }

    void InterpreterThread::ReleaseLock()
    {
        PyEval_ReleaseLock();
        threadLock->Unlock();
    }

    void InterpreterThread::Execute()
    {
        if( !instructions )
        {
            ThrowError(-10);
            return;
        }

        threadLock->TryLock();

        //usleep(1000);

        /*if( !mainInterpreterState )
        {
            mainInterpreterState = ScriptEngine::mainThreadState->interp;
        }
        if( !threadState )
        {
            threadState = PyThreadState_New(mainInterpreterState);
        }*/
        if( POGEL::hasproperty(POGEL_DEBUG) && false )
        {
            cout << "Executing InterpriterThread(" << myNumInterpreterThreads << "/" << numInterpreterThreads << ")";
            cout << " with Executor(" << instructions->getExecutorIdNum() << "/" << instructions->getNumExecutors() << ")" << endl;
        }
        PyGILState_STATE state = PyGILState_Ensure();
        // grab the global interpreter lock
        //PyEval_AcquireLock();
        // swap in my thread state
        //PyEval_AcquireThread(threadState);
        //PyEval_RestoreThread(threadState);
        //PyThreadState_Swap(NULL);
        //PyThreadState_Swap(threadState);
        // register a profiler
        if( POGEL::hasproperty(POGEL_DEBUG) && false )
        {
            PyEval_SetProfile( (Py_tracefunc)PythonTrace, Py_BuildValue("i",myNumInterpreterThreads) );
        }
        // execute some python code
        instructions->Execute();
        // clear the thread state
        //PyThreadState_Swap(NULL);
        // release our hold on the global interpreter
        //PyEval_ReleaseLock();
        //PyEval_ReleaseThread(threadState);
        PyGILState_Release(state);

        threadLock->Unlock();
    }
}
