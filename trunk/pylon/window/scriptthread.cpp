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
    this->joinThread();
    firstRun = false;
}

void ScriptThread::run()
{
    if(firstRun)
    {
        firstRun = false;

        ScriptEngine::Begin();

        ScriptEngine::MethodInterface::Add( "calc", Main::calcLockMethods );
        ScriptEngine::MethodInterface::Add( "draw", Main::drawLockMethods );
        ScriptEngine::MethodInterface::Add( "_pylon", Main::getVersionMethod );

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

        Renderer::Timer *timer25 = new Renderer::Timer(25); // 25 cycles per second

        while(true)
        {
            ScriptEngine::Execute((const ScriptEngine::Executor)mainScript);
            timer25->sleep();
        }

        ScriptEngine::End();

        delete timer25;
    }

    if(!Main::dontremove)
    #ifdef _WIN32
        system(("del /S /Q " + Main::ext_dir + "\\*.*").c_str());
    #else
        { int ret = system(("cd " + Main::ext_dir + " && rm *.* && cd ..").c_str()); ret = 0; }
    #endif
}
