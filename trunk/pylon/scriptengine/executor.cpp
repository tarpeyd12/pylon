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

    std::string Executor::getInstructions()
    {
        return instructions;
    }

    Execute::Execute(std::string instructions) : ScriptEngine::Executor()
    {
        //ScriptEngine::Initialize();
        PyRun_SimpleString(instructions.c_str());
        //ScriptEngine::Finalize();
    }

    Execute::Execute(const Executor& other) : ScriptEngine::Executor()
    {
        //ScriptEngine::Initialize();
        PyRun_SimpleString(Executor(other).getInstructions().c_str());
        //ScriptEngine::Finalize();
    }

    Execute::~Execute()
    {
        //ScriptEngine::Executor::~Executor();
    }

    FileExecutor::FileExecutor(std::string file) : ScriptEngine::Executor(file)
    {

    }

    FileExecutor::FileExecutor(const Executor& other) : ScriptEngine::Executor()
    {

    }

    FileExecutor::~FileExecutor()
    {

    }

    void FileExecutor::Execute()
    {
        ScriptEngine::Initialize();
        PyRun_AnyFile(stdout, getInstructions().c_str());
        ScriptEngine::Finalize();
    }

    FunctionCaller::FunctionCaller(std::string inst) : ScriptEngine::Executor(inst)
    {

    }

    FunctionCaller::~FunctionCaller()
    {

    }

    void FunctionCaller::call(std::string func, std::string* args, unsigned int numArgs)
    {
        PyObject *pName, *pModule, *pFunc;
        PyObject *pArgs, *pValue = NULL;

        //ScriptEngine::Initialize();
        pName = PyString_FromString(getInstructions().c_str());
        //pModule = PyImport_ImportModuleNoBlock(getInstructions().c_str());
        pModule = PyImport_Import(pName);
        if (pModule != NULL) {
            pFunc = PyObject_GetAttrString(pModule, func.c_str());
            if (pFunc && PyCallable_Check(pFunc)) {
                pArgs = PyTuple_New(numArgs);
                for(unsigned int i = 0; i < numArgs; i++)
                {
                    std::string type = args[i].substr(0, args[i].find_first_of(' '));
                    std::string data = args[i].substr(args[i].find_first_of(' '));

                    //std::cout << type << " " << data << std::endl;

                    if(type.compare("int") == 0)
                    {
                        pValue = PyInt_FromLong(atoi(data.c_str()));
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
                    printf("Result of call: %ld\n", PyInt_AsLong(pValue));
                    Py_DECREF(pValue);
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
        //ScriptEngine::Finalize();
    }

}
