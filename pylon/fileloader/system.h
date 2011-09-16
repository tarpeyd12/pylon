#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#ifndef FILELOADER_H_INCLUDED
#include "fileloader.h"
#endif // FILELOADER_H_INCLUDED

namespace FileLoader
{
    namespace System
    {
        namespace Dir
        {
            int changeDir(std::string);
            int makeDir(std::string);
            int removeDir(std::string);
            int clearDir(std::string);
        }

        namespace Files
        {
            int remove(std::string);
            //int removeBatch();
            int copy(std::string,std::string);
        }
    }
}

#endif // SYSTEM_H_INCLUDED
