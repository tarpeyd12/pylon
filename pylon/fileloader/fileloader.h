#ifndef FILELOADER_H_INCLUDED
#define FILELOADER_H_INCLUDED

#include <string>
#include <fstream>

#include "../pogel/pogel.h"

namespace FileLoader
{
    std::string getline( std::string filename, int line );
    std::string totalfile( std::string filename );
    bool checkfile( std::string );
}

#include "unzip.h"
#include "ini.h"
#include "archivehandler.h"

#include "system.h"

#endif // FILELOADER_H_INCLUDED
