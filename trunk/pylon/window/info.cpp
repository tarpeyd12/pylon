#include "main.h"

#include "versionheaders.h"

namespace Main
{
    void printVersion()
    {
        cout << "Pylon." << VersionString << endl;
        cout << "  Pogel."          << std::string(PogelAutoVersion::_FULLVERSION_STRING)          + "." + std::string(PogelAutoVersion::_STATUS_SHORT)          << endl;
        cout << "  FileLoader."     << std::string(FileLoaderAutoVersion::_FULLVERSION_STRING)     + "." + std::string(FileLoaderAutoVersion::_STATUS_SHORT)     << endl;
        cout << "  ScriptEngine."   << std::string(ScriptEngineAutoVersion::_FULLVERSION_STRING)   + "." + std::string(ScriptEngineAutoVersion::_STATUS_SHORT)   << endl;
        cout << "  Renderer."       << std::string(RendererAutoVersion::_FULLVERSION_STRING)       + "." + std::string(RendererAutoVersion::_STATUS_SHORT)       << endl;
        cout << "  Threads."        << std::string(ThreadsAutoVersion::_FULLVERSION_STRING)        + "." + std::string(ThreadsAutoVersion::_STATUS_SHORT)        << endl;
        cout << "  pogelInterface." << std::string(pogelInterfaceAutoVersion::_FULLVERSION_STRING) + "." + std::string(pogelInterfaceAutoVersion::_STATUS_SHORT) << endl;
        cout << "  ObjectLoader."   << std::string(ObjectLoaderAutoVersion::_FULLVERSION_STRING)   + "." + std::string(ObjectLoaderAutoVersion::_STATUS_SHORT)   << endl;
        cout << "Created by Dean Tarpey" << endl;
        cout << "http://pylon.googlecode.com/" << endl;
    }

    void printHelp()
    {
        cout << "Usage:" << "\n";//endl;
        std::string cmds = "[args]";
        #if defined(WINDOWS) || defined(_WIN32)
        cout << "  pylon.exe " + cmds << endl;
        #else
        cout << "  ./pylon " + cmds << endl;
        #endif
        cout << "  args:" << endl;
        cout << "    -f [filename]            forces the archive to filename" << endl;
        cout << "    -dir [directory]         forces the search directory" << endl;
        #if defined(PYLON_DEBUG_VERSION) || defined(PYLON_DEV_VERSION)
        cout << "    -usedirdata              uses the data in the directory specified by -dir instead of the pylon archive file" << endl;
        cout << "    -dnrm                    forces no-removal of data temporaries" << endl;
        cout << "    -usedir [directory]      sets -dir with directory, -dnrm and -usedirdata" << endl;
        cout << "    -nolimit                 unlimits the thread cycleclock" << endl;
        cout << "    -bench                   for running benchmark tests, same as setting \"-nolimit\" and \"-single\"" << endl;
        #endif
        cout << "    -single                  forces a one threaded environment, physics and scripts are in the renderer loop" << endl;
        cout << "    -version                 prints the versions" << endl;
        cout << "    ?                        this help menu" << endl;
        cout << endl;
    }

    void findVersion()
    {
        #if defined(PYLON_DEBUG_VERSION)
        VersionString += ".debug";
        #endif
        #if defined(PYLON_DEV_VERSION)
        VersionString += ".dev";
        #endif
        ObjectLoader::pylon::VersionStringRaw = Main::VersionStringRaw;
    }
}
