#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#ifndef RENDERER_H_INCLUDED
#include "renderer.h"
#endif // RENDERER_H_INCLUDED

namespace Renderer
{
    namespace Camera
    {
        extern POGEL::POINT camrot;
        extern POGEL::POINT prot;
        extern POGEL::POINT campos;
        extern POGEL::POINT ppos;

        POGEL::VECTOR GetCamDirection();
    }
}

#endif // CAMERA_H_INCLUDED
