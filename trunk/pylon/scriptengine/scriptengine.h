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

#include "scripttypes.h"

namespace ScriptEngine
{
    namespace MethodInterface
    {
        class __Module
        {
            public:
                std::string modname;
                ScriptEngine::MethodInterface::Object* module;

                __Module();
                ~__Module();
                __Module( const std::string&, ScriptEngine::MethodInterface::Object*);

                void addIntConstant( const std::string&, long );

                bool operator == ( const __Module& ) const;
                bool operator == ( const std::string& ) const;
                bool operator == ( __Module* ) const;
        };

        extern ClassList<__Module*> moduleList;

        void __AddModule( __Module* );

        __Module* __GetModule( const std::string& );

        void Add( const std::string&, ScriptEngine::MethodInterface::MethodDef* );
        void Add( const std::string&, ScriptEngine::MethodInterface::MethodDef*, const std::string& );
    }

    extern volatile bool started;

    extern ThreadState * mainThreadState;

    void Begin();
    void BeginThreads();
    void End();
    bool HasBegun();

    void Initialize();
    void Finalize();


    class Executor;
    class FileExecutor;
    class FunctionCaller;
    class SubInterpreter;
    class InterpreterThread;
}

//#ifndef EXECUTOR_H
#include "executor.h"
//#endif

//#ifndef STRINGPARSER_H_INCLUDED
#include "stringparser.h"
//#endif

//#ifndef INTERPRITER_THREAD_H_INCLUDED
#include "interpriterthread.h"
//#endif

//#ifndef SUBINTERPRITER_H_INCLUDED
#include "subinterpriter.h"
//#endif

#endif // SCRIPTENGINE_H_INCLUDED
