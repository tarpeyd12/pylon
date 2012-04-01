#include "objectloader.h"

namespace ObjectLoader
{
    POGEL::OBJECT *
    newFromFile( const char * filename, const char * _type, const char * objname, POGEL::OBJECT * object )
    {
        //POGEL::OBJECT * object;

        std::string type(_type);

        if( !type.compare("ms3d bin") || !type.compare("MS3D bin") )
        {
            object = ObjectLoader::ms3d::newFromMs3dBinFile( filename, objname, object );
        }
        else
        {
            object = NULL;
        }

        return object;
    }
}
