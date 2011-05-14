#ifndef OBJECTLOADER_H_INCLUDED
#define OBJECTLOADER_H_INCLUDED

#include "../pogel/pogel.h"
#include "../scriptengine/scriptengine.h"

#include "keyframe.h"

namespace ObjectLoader
{
    std::string getobject(std::string name, std::string type, std::string dat);
    std::string getobjectformfile(std::string name, std::string type, std::string filename);


}

#endif // OBJECTLOADER_H_INCLUDED