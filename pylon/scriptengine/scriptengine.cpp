#include "scriptengine.h"

namespace ScriptEngine
{
    bool started;

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
        //started = true;
        Py_Initialize();
        started = ScriptEngine::HasBegun();
    }

    void End()
    {
        //started = false;
        Py_Finalize();
        started = ScriptEngine::HasBegun();
    }

    bool HasBegun()
    {
        return (bool)Py_IsInitialized();
        //return started;
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
