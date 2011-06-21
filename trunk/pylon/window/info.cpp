#include "main.h"

#include "versionheaders.h"

namespace Main
{
    void printVersion()
    {
        cout << "Pylon_" << VersionString << endl;
        cout << "  Pogel_" << std::string(PogelAutoVersion::FULLVERSION_STRING) + " " + std::string(PogelAutoVersion::STATUS) << endl;
        cout << "  FileLoader_" << std::string(FileLoaderAutoVersion::FULLVERSION_STRING) + " " + std::string(FileLoaderAutoVersion::STATUS) << endl;
        cout << "  ScriptEngine_" << std::string(ScriptEngineAutoVersion::FULLVERSION_STRING) + " " + std::string(ScriptEngineAutoVersion::STATUS) << endl;
        cout << "  Renderer_" << std::string(RendererAutoVersion::FULLVERSION_STRING) + " " + std::string(RendererAutoVersion::STATUS) << endl;
        cout << "  Threads_" << std::string(ThreadsAutoVersion::FULLVERSION_STRING) + " " + std::string(ThreadsAutoVersion::STATUS) << endl;
        cout << "  pogelInterface_" << std::string(pogelInterfaceAutoVersion::FULLVERSION_STRING) + " " + std::string(pogelInterfaceAutoVersion::STATUS) << endl;
        cout << "  ObjectLoader_" << std::string(ObjectLoaderAutoVersion::FULLVERSION_STRING) + " " + std::string(ObjectLoaderAutoVersion::STATUS) << endl;
        cout << "Created by: Dean Tarpey" << endl;
        cout << "http://pylon.googlecode.com/" << endl;
    }

    void printHelp()
    {
        cout << "Ussage:" << endl;
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
        #endif
        cout << "    -version                 prints the versions" << endl;
        cout << "    ?                        this help menu" << endl;
        cout << endl;
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
