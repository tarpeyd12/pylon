#include "scriptengine.h"

namespace ScriptEngine
{
    bool started;

    //PyThreadState * mainState;

    namespace MethodInterface
    {
        const unsigned int OldArgs = METH_OLDARGS;
        const unsigned int VarArgs = METH_VARARGS;
        const unsigned int KeyWords = METH_KEYWORDS;
        const unsigned int NoArgs = METH_NOARGS;
        //const unsigned int Args0 = METH_O;
        const unsigned int Class = METH_CLASS;
        const unsigned int Static = METH_STATIC;

        void Add(std::string name, ScriptEngine::MethodInterface::MethodDef* def)
        {
            Py_InitModule(name.c_str(), def);
        }
    }

    void Begin()
    {
        Py_Initialize();
        //PyEval_InitThreads();
        //mainState = PyThreadState_Swap(NULL);
        //PyThreadState_Swap(mainState);
        //PyEval_ReleaseLock();
        started = ScriptEngine::HasBegun();
    }

    void End()
    {
        //PyEval_AcquireLock();
        //PyThreadState_Swap(mainState);
        //PyEval_ReleaseLock();
        Py_Finalize();
        started = ScriptEngine::HasBegun();
    }

    bool HasBegun()
    {
        return (bool)Py_IsInitialized();
    }

    void Initialize()
    {
        if(!ScriptEngine::HasBegun())
            ScriptEngine::Begin();
    }

    void Finalize()
    {
        if(ScriptEngine::HasBegun())
            ScriptEngine::End();
    }
}
