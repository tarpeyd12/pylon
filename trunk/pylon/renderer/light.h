#ifndef RENDERER_LIGHT_H_INCLUDED
#define RENDERER_LIGHT_H_INCLUDED

#ifndef RENDERER_H_INCLUDED
#include "renderer.h"
#endif

//#include "../pogel/pogel.h"

#define glLight(n) ( GL_LIGHT0 + n )

#define MAXNUMLIGHTS    8

namespace Renderer
{
    namespace Lighting
    {

        class Light
        {
            public:

                POGEL::POINT position;
                POGEL::COLOR ambient;
                POGEL::COLOR diffuse;
                POGEL::COLOR specular;

                // weather it draw()s before or after camera transforms.
                // true: before, false: after, default: false
                bool inCameraSpace;

                int lightNumber; // from 0 to (MAXNUMLIGHTS-1), -1 is default, do not initialize, will be set later

                Light();
                Light(POGEL::POINT, POGEL::COLOR, POGEL::COLOR, POGEL::COLOR);
                Light(POGEL::POINT, POGEL::COLOR, POGEL::COLOR, POGEL::COLOR, bool);
                virtual ~Light();

                void draw();

                void setPosition(POGEL::POINT);
                void setAmbient(POGEL::COLOR);
                void setDiffuse(POGEL::COLOR);
                void setSpecular(POGEL::COLOR);
                void setCameraSpace(bool);

        };

        extern Renderer::Lighting::Light Lights[MAXNUMLIGHTS];

    }
}

/*
#if defined(glLight)
#undef glLight
#endif
*/

#endif // RENDERER_LIGHT_H_INCLUDED
