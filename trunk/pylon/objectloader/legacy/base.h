#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

//#include "objectloader.h"

#include "../../scriptengine/scriptengine.h"
#include "../../pogel/pogel.h"
#include "../../fileloader/fileloader.h"

#include "keyframelist.h"

namespace ObjectLoader
{
    class _Base
    {
        public:
            std::string Name;
            POGEL::COLOR Color;
            POGEL::POINT Origin;
            POGEL::POINT Rotation;
            POGEL::POINT Scale;
            POGEL::POINT Translate;
            unsigned int Constraints;
            POGEL::POINT OrgnLimitsNeg;
            POGEL::POINT OrgnLimitsPos;
            POGEL::POINT RotnLimitsNeg;
            POGEL::POINT RotnLimitsPos;
            unsigned int DisplayMode;
            unsigned int ShowObject;
            unsigned int SolidColor;
            unsigned int RenderMode;
            unsigned int CastsShadows;
            unsigned int ReceivesShadows;
            unsigned int EnableLighting;
            std::string MaterialName;
            unsigned int NumTextures;
            //CLASSLIST<> _Textures;
            std::string GLSLShader;
            AnimKeyFrame *_Animation_stuff;
        /* constructors */
            _Base();
            _Base(std::string);
            virtual ~_Base();
    };
}
#endif // BASE_H_INCLUDED
