#include "main.h"

#include "mainscriptdefs.h"

#include "versionheaders.h"

namespace Main
{
    ScriptEngine::MethodInterface::Object* lockCalculations( ScriptEngine::MethodInterface::Object* )
    {
        if( !Main::calcLock )
        {
            Renderer::Physics::doIncrimentSimulations = false;
            Main::calcLock = true;
            usleep( 1000 );
            if( !Main::SingleThreaded )
            {
                try
                {
                    Main::calcThread->cancelThread();
                    Main::calcThread->joinThread();
                }
                catch( int e )
                {
                    cout << "Physics Thread Destruction Failure " << e << endl;
                }
            }
            else
            {
                Renderer::HaltPhysics = true;
            }
        }
        Py_RETURN_NONE;
    }

    ScriptEngine::MethodInterface::Object* unlockCalculations( ScriptEngine::MethodInterface::Object* )
    {
        if( Main::calcLock )
        {
            Renderer::Physics::doIncrimentSimulations = true;
            Main::calcLock = false;
            if( !Main::SingleThreaded )
            {
                try
                {
                    Main::calcThread->startThread();
                }
                catch( int e )
                {
                    cout << "Physics Thread Creation Failure " << e << endl;
                }
            }
            else
            {
                Renderer::HaltPhysics = false;
            }
        }
        Py_RETURN_NONE;
    }

    ScriptEngine::MethodInterface::MethodDef calcLockMethods[] =
    {
        { "lock", (ScriptEngine::MethodInterface::CFunction)lockCalculations, ScriptEngine::MethodInterface::NoArgs, NULL },
        { "unlock", (ScriptEngine::MethodInterface::CFunction)unlockCalculations, ScriptEngine::MethodInterface::NoArgs, NULL },
        { NULL }
    };

    ScriptEngine::MethodInterface::Object* lockRenderer( ScriptEngine::MethodInterface::Object* )
    {
        if( !Renderer::drawLock )
        {
            Renderer::drawLock = true;
        }
        Py_RETURN_NONE;
    }

    ScriptEngine::MethodInterface::Object* unlockRenderer( ScriptEngine::MethodInterface::Object* )
    {
        if( Renderer::drawLock )
        {
            Renderer::drawLock = false;
        }
        Py_RETURN_NONE;
    }

    ScriptEngine::MethodInterface::MethodDef drawLockMethods[] =
    {
        { "lock", (ScriptEngine::MethodInterface::CFunction)lockRenderer, ScriptEngine::MethodInterface::NoArgs, NULL },
        { "unlock", (ScriptEngine::MethodInterface::CFunction)unlockRenderer, ScriptEngine::MethodInterface::NoArgs, NULL },
        { NULL }
    };

    ScriptEngine::MethodInterface::Object* getVersion( ScriptEngine::MethodInterface::Object* )
    {
        return Py_BuildValue( "s", Main::VersionStringNoOS.c_str() );
    }

    ScriptEngine::MethodInterface::Object* getPluginVersion(ScriptEngine::MethodInterface::Object* self, ScriptEngine::MethodInterface::Object* args)
    {
        char* pluginName;
        if( !PyArg_ParseTuple( args, "s:getPluginVersion", &pluginName ) )
            return NULL;
        std::string pname( pluginName );
        if( !pname.compare( "pogel" ) )
            return Py_BuildValue( "s", PogelAutoVersion::_FULLVERSION_STRING );
        else
        if( !pname.compare( "fileloader" ) )
            return Py_BuildValue( "s", FileLoaderAutoVersion::_FULLVERSION_STRING );
        else
        if( !pname.compare( "scriptengine" ) )
            return Py_BuildValue( "s", ScriptEngineAutoVersion::_FULLVERSION_STRING );
        else
        if( !pname.compare( "renderer" ) )
            return Py_BuildValue( "s", RendererAutoVersion::_FULLVERSION_STRING );
        else
        if( !pname.compare( "threads" ) )
            return Py_BuildValue( "s", ThreadsAutoVersion::_FULLVERSION_STRING );
        else
        if( !pname.compare( "pogelinterface" ) )
            return Py_BuildValue( "s", pogelInterfaceAutoVersion::_FULLVERSION_STRING );
        else
        if( !pname.compare( "objectloader" ) )
            return Py_BuildValue( "s", ObjectLoaderAutoVersion::_FULLVERSION_STRING );
        else
            return Py_BuildValue( "s", "0.0.0.0" );
    }

    ScriptEngine::MethodInterface::Object* Exit(ScriptEngine::MethodInterface::Object* self, ScriptEngine::MethodInterface::Object* args)
    {
        int ret;
        if( !PyArg_ParseTuple( args, "i:exit", &ret ) )
        {
            return NULL;
        }
        if( !Main::SingleThreaded && Main::scriptThread != NULL )
        {
            Main::scriptThread->running = false;
        }
        Renderer::drawLock = true;
        Renderer::ExitValue = ret;
        Renderer::DoExit = true;
        return Py_BuildValue( "s", "Exiting ..." );
    }

    ScriptEngine::MethodInterface::MethodDef getVersionMethod[] =
    {
        { "version", (ScriptEngine::MethodInterface::CFunction)getVersion, ScriptEngine::MethodInterface::NoArgs, NULL },
        { "componentversion", (ScriptEngine::MethodInterface::CFunction)getPluginVersion, ScriptEngine::MethodInterface::VarArgs, NULL },
        { "exit", (ScriptEngine::MethodInterface::CFunction)Exit, ScriptEngine::MethodInterface::VarArgs, NULL },
        { "quit", (ScriptEngine::MethodInterface::CFunction)Exit, ScriptEngine::MethodInterface::VarArgs, NULL },
        { "physics_lock", (ScriptEngine::MethodInterface::CFunction)lockCalculations, ScriptEngine::MethodInterface::NoArgs, NULL },
        { "physics_unlock", (ScriptEngine::MethodInterface::CFunction)unlockCalculations, ScriptEngine::MethodInterface::NoArgs, NULL },
        { "physics_stop", (ScriptEngine::MethodInterface::CFunction)lockCalculations, ScriptEngine::MethodInterface::NoArgs, NULL },
        { "physics_start", (ScriptEngine::MethodInterface::CFunction)unlockCalculations, ScriptEngine::MethodInterface::NoArgs, NULL },
        { "render_lock", (ScriptEngine::MethodInterface::CFunction)lockRenderer, ScriptEngine::MethodInterface::NoArgs, NULL },
        { "render_unlock", (ScriptEngine::MethodInterface::CFunction)unlockRenderer, ScriptEngine::MethodInterface::NoArgs, NULL },
        { "render_stop", (ScriptEngine::MethodInterface::CFunction)lockRenderer, ScriptEngine::MethodInterface::NoArgs, NULL },
        { "render_start", (ScriptEngine::MethodInterface::CFunction)unlockRenderer, ScriptEngine::MethodInterface::NoArgs, NULL },
        { NULL }
    };
}
