#include "main.h"

#include "versionheaders.h"

/* Program entry point */

int main(int argc, char *argv[])
{
    Main::findVersion();

    Renderer::CMD::get(argc, argv);

    Main::getCMD(argc, argv);

    Main::Init();

    Renderer::Init();

    Main::scriptThread = new ScriptThread();
    Main::calcThread = new CalcThread();

    glutMainLoop();

    return EXIT_SUCCESS;
}
