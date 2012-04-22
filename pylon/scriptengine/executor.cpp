#include "executor.h"

namespace ScriptEngine
{
    Executor::Executor()
    {
        instructions = "";
    }

    Executor::Executor(std::string instr)
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
        if(!is_init)
            ScriptEngine::Initialize();

        int ret = PyRun_SimpleString(getInstructions().c_str());
        PyObject* err = PyErr_Occurred();
        if(ret || err)
        {
            if(err)
                PyErr_Print();
            throw ret;
        }

        if(!is_init)
            ScriptEngine::Finalize();
    }

    std::string Executor::getInstructions()
    {
        return instructions;
    }

    std::string Executor::getResult()
    {
        return std::string();
    }



    FileExecutor::FileExecutor(std::string file) : ScriptEngine::Executor(file)
    {

    }

    FileExecutor::~FileExecutor()
    {

    }

    void FileExecutor::Execute()
    {
        bool is_init = ScriptEngine::HasBegun();
        if(!is_init)
            ScriptEngine::Initialize();

        int ret = PyRun_AnyFile(stdout, getInstructions().c_str());
        PyObject* err = PyErr_Occurred();
        if(ret || err)
        {
            if(err)
                PyErr_Print();
            throw ret;
        }

        if(!is_init)
            ScriptEngine::Finalize();
    }

    FunctionCaller::FunctionCaller(std::string inst) : ScriptEngine::Executor(inst)
    {

    }

     FunctionCaller::FunctionCaller(std::string inst, std::string func, std::string* args, unsigned int numArgs) : ScriptEngine::Executor(inst)
    {
        function = func;
        arguments.add( args, numArgs );
    }

    FunctionCaller::~FunctionCaller()
    {
        arguments.clear();
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

    void FunctionCaller::call(std::string func, std::string* args, unsigned int numArgs, std::string* res)
    {
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
                for(unsigned int i = 0; i < numArgs; i++)
                {
                    std::string type = args[i].substr(0, args[i].find_first_of(':'));
                    std::string data = args[i].substr(args[i].find_first_of(':')+1);

                    /*if(POGEL::hasproperty(POGEL_DEBUG))
                    {
                        concatargs = concatargs + args[i];
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
                    Py_DECREF(pValue);
                    Py_DECREF(reslt);
                    result = type+":"+std::string(sres);
                    //if(POGEL::hasproperty(POGEL_DEBUG))
                        //cout << "Function " << func << "(" << concatargs << ") resulted in " << result << endl;
                    sres = NULL;

                    if( res )
                    {
                        *res = result;
                    }
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
