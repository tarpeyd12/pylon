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
    //if(Threads::getNumCores() > 2) this->setAffinity(3);
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
    running = false;
    usleep(100000);

    /*if( mainScript )
    {
        delete mainScript;
    }
    mainScript = NULL;
    ScriptEngine::Finalize();*/

    if(!Main::SingleThreaded)
    {
        /*try
        {
            this->cancelThread();
        }
        catch(int e)
        {
            cout << "Unable to Cancel the Scripting Thread. err:" << e << endl;
        }*/

        try
        {
            this->joinThread();
        }
        catch(int e)
        {
            cout << "Unable to Join the Scripting Thread. err:" << e << endl;
        }
    }
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
        //FileLoader::System::Dir::clearDir(Main::ext_dir);
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

    ScriptEngine::MethodInterface::Add( "_pylon_calc", Main::calcLockMethods );
    ScriptEngine::MethodInterface::Add( "_pylon_draw", Main::drawLockMethods );
    ScriptEngine::MethodInterface::Add( "_pylon", Main::getVersionMethod );

    pogelInterface::Init();

    std::string initScriptData = FileLoader::totalfile(Main::init_py);

    if(initScriptData.length() == 0)
    {
        cout << "ERROR: no init data." << endl;
        exit(-1);
    }

    if(!Main::dontremove)
        FileLoader::System::Files::remove(Main::init_py);

    mainScriptData = FileLoader::totalfile(Main::main_py);

    if(!Main::dontremove)
        FileLoader::System::Files::remove(Main::main_py);

    if(mainScriptData.length() == 0)
    {
        cout << "ERROR: no main data." << endl;
        exit(-1);
    }

    ScriptEngine::Executor("import pylon\n").Execute();
    ScriptEngine::Executor("import _pylon\n").Execute();
    ScriptEngine::Executor("import _pylon_calc\n").Execute();
    ScriptEngine::Executor("import _pylon_draw\n").Execute();

    // I am calling this the 'StoneBug'
    // start StoneBug fix

    /* this is to compensate for a bug no clue where, mostly when pylon is called
     * within another program. May also be a bug in pogel, or how pylon uses
     * pogel this is somewhat tricky, some times no dummy simulations are
     * needed because they cause the problem, some times more are needed.
     * the command line option "-numsim <num>" is used to set the number of
     * simulations, default is 2, the command line option is undocumented.
     */

    if(POGEL::hasproperty(POGEL_DEBUG) || Main::SingleThreaded || POGEL::hasproperty(POGEL_LABEL) || Main::numDummySimulations)
    {
        unsigned int max = Main::numDummySimulations ? Main::numDummySimulations : 2;
        for(unsigned int i = 0; i < max; i++)
        {
            char *pcNum = POGEL::string("%u", i);
            ScriptEngine::Executor("import pylon\npylon.addsimulation('NullSimulation_" + std::string(pcNum) + "',False)").Execute();
            delete pcNum;
        }
    }

    // end StoneBug fix

    try
    {
        ScriptEngine::Executor(initScriptData).Execute();
    }
    catch(int e)
    {
        cout << "ERROR: Initialization script failed: " << e << endl;
        exit(e);
    }

    //mainScript = new ScriptEngine::Executor(mainScriptData);
    mainScript = new ScriptEngine::InterpreterThread( new ScriptEngine::Executor(mainScriptData) );
    //mainScript = new ScriptEngine::SubInterpreter( new ScriptEngine::Executor(mainScriptData) );
}

void ScriptThread::MainRun()
{
    Renderer::Timing::Timer *timer = new Renderer::Timing::Timer(25,"Scripts"); // 25 cycles per second

    while(running)
    {
        timer->sleep();

        try
        {
            mainScript->Execute();
        }
        catch(int e)
        {
            cout << "ERROR: Main-Loop script failed: " << e << endl;
            exit(e);
        }
    }

    delete timer;

    running = false;

    //ScriptEngine::Finalize();
}

void ScriptThread::SingleCall()
{
    mainScript->Execute();
}

void ScriptCallFunction()
{
    if(Main::scriptThread)
    {
        Main::scriptThread->SingleCall();
    }
}
