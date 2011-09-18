#ifndef SCRIPTENGINE_H_INCLUDED
#define SCRIPTENGINE_H_INCLUDED

#ifndef Py_PYTHON_H
#include <Python.h> // include Python.h before any other includes, because it redefines some system stuff if it is after other includes
#ifdef _POSIX_C_SOURCE
#undef _POSIX_C_SOURCE
#endif
#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#endif
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
    bool HasBegun();

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
