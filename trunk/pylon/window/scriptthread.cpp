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
    this->run();
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

    // I am calling this the 'StoneBug'
    // start StoneBug fix

    /* this is to compensate for a bug in Code::Blocks, and when pylon is called
     * within another program. May also be a bug in pogel, or how pylon uses
     * pogel this is somewhat tricky, somne times no dummy simulations are
     * needed because they cause the problem, some times two are needed, maby
     * even one, I have only tested up to 2 dummy's
     */

    //ScriptEngine::Execute(ScriptEngine::Executor("import pylon\npylon.addsimulation('NullSimulation',False)"));
    //ScriptEngine::Execute(ScriptEngine::Executor("import pylon\npylon.addsimulation('NullSimulation2',False)"));

    // end StoneBug fix

    ScriptEngine::Execute(ScriptEngine::Executor(initScriptData));

    mainScript = new ScriptEngine::Executor(mainScriptData);
}

void ScriptThread::MainRun()
{
    Renderer::Timing::Timer *timer25 = new Renderer::Timing::Timer(25,"Scripts"); // 25 cycles per second

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
