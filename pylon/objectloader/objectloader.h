#ifndef OBJECTLOADER_H_INCLUDED
#define OBJECTLOADER_H_INCLUDED

//#include "../scriptengine/scriptengine.h"

#include "../pogel/pogel.h"
#include "../fileloader/fileloader.h"

namespace ObjectLoader
{
    namespace ms3d
    {
        POGEL::OBJECT * newFromMs3dBinFile( const char *, const char *, POGEL::OBJECT * );
    }

    POGEL::OBJECT * newFromFile( const char *, const char *, const char *, POGEL::OBJECT * );
}

#endif // OBJECTLOADER_H_INCLUDED
