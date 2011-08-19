#include "main.h"

#include "versionheaders.h"

namespace Main
{
    void printVersion()
    {
        cout << "Pylon_" << VersionString << "\n";//endl;
        cout << "  Pogel_" << std::string(PogelAutoVersion::FULLVERSION_STRING) + " " + std::string(PogelAutoVersion::STATUS) << "\n";//endl;
        cout << "  FileLoader_" << std::string(FileLoaderAutoVersion::FULLVERSION_STRING) + " " + std::string(FileLoaderAutoVersion::STATUS) << "\n";//endl;
        cout << "  ScriptEngine_" << std::string(ScriptEngineAutoVersion::FULLVERSION_STRING) + " " + std::string(ScriptEngineAutoVersion::STATUS) << "\n";//endl;
        cout << "  Renderer_" << std::string(RendererAutoVersion::FULLVERSION_STRING) + " " + std::string(RendererAutoVersion::STATUS) << "\n";//endl;
        cout << "  Threads_" << std::string(ThreadsAutoVersion::FULLVERSION_STRING) + " " + std::string(ThreadsAutoVersion::STATUS) << "\n";//endl;
        cout << "  pogelInterface_" << std::string(pogelInterfaceAutoVersion::FULLVERSION_STRING) + " " + std::string(pogelInterfaceAutoVersion::STATUS) << "\n";//endl;
        cout << "  ObjectLoader_" << std::string(ObjectLoaderAutoVersion::FULLVERSION_STRING) + " " + std::string(ObjectLoaderAutoVersion::STATUS) << "\n";//endl;
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
        #endif
        cout << "    -version                 prints the versions" << "\n";//endl;
        cout << "    ?                        this help menu" << "\n";//endl;
        cout << "\n";//endl;
    }

    void findVersion()
    {
        #if defined(PYLON_DEBUG_VERSION)
        VersionString += "_debug";
        #endif
        #if defined(PYLON_DEV_VERSION)
        VersionString += "_dev";
        #endif
    }
}
