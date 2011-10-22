#include "main.h"

#include "versionheaders.h"

void _atExit()
{
    // cleanup
    Renderer::drawLock = true;

    if(!Main::SingleThreaded)
    {
        if(Main::calcThread != NULL)
        {
            cout << "Stopping Physics Thread ...\t";
            Main::calcLock = true;
            sleep(1);
            delete Main::calcThread;
            Main::calcThread = NULL;
            cout << "OK" << endl;
        }
    }

    if(Main::scriptThread != NULL)
    {
        cout << "Stopping Scripting Thread ...\t";
        Main::scriptThread->running = false;
        sleep(1);
        delete Main::scriptThread;
        Main::scriptThread = NULL;
        cout << "OK" << endl;
    }
}

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

    // cleanup is done with the atexit(_atExit); call to _atExit() above.

    // goodby and good riddance
    return EXIT_SUCCESS;
}
