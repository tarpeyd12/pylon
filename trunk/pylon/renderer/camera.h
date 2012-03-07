#ifndef RENDERER_CAMERA_H_INCLUDED
#define RENDERER_CAMERA_H_INCLUDED

#include "../pogel/pogel.h"

namespace Renderer
{
    namespace Camera
    {
        class Viewpoint
        {
            public:
                POGEL::POINT rotation;
                POGEL::POINT position;

                Viewpoint();
                Viewpoint(POGEL::POINT,POGEL::POINT);

                void set();
                POGEL::VECTOR GetCamDirection();
        };

        extern POGEL::POINT camrot;
        extern POGEL::POINT prot;
        extern POGEL::POINT campos;
        extern POGEL::POINT ppos;

        POGEL::VECTOR GetCamDirection();
    }
}

#endif // RENDERER_CAMERA_H_INCLUDED
