#include "main.h"

namespace Main
{
    void getCMD(int argc, char *argv[])
    {
        pylon_archive = "rc.pylon";

        for(int i = 0; i < argc; i++)
        {
            std::string curarg(argv[i]);
            if(curarg.compare("-f") == 0)
            {
                i++;
                pylon_archive = std::string(argv[i]);
                continue;
            }
            #if defined(PYLON_DEBUG_VERSION) || defined(PYLON_DEV_VERSION)
            else
            if(curarg.compare("-dnrm") == 0)
            {
                dontremove = true;
                continue;
            }
            #endif
            else
            if(curarg.compare("-forcedir") == 0 || curarg.compare("-dir") == 0)
            {
                forcedir = true;
                forced_dir = std::string(argv[++i]);
                continue;
            }
            #if defined(PYLON_DEBUG_VERSION) || defined(PYLON_DEV_VERSION)
            else
            if(curarg.compare("-usedirdata") == 0)
            {
                noarchiving = true;
                dontremove = true;
                continue;
            }
            else
            if(curarg.compare("-usedir") == 0)
            {
                forced_dir = std::string(argv[++i]);
                forcedir = true;
                noarchiving = true;
                dontremove = true;
                continue;
            }
            #endif
            else
            if(
                curarg.compare("-version") == 0 ||
                curarg.compare("?") == 0 ||
                curarg.compare("help") == 0 ||
                curarg.compare("-help") == 0 ||
                curarg.compare("-about") == 0
            )
            {
                printVersion();
                cout << endl;
                if(curarg.compare("?") == 0 || curarg.compare("help") == 0 || curarg.compare("-help") == 0)
                    Main::printHelp();
                exit(0);
            }
            else
            if(curarg.compare("-forcesingle") == 0)
            {
                Main::SingleThreaded = Renderer::SingleThreaded = true;
                continue;
            }
            else { }
        }

        FileLoader::__ar_extract_init(noarchiving,dontremove,forcedir,forced_dir);

        if(forcedir)
            FileLoader::System::Dir::changeDir(forced_dir);

        if(POGEL::hasproperty(POGEL_DEBUG))
            Main::printVersion();
    }
}
