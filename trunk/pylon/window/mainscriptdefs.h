#ifndef MAINSCRIPTDEFS_H_INCLUDED
#define MAINSCRIPTDEFS_H_INCLUDED

namespace Main
{
    extern ScriptEngine::MethodInterface::MethodDef calcLockMethods[];
    extern ScriptEngine::MethodInterface::MethodDef drawLockMethods[];
    extern ScriptEngine::MethodInterface::MethodDef getVersionMethod[];

    ScriptEngine::MethodInterface::Object* lockCalculations( ScriptEngine::MethodInterface::Object* );
    ScriptEngine::MethodInterface::Object* unlockCalculations( ScriptEngine::MethodInterface::Object* );

    ScriptEngine::MethodInterface::Object* lockRenderer( ScriptEngine::MethodInterface::Object* );
    ScriptEngine::MethodInterface::Object* unlockRenderer( ScriptEngine::MethodInterface::Object* );

    ScriptEngine::MethodInterface::Object* getVersion( ScriptEngine::MethodInterface::Object* );
    ScriptEngine::MethodInterface::Object* getPluginVersion(ScriptEngine::MethodInterface::Object* self, ScriptEngine::MethodInterface::Object* args);
}


#endif // MAINSCRIPTDEFS_H_INCLUDED
