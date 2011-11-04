#include "system.h"

namespace FileLoader
{
    namespace System
    {
        namespace Dir
        {

            int changeDir(std::string dir)
            {
                int ret = 0;
                #ifdef _WIN32
                    ret = _chdir(dir.c_str());
                #else
                    ret = chdir(dir.c_str());
                #endif
                return ret;
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

                std::cout << "Clearing all contentents of the directory \"" << dir << "\" ..." << std::endl;

                int ret = 0;
                #ifdef _WIN32
                    ret = system(("del /S /Q " + dir + "\\*.*").c_str());
                #else
                    // this is unsafe, it cd's to the dir but only cd's up one dir instead of back to working dir.
                    //ret = system(("cd " + dir + " && rm --recursive * && cd ..").c_str());
                    // this one is safe ...
                    ret = system(("rm --recursive "+dir+"/*").c_str());
                #endif

                return ret;
            }

        }

        namespace Files
        {

            int remove(std::string fileName)
            {
                int ret = 0;
                #ifdef _WIN32
                    ret = system((std::string("del /Q ") + fileName).c_str());
                #else
                    ret = system((std::string("rm ") + fileName).c_str());
                #endif
                return ret;
            }

        }
    }
}
