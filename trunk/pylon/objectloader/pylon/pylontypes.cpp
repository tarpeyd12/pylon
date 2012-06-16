#include "pylon.h"

namespace ObjectLoader
{
    namespace pylon
    {
        bool suportedType( const std::string& type )
        {
            if( !type.compare("object") )
            {
                return true;
            }
            else
            if( !type.compare("fractal") )
            {
                return true;
            }
            return false;
        }

        int executeArchiveType( const std::string& type, POGEL::OBJECT* object, FileLoader::Ini* ini, const std::string& location, const std::string& codeDir, const std::string& simname, const std::string& objname )
        {
            if( !type.compare("object") )
            {
                return executeObjectArchive(object,ini,location,codeDir,simname,objname);
            }
            else
            if( !type.compare("fractal") )
            {
                return executeFractalArchive(object,ini,location,codeDir,simname,objname);
            }
            return -1;
        }
    }
}
