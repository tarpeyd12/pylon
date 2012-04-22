#ifndef SCRIPT_TYPES_H_INCLUDED
#define SCRIPT_TYPES_H_INCLUDED

namespace ScriptEngine
{
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
    }

    typedef PyThreadState ThreadState;
    typedef PyInterpreterState InterpreterState;
}

#endif // SCRIPT_TYPES_H_INCLUDED
