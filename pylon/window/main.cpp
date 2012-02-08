#include "main.h"

#include "versionheaders.h"

void _atExit();

// Program entry point
int main(int argc, char *argv[])
{
    // setup the version identifications
    Main::findVersion();

    // have the renderer parse the command line for its paramiters
    Renderer::CMD::get(argc, argv);

    // parse the command line for pylon specific paramiters
    Main::getCMD(argc, argv);

    // read the settings from the data files and initialize pylon
    Main::Init();

    // initialize the renderer
    Renderer::Init();

    // to clean stuff up at exit.
    atexit(_atExit);

    //std::cout << "Number of CPU's: " << Threads::getNumCores() << std::endl;

    if(Main::SingleThreaded)
    {
        // create scripting callbacks
        Main::scriptThread = new ScriptThread(true);
    }
    else
    {
        // start the script thread
        Main::scriptThread = new ScriptThread();

        // start the physics thread
        Main::calcThread = new CalcThread();
    }

    // and start the renderer on this thread
    glutMainLoop();

    // cleanup is done with the atexit(_atExit); call to _atExit() below.

    // goodby and good riddance
    return EXIT_SUCCESS;
}

// main exit point
void _atExit()
{
    // cleanup
    Renderer::drawLock = true;

    if(!Main::SingleThreaded && Main::calcThread != NULL)
    {
        Main::calcLock = true;
        cout << "Stopping Physics Thread ...\t";
        delete Main::calcThread;
        Main::calcThread = NULL;
        cout << "OK" << endl;
    }

    if(Main::scriptThread != NULL)
    {
        Main::scriptThread->running = false;
        cout << "Stopping Scripting Thread ...\t";
        delete Main::scriptThread;
        Main::scriptThread = NULL;
        cout << "OK" << endl;
    }
}
