#include "main.h"

#include "mainscriptdefs.h"

#include "scriptthread.h"

ScriptThread::ScriptThread()
{
    firstRun = true;
    this->run();
    this->startThread();
}

ScriptThread::ScriptThread(bool st)
{
    firstRun = true;
    if(st)
    {
        Renderer::SciptCall = ScriptCallFunction;
    }
    this->FirstRun();
}

ScriptThread::~ScriptThread()
{
    if(!Main::SingleThreaded)
        this->joinThread();
    ScriptEngine::Finalize();
    firstRun = false;
}

void ScriptThread::run()
{
    if(firstRun)
    {
        this->FirstRun();
    }
    else
    {
        this->MainRun();
    }

    if(!Main::dontremove)
        FileLoader::System::Dir::clearDir(Main::ext_dir);
}

void ScriptThread::FirstRun()
{
    firstRun = false;

    ScriptEngine::Initialize();

    ScriptEngine::MethodInterface::Add( "calc", Main::calcLockMethods );
    ScriptEngine::MethodInterface::Add( "draw", Main::drawLockMethods );
    ScriptEngine::MethodInterface::Add( "_pylon", Main::getVersionMethod );

    pogelInterface::Init();

    std::string initScriptData = FileLoader::totalfile(Main::init_py);

    if(!Main::dontremove)
        FileLoader::System::Files::remove(Main::init_py);

    mainScriptData = FileLoader::totalfile(Main::main_py);

    if(!Main::dontremove)
        FileLoader::System::Files::remove(Main::main_py);
    if(mainScriptData.length() == 0)
    {
        cout << "no main data." << endl;
        exit(-1);
    }

    ScriptEngine::Execute(ScriptEngine::Executor(initScriptData));

    mainScript = new ScriptEngine::Executor(mainScriptData);
}

void ScriptThread::MainRun()
{
    Renderer::Timer *timer25 = new Renderer::Timer(25); // 25 cycles per second

    while(true)
    {
        ScriptEngine::Execute((const ScriptEngine::Executor)*mainScript);
        timer25->sleep();
    }

    ScriptEngine::Finalize();

    delete timer25;
}

void ScriptThread::SingleCall()
{
    ScriptEngine::Execute((const ScriptEngine::Executor)*mainScript);
}

void ScriptCallFunction()
{
    if(Main::scriptThread)
        Main::scriptThread->SingleCall();
}
