#include "ini.h"

namespace FileLoader
{
    Ini::Ini(std::string fn)
    {
        filename = fn;
        ini.LoadFile(fn.c_str());
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
}
