#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

namespace Renderer
{
    namespace Mouse
    {
        extern volatile int X;
        extern volatile int Y;
        extern volatile int static_x;
        extern volatile int static_y;
        extern volatile int button;
        extern volatile int state;

        extern volatile int prev_x;
        extern volatile int prev_y;

        void Rotation();
        void Translation();

        void Moved(int x, int y);
        void Clicked(int button, int state, int x, int y);
    }
}


#endif // MOUSE_H_INCLUDED
