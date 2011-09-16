#include "system.h"

namespace FileLoader
{
    namespace System
    {
        namespace Dir
        {


            int changeDir(std::string dir)
            {
                #ifdef _WIN32
                    _chdir(dir.c_str());
                #else
                    int ret = chdir(dir.c_str()); ret = 0;
                #endif
                return 0;
            }

            int makeDir(std::string dir)
            {

            }

            int removeDir(std::string dir)
            {

            }

            int clearDir(std::string dir)
            {
                #ifdef _WIN32
                    system(("del /S /Q " + dir + "\\*.*").c_str());
                #else
                    int ret = system(("cd " + dir + " && rm *.* && cd ..").c_str()); ret = 0;
                #endif
            }

        }

        namespace Files
        {

        }
    }
}
