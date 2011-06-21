#include "main.h"

#include "mainscriptdefs.h"

#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../pogel/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../fileloader/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../scriptengine/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../renderer/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../threads/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../pogelscriptinterface/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../objectloader/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING

ScriptEngine::MethodInterface::Object* lockCalculations( ScriptEngine::MethodInterface::Object* )
{
    if(!Main::calcLock)
    {
        Main::calcLock = true;
        Main::calcThread->joinThread();
    }
    Py_RETURN_NONE;
}

ScriptEngine::MethodInterface::Object* unlockCalculations( ScriptEngine::MethodInterface::Object* )
{
    if(Main::calcLock)
    {
        Main::calcLock = false;
        Main::calcThread->startThread();
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
    if(!Renderer::drawLock)
    {
        Renderer::drawLock = true;
    }
    Py_RETURN_NONE;
}

ScriptEngine::MethodInterface::Object* unlockRenderer( ScriptEngine::MethodInterface::Object* )
{
    if(Renderer::drawLock)
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
    return Py_BuildValue("s", Main::VersionStringNoOS.c_str());
}

ScriptEngine::MethodInterface::Object* getPluginVersion(ScriptEngine::MethodInterface::Object* self, ScriptEngine::MethodInterface::Object* args)
{
    char* pluginName;
    if(!PyArg_ParseTuple(args, "s:getPluginVersion", &pluginName))
        return NULL;
    std::string pname(pluginName);
    if(pname.compare("pogel"))
        return Py_BuildValue("s", PogelAutoVersion::FULLVERSION_STRING);
    else
    if(pname.compare("fileloader"))
        return Py_BuildValue("s", FileLoaderAutoVersion::FULLVERSION_STRING);
    else
    if(pname.compare("scriptengine"))
        return Py_BuildValue("s", ScriptEngineAutoVersion::FULLVERSION_STRING);
    else
    if(pname.compare("renderer"))
        return Py_BuildValue("s", RendererAutoVersion::FULLVERSION_STRING);
    else
    if(pname.compare("threads"))
        return Py_BuildValue("s", ThreadsAutoVersion::FULLVERSION_STRING);
    else
    if(pname.compare("pogelinterface"))
        return Py_BuildValue("s", pogelInterfaceAutoVersion::FULLVERSION_STRING);
    else
    if(pname.compare("objectloader"))
        return Py_BuildValue("s", ObjectLoaderAutoVersion::FULLVERSION_STRING);
    else
        return Py_BuildValue("s", "0.0.0.0");
}

ScriptEngine::MethodInterface::MethodDef gatVersionMethod[] =
{
    { "version", (ScriptEngine::MethodInterface::CFunction)getVersion, ScriptEngine::MethodInterface::NoArgs, NULL },
    { "pluginversion", (ScriptEngine::MethodInterface::CFunction)getPluginVersion, ScriptEngine::MethodInterface::VarArgs, NULL },
    { NULL }
};
