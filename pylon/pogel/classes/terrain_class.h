#ifndef _TERRAIN_CLASS_H
#define _TERRAIN_CLASS_H

namespace POGEL {
class TERRAIN;
}

#include "object_class.h"
#include "point_class.h"
#include "object_funcs.h"
#include "image_class.h"
#include "../templates/classlist_template.h"

class POGEL::TERRAIN : public POGEL::OBJECT {
    private:
        unsigned int properties;
    protected:
        POGEL::IMAGE* heightMap;

        CLASSLIST<POGEL::IMAGE*> terrainTextures;

        float  widthScale;
        float  depthScale;
        float heightScale;
    public:
        TERRAIN();

        ~TERRAIN();

        int generate(POGEL::IMAGE* hm, CLASSLIST<POGEL::IMAGE*> tt);
        int generate(std::string   hm, CLASSLIST<POGEL::IMAGE*> tt);
        int generate(POGEL::IMAGE* hm, CLASSLIST<std::string>   tt);
        int generate(std::string   hm, CLASSLIST<std::string>   tt);

        void setScale(float hs, float ws=1.0f, float ds=1.0f);

        PROPERTIES_METHODS;

#endif /* _TERRAIN_CLASS_H */
