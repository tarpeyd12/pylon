#include "threads.h"

namespace Threads
{

    int getNumCores() {
        #if defined(WINDOWS) || defined(_WIN32) || defined(_WIN64)
            #include <windows.h>
            SYSTEM_INFO sysinfo;
            GetSystemInfo(&sysinfo);
            return sysinfo.dwNumberOfProcessors;
        #elif defined(APPLE) || defined(_APPLE) || defined(_APPLE_) || defined(__APPLE__)
            #include <sys/param.h>
            #include <sys/sysctl.h>
            int nm[2];
            size_t len = 4;
            uint32_t count;
            nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
            sysctl(nm, 2, &count, &len, NULL, 0);
            if(count < 1) {
                nm[1] = HW_NCPU;
                sysctl(nm, 2, &count, &len, NULL, 0);
                if(count < 1) { count = 1; }
            }
            return count;
        #else
            #include <unistd.h>
            return sysconf(_SC_NPROCESSORS_ONLN);
        #endif
    }
}
