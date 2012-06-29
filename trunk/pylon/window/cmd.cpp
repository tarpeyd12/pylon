#include "main.h"

namespace Main
{
    void getCMD(int argc, char *argv[])
    {

        pylon_archive = "rc.pylon"; // the default filename

        for( unsigned int i = 0 ; i < (unsigned int)argc ; i++ )
        {
            std::string curarg(argv[i]);
            if(
                i == 1 &&
                (ScriptEngine::Parse::endsWith(curarg,".pylon") ||
                ScriptEngine::Parse::endsWith(curarg,".zip") ||
                ScriptEngine::Parse::endsWith(curarg,".zip.pylon") ||
                ScriptEngine::Parse::endsWith(curarg,".pylon.zip"))
            )
            {
                pylon_archive = curarg;
                #if defined(WINDOWS) || defined(_WIN32) || defined(_WIN64)
                int slppos = curarg.rfind("\\");
                #else
                int slppos = curarg.rfind("/");
                #endif
                if( slppos != std::string::npos )
                {
                    forcedir = true;
                    forced_dir = curarg.substr( 0, slppos );
                    pylon_archive = curarg.substr(forced_dir.length());
                    if( pylon_archive[ 0 ] == '\\' || pylon_archive[ 0 ] == '/' )
                    {
                        pylon_archive = pylon_archive.substr(1);
                    }
                }
                continue;
            }
            else
            if( !curarg.compare("-f") )
            {
                pylon_archive = std::string(argv[++i]);
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
            if( !forcedir && !curarg.compare("-usedir") )
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
            else
            if( !curarg.compare("-benchmark") || !curarg.compare("-bench") )
            {
                Main::SingleThreaded = Renderer::SingleThreaded = Renderer::Timing::noTiming = true;
                continue;
            }
            #endif
            else
            if( !forcedir && (!curarg.compare("-forcedir") || !curarg.compare("-dir")) )
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
            if( !curarg.compare("-forcesingle") || !curarg.compare("-single") )
            {
                Main::SingleThreaded = Renderer::SingleThreaded = true;
                continue;
            }
            else
            // this is purposfully left out of the help
            if( !curarg.compare("-numsim") )
            {
                sscanf(argv[++i], "%u", &Main::numDummySimulations);
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
