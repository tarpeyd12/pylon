#include "main.h"

#include "mainscriptdefs.h"

#include "scriptthread.h"

ScriptThread::ScriptThread()
{
    firstRun = true;
    this->run();
    this->startThread();
}

ScriptThread::~ScriptThread()
{

}

void ScriptThread::run()
{
    if(firstRun)
    {
        firstRun = false;
        ScriptEngine::Begin();
        ScriptEngine::MethodInterface::Add( "calc", calcLockMethods );
        ScriptEngine::MethodInterface::Add( "draw", drawLockMethods );
        ScriptEngine::MethodInterface::Add( "_pylon", gatVersionMethod );
        pogelInterface::Init();
        ScriptEngine::Execute(FileLoader::totalfile(Main::init_py));
        if(!Main::dontremove)
        #ifdef _WIN32
            system(("del /Q " + Main::init_py).c_str());
        #else
            { int ret = system(("rm " + Main::init_py).c_str()); ret = 0; }
        #endif
    }
    else
    {
        std::string mainScriptData = FileLoader::totalfile(Main::main_py);
        if(!Main::dontremove)
        #ifdef _WIN32
            system(("del /Q " + Main::main_py).c_str());
        #else
            { int ret = system(("rm " + Main::main_py).c_str()); ret = 0; }
        #endif
        if(mainScriptData.length() == 0)
        {
            cout << "no main data." << endl;
            exit(-1);
        }
        ScriptEngine::Executor mainScript(mainScriptData);
        float lastdur = POGEL::GetTimePassed();
        while(true)
        {
            ScriptEngine::Execute((const ScriptEngine::Executor)mainScript);
            float curdur = POGEL::GetTimePassed();
            if(1.0/(curdur-lastdur) > 25)
                usleep(1000000/25.0-(curdur - lastdur));
            else if(curdur == lastdur)
                usleep(1000000/25.0);
            lastdur = POGEL::GetTimePassed();
        }
        ScriptEngine::End();
    }
    if(!Main::dontremove)
    #ifdef _WIN32
        system(("del /S /Q " + Main::ext_dir + "\\*.*").c_str());
    #else
        { int ret = system(("cd " + Main::ext_dir + " && rm *.* && cd ..").c_str()); ret = 0; }
    #endif
}
