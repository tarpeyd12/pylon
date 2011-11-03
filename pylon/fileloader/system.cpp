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
                return 0;
            }

            int removeDir(std::string dir)
            {
                return 0;
            }

            int clearDir(std::string dir)
            {
                if(!dir.length())
                {
                    std::cout << "Cannot remove files from directory: \"\"" << std::endl;
                    return -1;
                }

                #ifdef _WIN32
                    system(("del /S /Q " + dir + "\\*.*").c_str());
                    return 0;
                #else
                    int ret = system(("cd " + dir + " && rm --recursive * && cd ..").c_str());
                    return ret;
                #endif
            }

        }

        namespace Files
        {

            int remove(std::string fileName)
            {
                #ifdef _WIN32
                    system((std::string("del /Q ") + fileName).c_str());
                    return 0;
                #else
                    int ret = system((std::string("rm ") + fileName).c_str());
                    return ret;
                #endif
            }

        }
    }
}
