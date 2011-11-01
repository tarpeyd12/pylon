#include "globals.h"

#include "version.h"

namespace Main
{
    std::string pylon_archive;

    std::string config_data;
    std::string init_py;
    std::string main_py;
    std::string ext_dir;
    bool dontremove = false;
    bool forcedir = false;
    bool noarchiving = false;
    std::string forced_dir = "";

    std::string VersionStringNoOS = std::string(AutoVersion::_FULLVERSION_STRING) + std::string(".") + std::string(AutoVersion::_STATUS_SHORT);

    #if defined(WINDOWS) || defined(_WIN32) || defined(_WIN64)
        #if defined(_WIN64)
            std::string VersionString = VersionStringNoOS + ".win64";
        #else
            std::string VersionString = VersionStringNoOS + ".win32";
        #endif

    #elif defined(APPLE) || defined(_APPLE) || defined(_APPLE_) || defined(__APPLE__)
    std::string VersionString = VersionStringNoOS + ".mac";

    #elif defined(LINUX) || defined(_LINUX) || defined(linux)
    std::string VersionString = VersionStringNoOS + ".linux";

    #elif defined(UNIX) || defined(_UNIX) || defined(unix)
    std::string VersionString = VersionStringNoOS + ".unix";

    #else
    std::string VersionString = VersionStringNoOS + ".other";

    #endif

    bool calcLock = false;

    CalcThread *calcThread;
    ScriptThread *scriptThread;

    bool SingleThreaded = false;
}
