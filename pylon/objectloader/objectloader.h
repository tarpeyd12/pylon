#ifndef OBJECTLOADER_H_INCLUDED
#define OBJECTLOADER_H_INCLUDED

#include "../scriptengine/scriptengine.h"
#include "../pogel/pogel.h"
#include "../fileloader/fileloader.h"

#include "keyframe.h"
#include "keyframelist.h"
#include "camera.h"
#include "light.h"

namespace ObjectLoader
{
    std::string getobject(std::string name, std::string type, std::string dat);
    std::string getobjectformfile(std::string name, std::string type, std::string filename);
}

#endif // OBJECTLOADER_H_INCLUDED
