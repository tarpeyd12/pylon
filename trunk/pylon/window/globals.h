#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "main.h"

#ifndef SCRIPTTHREAD_H_INCLUDED
#include "scriptthread.h"
#endif
#ifndef CALCTHREAD_H_INCLUDED
#include "calcthread.h"
#endif

namespace Main
{
    extern std::string pylon_archive;
    extern std::string config_data;
    extern std::string init_py;
    extern std::string main_py;
    extern std::string ext_dir;
    extern bool dontremove;
    extern bool forcedir;
    extern bool noarchiving;
    extern std::string forced_dir;

    extern std::string VersionStringNoOS;
    extern std::string VersionString;

    extern bool calcLock;

    extern CalcThread *calcThread;
    extern ScriptThread *scriptThread;

    extern bool SingleThreaded;
}

#endif // GLOBALS_H_INCLUDED
