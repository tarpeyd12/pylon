#include "objectloader.h"

namespace ObjectLoader
{
    POGEL::OBJECT *
    newFromFile( const char * filename, const char * _type, const char * objname, POGEL::OBJECT * object, const std::string& simname )
    {
        //POGEL::OBJECT * object;

        std::string type(_type);

        if( !type.compare("pylon") )
        {
            object = ObjectLoader::pylon::newFromPylonZipFile( filename, objname, object, simname );
        }
        else
        if( !type.compare("ms3d") || !type.compare("ms3d bin") || !type.compare("MS3D bin") )
        {
            object = ObjectLoader::ms3d::newFromMs3dBinFile( filename, objname, object );
        }
        else
        if( !type.compare("objmtl") || !type.compare("objmtl text") || !type.compare("OBJMTL text") )
        {
            object = ObjectLoader::objmtl::newFromObjMtlTextFile( filename, objname, object );
        }
        else
        {
            object = NULL;
        }

        return object;
    }
}
