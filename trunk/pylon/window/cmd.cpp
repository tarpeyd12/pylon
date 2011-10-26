#include "main.h"

namespace Main
{
    void getCMD(int argc, char *argv[])
    {

        pylon_archive = "rc.pylon"; // the default filename

        for( unsigned int i = 0 ; i < (unsigned int)argc ; i++ )
        {
            std::string curarg(argv[i]);
            if( false )
            { }
            else
            if( !curarg.compare("-f") )
            {
                i++;
                pylon_archive = std::string(argv[i]);
                continue;
            }
            #if defined(PYLON_DEBUG_VERSION) || defined(PYLON_DEV_VERSION)
            else
            if( !curarg.compare("-dnrm") )
            {
                dontremove = true;
                continue;
            }
            else
            if( !curarg.compare("-usedirdata") )
            {
                noarchiving = true;
                dontremove = true;
                continue;
            }
            else
            if( !curarg.compare("-usedir") )
            {
                forced_dir = std::string(argv[++i]);
                forcedir = true;
                noarchiving = true;
                dontremove = true;
                continue;
            }
            else
            if( !curarg.compare("-nolimit") )
            {
                Renderer::Timing::noTiming = true;
                continue;
            }
            #endif
            else
            if( !curarg.compare("-forcedir") || !curarg.compare("-dir") )
            {
                forcedir = true;
                forced_dir = std::string(argv[++i]);
                continue;
            }
            else
            if(
                !curarg.compare("-version") ||
                !curarg.compare("?") ||
                !curarg.compare("help") ||
                !curarg.compare("-help") ||
                !curarg.compare("-about")
            )
            {
                printVersion();
                cout << endl;
                if(!curarg.compare("?") || !curarg.compare("help") || !curarg.compare("-help"))
                    Main::printHelp();
                exit(0);
            }
            else
            if( !curarg.compare("-forcesingle") )
            {
                Main::SingleThreaded = Renderer::SingleThreaded = true;
                continue;
            }
            else
            { }
        }

        FileLoader::__ar_extract_init(noarchiving,dontremove,forcedir,forced_dir);

        if(forcedir)
        {
            FileLoader::System::Dir::changeDir(forced_dir);
        }

        if(POGEL::hasproperty(POGEL_DEBUG))
        {
            Main::printVersion();
        }
    }
}