#include "ini.h"

namespace FileLoader
{
    Ini::Ini(std::string fn)
    {
        filename = fn;
        ini.LoadFile(fn.c_str());
    }

    Ini::Ini( const Ini& other )
    {
        memcpy( this, &other, sizeof( other ) );
    }

    Ini::~Ini()
    {

    }

    std::string Ini::getvalue(std::string section, std::string key)
    {
        const char * val = ini.GetValue(section.c_str(),key.c_str(),"");
        std::string ret = std::string(val);
        return ret;
    }

    bool Ini::hasSection(std::string sec)
    {
        return ini.GetSection(sec.c_str()) != NULL;
    }

    ClassList<std::string> * Ini::keysinsection(std::string sec)
    {
        if(!hasSection(sec))
            return NULL;

        CSimpleIniA::TNamesDepend keys;
        ini.GetAllKeys(sec.c_str(), keys);

        ClassList<std::string> * ret = new ClassList<std::string>();

        CSimpleIniA::TNamesDepend::iterator it;
        for ( it = keys.begin(); it != keys.end(); it++ )
            ret->add(std::string(it->pItem));

        return ret;
    }
}
