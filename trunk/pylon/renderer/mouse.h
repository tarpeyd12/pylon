#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#ifndef RENDERER_H_INCLUDED
#include "renderer.h"
#endif // RENDERER_H_INCLUDED

namespace Renderer
{
    namespace Mouse
    {
        extern int X;
        extern int Y;
        extern int static_x;
        extern int static_y;
        extern int button;
        extern int state;

        extern int prev_x;
        extern int prev_y;

        void Rotation();
        void Translation();

        void Moved(int x, int y);
        void Clicked(int button, int state, int x, int y);
    }
}


#endif // MOUSE_H_INCLUDED
