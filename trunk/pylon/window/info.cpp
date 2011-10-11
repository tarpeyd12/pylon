#include "main.h"

#include "versionheaders.h"

namespace Main
{
    void printVersion()
    {
        cout << "Pylon." << VersionString << "\n";//endl;
        cout << "  Pogel." << std::string(PogelAutoVersion::_FULLVERSION_STRING) + "." + std::string(PogelAutoVersion::_STATUS_SHORT) << "\n";//endl;
        cout << "  FileLoader." << std::string(FileLoaderAutoVersion::FULLVERSION_STRING) + "." + std::string(FileLoaderAutoVersion::STATUS_SHORT) << "\n";//endl;
        cout << "  ScriptEngine." << std::string(ScriptEngineAutoVersion::FULLVERSION_STRING) + "." + std::string(ScriptEngineAutoVersion::STATUS_SHORT) << "\n";//endl;
        cout << "  Renderer." << std::string(RendererAutoVersion::FULLVERSION_STRING) + "." + std::string(RendererAutoVersion::STATUS_SHORT) << "\n";//endl;
        cout << "  Threads." << std::string(ThreadsAutoVersion::FULLVERSION_STRING) + "." + std::string(ThreadsAutoVersion::STATUS_SHORT) << "\n";//endl;
        cout << "  pogelInterface." << std::string(pogelInterfaceAutoVersion::FULLVERSION_STRING) + "." + std::string(pogelInterfaceAutoVersion::STATUS_SHORT) << "\n";//endl;
        cout << "  ObjectLoader." << std::string(ObjectLoaderAutoVersion::FULLVERSION_STRING) + "." + std::string(ObjectLoaderAutoVersion::STATUS_SHORT) << "\n";//endl;
        cout << "Created by: Dean Tarpey" << "\n";//endl;
        cout << "http://pylon.googlecode.com/" << "\n";//endl;
    }

    void printHelp()
    {
        cout << "Ussage:" << "\n";//endl;
        std::string cmds = "[args]";
        #if defined(WINDOWS) || defined(_WIN32)
        cout << "  pylon.exe " + cmds << "\n";//endl;
        #else
        cout << "  ./pylon " + cmds << "\n";//endl;
        #endif
        cout << "  args:" << "\n";//endl;
        cout << "    -f [filename]            forces the archive to filename" << "\n";//endl;
        cout << "    -dir [directory]         forces the search directory" << "\n";//endl;
        #if defined(PYLON_DEBUG_VERSION) || defined(PYLON_DEV_VERSION)
        cout << "    -usedirdata              uses the data in the directory specified by -dir instead of the pylon archive file" << "\n";//endl;
        cout << "    -dnrm                    forces no-removal of data temporaries" << "\n";//endl;
        cout << "    -usedir [directory]      sets -dir with directory, -dnrm and -usedirdata" << "\n";//endl;
        cout << "    -nolimit                 unlimits the thread cycleclock" << "\n";//endl;
        #endif
        cout << "    -forcesingle             forces a one threaded environment, physics and scripts are in the renderer loop" << "\n";//endl;
        cout << "    -version                 prints the versions" << "\n";//endl;
        cout << "    ?                        this help menu" << "\n";//endl;
        cout << "\n";//endl;
    }

    void findVersion()
    {
        #if defined(PYLON_DEBUG_VERSION)
        VersionString += ".debug";
        #endif
        #if defined(PYLON_DEV_VERSION)
        VersionString += ".dev";
        #endif
    }
}
