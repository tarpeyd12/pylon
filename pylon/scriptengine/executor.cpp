#include "executor.h"

namespace ScriptEngine
{
    Executor::Executor()
    {
        instructions = "";
    }

    Executor::Executor( const std::string& instr)
    {
        instructions = instr;
    }

    Executor::~Executor()
    {
        instructions = "";
    }

    Executor& Executor::operator=(const Executor& rhs)
    {
        if (this == &rhs) return *this; // handle self assignment
        //assignment operator
        return *this;
    }

    void Executor::Execute()
    {
        bool is_init = ScriptEngine::HasBegun();
        if( !is_init )
        {
            ScriptEngine::Initialize();
        }

        #if defined( SIMPLE_EXECUTION )
        int ret = PyRun_SimpleString( getInstructions().c_str() );
        PyObject* err = PyErr_Occurred();
        if( ret || err )
        {
            if( err )
            {
                PyErr_Print();
            }
            throw ret;
        }
        #else
        PyObject* mainModule = PyImport_ImportModule( "__main__" );
        //PyObject* mainModule = PyImport_AddModule("__main__");
        PyObject* globalDict = PyModule_GetDict( mainModule );
        PyObject* localDict = globalDict;

        char* inst = strcpy(new char[getInstructions().length()], getInstructions().c_str());

        PyObject* ret = PyRun_String( inst, Py_file_input, globalDict, localDict );
        delete [] inst;
        PyObject* err = PyErr_Occurred();
        if( !ret || err )
        {
            if( err )
            {
                PyErr_Print();
            }
            throw -1;
        }
        #endif

        if( !is_init )
        {
            ScriptEngine::Finalize();
        }
    }

    std::string Executor::getInstructions()
    {
        return instructions;
    }

    std::string Executor::getResult()
    {
        return std::string();
    }



    FileExecutor::FileExecutor( const std::string& file ) : ScriptEngine::Executor( file )
    {

    }

    FileExecutor::~FileExecutor()
    {

    }

    void FileExecutor::Execute()
    {
        bool is_init = ScriptEngine::HasBegun();
        if( !is_init )
        {
            ScriptEngine::Initialize();
        }

        int ret = PyRun_AnyFile( stdout, getInstructions().c_str() );
        PyObject* err = PyErr_Occurred();
        if( ret || err )
        {
            if( err )
            {
                PyErr_Print();
            }
            throw ret;
        }

        if( !is_init )
        {
            ScriptEngine::Finalize();
        }
    }

    FunctionCaller::FunctionCaller( const std::string& inst ) : ScriptEngine::Executor(inst)
    {
        outsidefunction = true;
        if( !instructions.length() )
        {
            instructions = "__main__";
        }
    }

    FunctionCaller::FunctionCaller( const std::string& inst, bool out ) : ScriptEngine::Executor(inst)
    {
        outsidefunction = out;
        if( !instructions.length() )
        {
            instructions = "__main__";
        }
    }

    FunctionCaller::FunctionCaller( const std::string& inst,  const std::string& func, std::string* args, unsigned int numArgs ) : ScriptEngine::Executor(inst)
    {
        function = func;
        arguments.add( args, numArgs );
        outsidefunction = true;
        if( !instructions.length() )
        {
            instructions = "__main__";
        }
    }

    FunctionCaller::FunctionCaller( const std::string& inst,  const std::string& func, std::string* args, unsigned int numArgs, bool out ) : ScriptEngine::Executor(inst)
    {
        function = func;
        arguments.add( args, numArgs );
        outsidefunction = out;
        if( !instructions.length() )
        {
            instructions = "__main__";
        }
    }

    FunctionCaller::~FunctionCaller()
    {
        arguments.clear();
        outsidefunction = true;
    }

    void FunctionCaller::setArgs(std::string* args,unsigned int numArgs)
    {
        arguments.clear();
        arguments.add( args, numArgs );
    }

    void FunctionCaller::Execute()
    {
        if( arguments.length() )
        {
            call( function, arguments.getList(), arguments.length(), NULL );
        }
    }

    void FunctionCaller::call( const std::string& func, std::string* args, unsigned int numArgs, std::string* res)
    {
        if( !args )
        {
            throw -1;
        }
        ClassList< std::string > arguments( numArgs );
        for(unsigned int i = 0; i < numArgs; ++i)
        {
            arguments += args[ i ];
            //cout << "FUNC " << func << " ARG" << i << ": " << args[i] << endl;
        }
        //cout << endl;
        bool is_init = ScriptEngine::HasBegun();
        if(!is_init)
            ScriptEngine::Initialize();

        PyObject *pName, *pModule, *pFunc;
        PyObject *pArgs, *pValue = NULL;

        pName = PyString_FromString(getInstructions().c_str());
        //pModule = PyImport_ImportModuleNoBlock(getInstructions().c_str());
        pModule = PyImport_Import(pName);

        if (pModule != NULL) {
            pFunc = PyObject_GetAttrString(pModule, func.c_str());
            if (pFunc && PyCallable_Check(pFunc)) {
                pArgs = PyTuple_New(numArgs);
                //std::string concatargs = "";
                for(unsigned int i = 0; i < numArgs; ++i)
                {
                    unsigned int argnum = i;
                    std::string curarg(arguments[ i ]);
                    unsigned int colonposition = curarg.find_first_of(':');
                    std::string type = curarg.substr(0, colonposition);
                    std::string data = curarg.substr(colonposition+1);
                    argnum = 0;

                    /*if(POGEL::hasproperty(POGEL_DEBUG))
                    {
                        concatargs = concatargs + curarg;
                        if( i+1 <numArgs )
                            concatargs = concatargs + ",";
                    }*/

                    //std::cout << type << " " << data << std::endl;

                    if(!type.compare("int"))
                    {
                        pValue = PyInt_FromLong(atoi(data.c_str()));
                    }
                    else
                    if(!type.compare("bool"))
                    {
                        if(!data.compare("true") || !data.compare("True"))
                            pValue = PyBool_FromLong(1);
                        else if(!data.compare("false") || !data.compare("False"))
                            pValue = PyBool_FromLong(0);
                        else
                            pValue = PyBool_FromLong(atoi(data.c_str()));
                    }
                    else
                    if(!type.compare("long"))
                    {
                        pValue = PyLong_FromLong(atoi(data.c_str()));
                    }
                    else
                    if(!type.compare("float"))
                    {
                        PyObject* s = PyString_FromString(data.c_str());
                        pValue = PyFloat_FromString(s,NULL);
                        // delete s;
                        Py_DECREF(s);
                    }
                    else
                    if(!type.compare("str"))
                    {
                        pValue = PyString_FromString(data.c_str());
                    }
                    else
                    if(!type.compare("char"))
                    {
                        pValue = Py_BuildValue("c", data[ 0 ]);
                    }
                    else
                    {
                        pValue = NULL;
                    }

                    if (!pValue) {
                        Py_DECREF(pArgs);
                        Py_DECREF(pModule);
                        fprintf(stderr, "Cannot convert argument\n");
                        return;
                    }

                    PyTuple_SetItem(pArgs, i, pValue);
                    type = data = curarg = "";
                }
                pValue = PyObject_CallObject(pFunc, pArgs);
                Py_DECREF(pArgs);
                if (pValue != NULL) {
                    std::string type = "?";
                    if( PyString_Check(pValue) )
                    {
                        type = "str";
                    }
                    else
                    if( PyFloat_Check(pValue) )
                    {
                        type = "float";
                    }
                    else
                    if( PyLong_Check(pValue) )
                    {
                        type = "long";
                    }
                    else
                    if( PyBool_Check(pValue) )
                    {
                        type = "bool";
                    }
                    else
                    if( PyInt_Check(pValue) )
                    {
                        type = "int";
                    }
                    PyObject* reslt = PyObject_Str(pValue);
                    const char* sres = PyString_AsString(reslt);

                    char* sres2 = strcpy(new char[strlen(sres)],sres);
                    sres = NULL;

                    Py_DECREF(pValue);
                    Py_DECREF(reslt);

                    result = type+":"+std::string(sres2);
                    delete [] sres2;

                    if( res )
                    {
                        *res = result;
                    }
                    //if(POGEL::hasproperty(POGEL_DEBUG))
                        //cout << "Function " << func << "(" << concatargs << ") resulted in " << result << endl;
                }
                else {
                    Py_DECREF(pFunc);
                    Py_DECREF(pModule);
                    PyErr_Print();
                    fprintf(stderr,"Call failed\n");
                    return;
                }
            }
            else {
                if (PyErr_Occurred())
                    PyErr_Print();
                fprintf(stderr, "Cannot find function \"%s\"\n", func.c_str());
            }
            Py_XDECREF(pFunc);
            Py_DECREF(pModule);
        }
        else {
            PyErr_Print();
            fprintf(stderr, "Failed to load \"%s\"\n", getInstructions().c_str());
            return;
        }

        if(!is_init)
            ScriptEngine::Finalize();
    }

    std::string FunctionCaller::getResult()
    {
        return result;
    }


}
