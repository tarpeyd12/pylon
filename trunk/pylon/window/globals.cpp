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

    std::string VersionStringNoOS = std::string(AutoVersion::_FULLVERSION_STRING) + std::string(AutoVersion::_STATUS_SHORT);

    #if defined(WINDOWS) || defined(_WIN32)
        #if defined(_WIN64)
            std::string VersionString = VersionStringNoOS + "_win64";
        #else
            std::string VersionString = VersionStringNoOS + "_win32";
        #endif
    #elif defined(APPLE) || defined(_APPLE)
    std::string VersionString = VersionStringNoOS + "_mac";
    #elif defined(LINUX) || defined(_LINUX) || defined(linux)
    std::string VersionString = VersionStringNoOS + "_linux";
    #elif defined(UNIX) || defined(_UNIX) || defined(unix)
    std::string VersionString = VersionStringNoOS + "_unix";
    #else
    std::string VersionString = VersionStringNoOS + "_other";
    #endif

    bool calcLock = false;

    CalcThread *calcThread;
    ScriptThread *scriptThread;
}
