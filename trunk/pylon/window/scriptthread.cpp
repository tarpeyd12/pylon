#include "main.h"

ScriptEngine::MethodInterface::Object* lockCalculations( ScriptEngine::MethodInterface::Object* )
{
    if(!calcLock)
    {
        calcLock = true;
        calcThread->joinThread();
    }
    Py_RETURN_NONE;
}

ScriptEngine::MethodInterface::Object* unlockCalculations( ScriptEngine::MethodInterface::Object* )
{
    if(calcLock)
    {
        calcLock = false;
        calcThread->startThread();
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

void* Scripts(void* arg)
{
    bool firstrun = (bool)arg;
    if(firstrun)
    {
        ScriptEngine::Begin();
        ScriptEngine::MethodInterface::Add( "calc", calcLockMethods );
        ScriptEngine::MethodInterface::Add( "draw", drawLockMethods );
        pogelInterface::Init();
        ScriptEngine::Execute(FileLoader::totalfile(init_py));
        if(!dontremove)
        #ifdef _WIN32
            system(("del /Q " + init_py).c_str());
        #else
            system(("rm " + init_py).c_str());
        #endif
    }
    else
    {
        std::string mainScriptData = FileLoader::totalfile(main_py);
        if(!dontremove)
        #ifdef _WIN32
            system(("del /Q " + main_py).c_str());
        #else
            system(("rm " + main_py).c_str());
        #endif
        if(mainScriptData.length() == 0)
            cout << "no main data." << endl;
        ScriptEngine::Executor mainScript(mainScriptData);
        float lastdur = POGEL::GetTimePassed();
        while(true)
        {
            //usleep(1000);
            ScriptEngine::Execute((const ScriptEngine::Executor)mainScript);
            float curdur = POGEL::GetTimePassed();
            if(1.0/(curdur-lastdur) > 25)
                usleep(1000000/25.0-(curdur - lastdur));
            else if(curdur == lastdur)
                usleep(1000000/25);
            //cout << 1/(curdur-lastdur) << endl;
            lastdur = POGEL::GetTimePassed();
        }
        ScriptEngine::End();
    }
    if(!dontremove)
    #ifdef _WIN32
        system(("del /S /Q " + ext_dir + "\\*.*").c_str());
    #else
        system(("cd " + ext_dir + " && rm *.* && cd ..").c_str());
    #endif
    pthread_exit(NULL);
}
