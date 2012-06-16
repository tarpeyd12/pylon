#ifndef OBJECTLOADER_PYLON_H_INCLUDED
#define OBJECTLOADER_PYLON_H_INCLUDED

#include "../objectloader.h"

namespace ObjectLoader
{
    namespace pylon
    {
        bool suportedType( const std::string& );

        int executeArchiveType( const std::string& type, POGEL::OBJECT* object, FileLoader::Ini* ini, const std::string& location, const std::string& codeDir, const std::string& simname, const std::string& objname );

        int executeObjectArchive( POGEL::OBJECT* object, FileLoader::Ini* ini, const std::string& location, const std::string& codeDir, const std::string& simname, const std::string& objname );

        int executeFractalArchive( POGEL::OBJECT* object, FileLoader::Ini* ini, const std::string& location, const std::string& codeDir, const std::string& simname, const std::string& objname );

    }
}

#endif // OBJECTLOADER_PYLON_H_INCLUDED
