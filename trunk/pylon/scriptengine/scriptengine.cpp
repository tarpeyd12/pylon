#include "scriptengine.h"

namespace ScriptEngine
{
    bool started;

    ThreadState * mainThreadState;

    namespace MethodInterface
    {
        const unsigned int OldArgs = METH_OLDARGS;
        const unsigned int VarArgs = METH_VARARGS;
        const unsigned int KeyWords = METH_KEYWORDS;
        const unsigned int NoArgs = METH_NOARGS;
        //const unsigned int Args0 = METH_O;
        const unsigned int Class = METH_CLASS;
        const unsigned int Static = METH_STATIC;

        ClassList<__Module*> moduleList;

        __Module::__Module()
        {
            module = NULL;
            modname = "";
        }

        __Module::__Module( const std::string& name, ScriptEngine::MethodInterface::Object * mod )
        {
            modname = name;
            module = mod;
        }

        __Module::~__Module()
        {
            module = NULL;
            modname = "";
        }

        void __Module::addIntConstant( const std::string& constantName, long constantValue )
        {
            int ret = PyModule_AddIntConstant( module, constantName.c_str(), constantValue );
            if( ret )
            {
                throw ret;
            }
        }

        bool __Module::operator == ( const __Module& other ) const
        {
            return other.modname.compare( this->modname ) == 0;
        }

        bool __Module::operator == ( const std::string& name ) const
        {
            return name.compare( this->modname ) == 0;
        }

        bool __Module::operator == ( __Module* other ) const
        {
            return other->modname.compare( this->modname ) == 0;
        }

        void __AddModule( __Module* mod )
        {
            moduleList += mod;
        }

        __Module* __GetModule( const std::string& name )
        {
            for( unsigned int i = 0; i < moduleList.length(); ++i )
            {
                if( moduleList[ i ]->operator==( name ) )
                    return moduleList[ i ];
            }
            return NULL;
        }

        void Add( const std::string& name, ScriptEngine::MethodInterface::MethodDef* def )
        {
            Object* ret = Py_InitModule( name.c_str(), def );
            if( !ret )
            {
                cout << "module creation falure" << endl;
                throw -1;
            }
            __AddModule( new __Module( name, ret ) );
        }

        void Add( const std::string& name, ScriptEngine::MethodInterface::MethodDef* def, const std::string& doc )
        {
            Object* ret = Py_InitModule3( name.c_str(), def, doc.c_str() );
            if( !ret )
            {
                cout << "module creation falure" << endl;
                throw -1;
            }
            __AddModule( new __Module( name, ret ) );
        }
    }

    void Begin()
    {
        Py_Initialize();
        //PyEval_InitThreads();
        //mainThreadState = PyThreadState_Swap( NULL );
        mainThreadState = PyEval_SaveThread();
        //PyThreadState_Swap( mainThreadState );
        PyEval_RestoreThread( mainThreadState );
        //PyEval_ReleaseLock();
        started = ScriptEngine::HasBegun();
    }

    void BeginThreads()
    {
        PyEval_InitThreads();
        PyEval_ReleaseLock();
    }

    void End()
    {
        PyEval_AcquireLock();
        PyThreadState_Swap( NULL );
        PyThreadState_Clear( mainThreadState );
        PyThreadState_Delete( mainThreadState );
        //PyEval_Restore( mainThreadState );
        Py_Finalize();
        started = ScriptEngine::HasBegun();
    }

    bool HasBegun()
    {
        return bool( Py_IsInitialized() );
    }

    void Initialize()
    {
        if( !ScriptEngine::HasBegun() )
        {
            ScriptEngine::Begin();
        }
    }

    void Finalize()
    {
        if( ScriptEngine::HasBegun() )
        {
            ScriptEngine::End();
        }
    }
}
