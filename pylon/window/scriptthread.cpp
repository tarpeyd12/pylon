#include "main.h"

#include "mainscriptdefs.h"

#include "scriptthread.h"

ScriptThread::ScriptThread()
{
    firstRun = true;
    this->run();
    running = true;
    this->startThread();
    // if the computer has more than 2 cpu's
    //  attempt to set the script thrads to cpu3
    if(Threads::getNumCores() > 2)
        this->setAffinity(3);
}

ScriptThread::ScriptThread(bool st)
{
    firstRun = true;
    running = true;
    if(st)
    {
        Renderer::SciptCall = ScriptCallFunction;
    }
    this->run();
}

ScriptThread::~ScriptThread()
{
    if(!Main::SingleThreaded)
    {
        try
        {
            this->cancelThread();
        }
        catch(int e)
        {
            cout << "Unable to Cancel the Scripting Thread. err:" << e << endl;
        }

        try
        {
            this->joinThread();
        }
        catch(int e)
        {
            cout << "Unable to Join the Scripting Thread. err:" << e << endl;
        }
    }
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

    if( !Main::dontremove )
    {
        FileLoader::System::Dir::clearDir(Main::ext_dir);
    }
}

void _atAbruptScriptInitExit()
{
    if( !Main::dontremove )
    {
        cout << "Cleaning Up ..." << endl;
        if(FileLoader::checkfile(Main::init_py))
            FileLoader::System::Files::remove(Main::init_py);
        if(FileLoader::checkfile(Main::main_py))
            FileLoader::System::Files::remove(Main::main_py);
        FileLoader::System::Dir::clearDir(Main::ext_dir);
    }
}

void ScriptThread::FirstRun()
{
    atexit(_atAbruptScriptInitExit);

    firstRun = false;

    ScriptEngine::Initialize();

    ScriptEngine::MethodInterface::Add( "calc", Main::calcLockMethods );
    ScriptEngine::MethodInterface::Add( "draw", Main::drawLockMethods );
    ScriptEngine::MethodInterface::Add( "_pylon", Main::getVersionMethod );

    pogelInterface::Init();

    std::string initScriptData = FileLoader::totalfile(Main::init_py);

    if(initScriptData.length() == 0)
    {
        cout << "no init data." << endl;
        exit(-1);
    }

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
     * pogel this is somewhat tricky, some times no dummy simulations are
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
    Renderer::Timing::Timer *timer = new Renderer::Timing::Timer(25,"Scripts"); // 25 cycles per second

    while(running)
    {
        timer->sleep();
        ScriptEngine::Execute((const ScriptEngine::Executor)*mainScript);
    }

    delete timer;

    running = false;

    //ScriptEngine::Finalize();
}

void ScriptThread::SingleCall()
{
    ScriptEngine::Execute((const ScriptEngine::Executor)*mainScript);
}

void ScriptCallFunction()
{
    if(Main::scriptThread)
    {
        Main::scriptThread->SingleCall();
    }
}
