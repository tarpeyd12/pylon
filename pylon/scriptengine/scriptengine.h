#ifndef SCRIPTENGINE_H_INCLUDED
#define SCRIPTENGINE_H_INCLUDED

#ifndef Py_PYTHON_H
#include <Python.h>
#endif // Py_PYTHON_H

#include "../fileloader/fileloader.h"
#include "../threads/threads.h"

#include <iostream>

#ifndef EXECUTOR_H
#include "executor.h"
#endif

#ifndef STRINGPARSER_H_INCLUDED
#include "stringparser.h"
#endif

namespace ScriptEngine
{
    extern bool started;

    void Begin();
    void End();

    void Initialize();
    void Finalize();

    namespace MethodInterface
    {
        typedef PyObject Object;
        typedef PyMethodDef MethodDef;
        typedef PyCFunction CFunction;

        extern const unsigned int OldArgs;
        extern const unsigned int VarArgs;
        extern const unsigned int KeyWords;
        extern const unsigned int NoArgs;
        //extern const unsigned int Args0;
        extern const unsigned int Class;
        extern const unsigned int Static;

        void Add(std::string, ScriptEngine::MethodInterface::MethodDef*);
    }
}

#endif // SCRIPTENGINE_H_INCLUDED
