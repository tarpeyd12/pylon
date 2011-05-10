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
        started = true;
        Py_Initialize();
    }

    void End()
    {
        started = false;
        Py_Finalize();
    }

    void Initialize()
    {
        if(!ScriptEngine::started)
            Py_Initialize();
    }

    void Finalize()
    {
        if(!ScriptEngine::started)
            Py_Finalize();
    }
}
