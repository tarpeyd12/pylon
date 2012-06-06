#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include "renderer.h"

namespace Renderer
{
    namespace Key
    {
        extern volatile bool keys[256];
        extern volatile float lastpressed[256];
        extern volatile float lastreleased[256];
        extern volatile int mousepospress[256][2];
        extern volatile int mouseposrelease[256][2];

        extern volatile char last;

        void Down(unsigned char key, int x, int y);
        void Up(unsigned char key, int x, int y);
    }
}

#endif // KEY_H_INCLUDED
