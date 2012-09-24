#include "executor.h"

namespace ScriptEngine
{
    unsigned int Executor::numExecutors = 0;
    Executor::Executor()
    {
        instructions = "";
        executorId = numExecutors++;
    }

    Executor::Executor( const std::string& instr)
    {
        instructions = instr;
        executorId = numExecutors++;
    }

    Executor::~Executor()
    {
        //--numExecutors;
        instructions = "";
    }

    Executor& Executor::operator=(const Executor& rhs)
    {
        if (this == &rhs) return *this; // handle self assignment
        //assignment operator
        throw -1;
        return *this;
    }

    void Executor::Execute()
    {
        bool is_init = ScriptEngine::HasBegun();
        if( !is_init )
            ScriptEngine::Initialize();

        #if defined( SIMPLE_EXECUTION )
        //int ret = PyRun_SimpleString( getInstructions().c_str() );
        PyCompilerFlags flags;
        flags.cf_flags = Py_InspectFlag;
        //std::string inst = getInstructions();
        //int ret = PyRun_SimpleStringFlags( (const char*)inst.c_str(), &flags );
        char* inst = strcpy(new char[getInstructions().length()], (getInstructions()).c_str());
        int ret = 0;
        ret = PyRun_SimpleStringFlags( inst, &flags );
        delete [] inst;

        PyObject* err = PyErr_Occurred();
        if( ret || err )
        {
            if( err )
            {
                PyErr_Print();
            }
            ThrowError(ret);
        }
        #else
        PyObject* mainModule = PyImport_ImportModule( "__main__" );
        //PyObject* mainModule = PyImport_AddModule( "__main__" );
        if( !mainModule )
        {
            ThrowError(-1);
        }
        //PyObject* mainModule = PyImport_AddModule("__main__");
        PyObject* globalDict = PyModule_GetDict( mainModule );
        PyObject* localDict = globalDict;
        if( !globalDict )
        {
            ThrowError(-2);
        }

        char* inst = strcpy(new char[getInstructions().length()], getInstructions().c_str());

        //PyObject* ret = PyRun_String( inst, Py_file_input, globalDict, localDict );
        PyCompilerFlags flags;
        flags.cf_flags = Py_InspectFlag;
        PyObject* ret = PyRun_StringFlags( inst, Py_file_input, globalDict, localDict, &flags );
        //PyObject* ret = PyRun_StringFlags( inst, Py_file_input, PyEval_GetGlobals(), PyEval_GetLocals(), &flags );

        delete [] inst;
        PyObject* err = PyErr_Occurred();
        if( !ret || err )
        {
            if( err )
            {
                PyErr_Print();
            }
            ThrowError(-3);
        }
        #endif

        if( !is_init )
            ScriptEngine::Finalize();
    }

    unsigned int Executor::getExecutorIdNum() const
    {
        return executorId;
    }

    unsigned int Executor::getNumExecutors() const
    {
        return numExecutors;
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
        //arguments.add( args, numArgs );
        setArgs( args, numArgs );
        outsidefunction = true;
        if( !instructions.length() )
        {
            instructions = "__main__";
        }
    }

    FunctionCaller::FunctionCaller( const std::string& inst,  const std::string& func, std::string* args, unsigned int numArgs, bool out ) : ScriptEngine::Executor(inst)
    {
        function = func;
        //arguments.add( args, numArgs );
        setArgs( args, numArgs );
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
        if( !args )
            ThrowError(-1);
        arguments.clear();
        //arguments.add( args, numArgs );
        //arguments = convertArgs( args, numArgs );
        arguments.add( convertArgs(args,numArgs), numArgs );
    }

    void FunctionCaller::setArgs(ScriptEngine::MethodInterface::Object** args,unsigned int numArgs)
    {
        if( !args )
            ThrowError(-1);
        arguments.clear();
        for( unsigned int i = 0; i < numArgs; ++i )
        {
            if( !args[i] )
                ThrowError(-2);
            arguments += args[i];
        }
        //arguments.add( args, numArgs );
        //arguments = convertArgs( args, numArgs );
    }

    void FunctionCaller::setArg( ScriptEngine::MethodInterface::Object* arg, unsigned int index )
    {
        if( !arg )
            ThrowError(-1);
        arguments.replace( index, arg );
    }

    void FunctionCaller::clearArg( unsigned int index )
    {
        arguments.replace( index, NULL );
    }

    void FunctionCaller::Execute()
    {
        if( arguments.length() )
        {
            call( function, arguments.getList(), arguments.length(), NULL );
        }
        else
        {
            ThrowError(-2);
        }
    }

    void FunctionCaller::call( const std::string& func, std::string* args, unsigned int numArgs, std::string* res)
    {
        if( !args )
        {
            ThrowError(-1);
        }

        //bool is_init = ScriptEngine::HasBegun();
        //if(!is_init) ScriptEngine::Initialize();
        arguments.clear();
        arguments.add( convertArgs(args,numArgs), numArgs );

        //if(!is_init) ScriptEngine::Finalize();

        if( arguments.length() != numArgs )
        {
            ThrowError(-2);
        }

        call( func, arguments.getList(), arguments.length(), res);

    }

    void FunctionCaller::call( const std::string& func, ScriptEngine::MethodInterface::Object** args, unsigned int numArgs, std::string* res )
    {
        if( !args )
        {
            ThrowError(-1);
        }
        bool is_init = ScriptEngine::HasBegun();
        if(!is_init)
            ScriptEngine::Initialize();
        //unsigned int numArgs = args.length();
        PyObject *pName = NULL, *pModule, *pFunc;
        PyObject *pArgs, *pValue = NULL;
        std::string inst = getInstructions();
        pName = PyString_FromString(inst.c_str());
        //pModule = PyImport_ImportModuleNoBlock(getInstructions().c_str());
        pModule = PyImport_Import(pName);
        //pModule = PyImport_ImportModule(getInstructions().c_str());

        if (pModule != NULL)
        {
            pFunc = PyObject_GetAttrString(pModule, func.c_str());
            if (pFunc && PyCallable_Check(pFunc))
            {
                pArgs = PyTuple_New(numArgs);
                if( POGEL::hasproperty(POGEL_DEBUG) && false )
                {
                    cout << "FUNC: " << func << "(" << numArgs << ")" << endl;
                }
                for( unsigned int i = 0; i < numArgs; ++i )
                {
                    if( POGEL::hasproperty(POGEL_DEBUG) && false )
                    {
                        PyObject* r = PyObject_Str(args[i]);
                        const char* sres = PyString_AsString(r);
                        //Py_CLEAR(r);
                        //Py_DECREF(r);
                        //char* sres2 = strcpy(new char[strlen(sres)],sres);
                        //sres = NULL;
                        cout << "\tArg" << i << ": '" << std::string(sres) << "'" << endl;
                        //delete [] sres2;
                        sres = NULL;
                    }
                    //Py_XINCREF(args[i]);
                    if( PyTuple_SetItem(pArgs, i, args[i]) )
                    {
                        cout << "PyTuple_SetItem(pArgs, " << i << ", args[" << i << "]) Failed" << endl;
                        ThrowError(-5);
                    }
                    //args[ i ] = NULL;
                    //Py_DECREF(args[i]);
                }
                pValue = PyObject_CallObject(pFunc, pArgs);
                //Py_DECREF(pArgs);
                Py_CLEAR(pArgs);
                if (pValue != NULL)
                {
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
                else
                {
                    Py_DECREF(pFunc);
                    Py_DECREF(pModule);
                    PyErr_Print();
                    fprintf(stderr,"Call failed\n");
                    ThrowError(-3);
                    return;
                }
            }
            else
            {
                if (PyErr_Occurred())
                    PyErr_Print();
                fprintf(stderr, "Cannot find function \"%s\"\n", func.c_str());
            }
            Py_XDECREF(pFunc);
            Py_DECREF(pModule);
        }
        else
        {
            PyErr_Print();
            fprintf(stderr, "Failed to load \"%s\"\n", getInstructions().c_str());
            ThrowError(-4);
            return;
        }

        if(!is_init)
            ScriptEngine::Finalize();
        for( unsigned int i = 0; i < arguments.length(); ++i )
        {
            arguments.replace( i, NULL );
        }
    }

    std::string FunctionCaller::getResult()
    {
        return result;
    }

    ScriptEngine::MethodInterface::Object** FunctionCaller::convertArgs( std::string* args, unsigned int numArgs ) const
    {
        if( !args )
        {
            ThrowError(-1);
        }
        //ClassList<ScriptEngine::MethodInterface::Object*> ret(numArgs);
        ScriptEngine::MethodInterface::Object** ret = new ScriptEngine::MethodInterface::Object*[numArgs];
        ClassList< std::string > argumentss( numArgs );
        for(unsigned int i = 0; i < numArgs; ++i)
        {
            argumentss += args[ i ];
            ret[i] = NULL;
            //cout << "FUNC " << function << " ARG" << i << ": " << args[i] << endl;
        }

        ScriptEngine::MethodInterface::Object* pValue = NULL;

        for(unsigned int i = 0; i < numArgs; ++i)
        {
            std::string curarg(argumentss[ i ]);
            unsigned int colonposition = curarg.find_first_of(':');
            std::string type = curarg.substr(0, colonposition);
            std::string data = curarg.substr(colonposition+1);

            if( !data.length() )
                continue;

            pValue = NULL;

            if(!type.compare("int"))
            {
                pValue = PyInt_FromLong(atoi((const char*)data.c_str()));
            }
            else
            if(!type.compare("bool"))
            {
                if(!data.compare("true") || !data.compare("True"))
                    pValue = PyBool_FromLong(1);
                else if(!data.compare("false") || !data.compare("False"))
                    pValue = PyBool_FromLong(0);
                else
                    pValue = PyBool_FromLong(atoi((const char*)data.c_str()));
            }
            else
            if(!type.compare("long"))
            {
                pValue = PyLong_FromLong(atoi((const char*)data.c_str()));
            }
            else
            if(!type.compare("float"))
            {
                PyObject* s = PyString_FromString((const char*)data.c_str());
                pValue = PyFloat_FromString(s,NULL);
                // delete s;
                Py_DECREF(s);
            }
            else
            if(!type.compare("str"))
            {
                pValue = PyString_FromString((const char*)data.c_str());
            }
            else
            if(!type.compare("char"))
            {
                pValue = Py_BuildValue("c", data[ 0 ]);
            }
            else
            //if(!type.compare("?"))
            {
                pValue = NULL;
                //pValue = Py_BuildValue( type.c_str(), data.c_str() );
            }

            if (!pValue) {
                //Py_DECREF(pArgs);
                //Py_DECREF(pModule);
                fprintf(stderr, "Cannot convert argument %d, %s\n", i, curarg.c_str());
                //delete [] ret;
                //throw -2;
                ThrowError(-2);
                return NULL;
            }
            //ret.replace( i, pValue );// += pValue;
            ret[i] = pValue;
        }
        return ret;//ret.getList();
    }


}
