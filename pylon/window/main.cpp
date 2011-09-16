#include "main.h"

#include "versionheaders.h"

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

    // and start the renderer on theis thread
    glutMainLoop();

    // goodby and good riddance
    return EXIT_SUCCESS;
}
