#ifndef RENDERER_KEY_H_INCLUDED
#define RENDERER_KEY_H_INCLUDED

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

        class KeyCallback
        {
            public:
                bool remove;
                KeyCallback() { remove = false; };
                virtual ~KeyCallback() { };
                virtual void operator()( unsigned char, int, int, float ) = 0;
        };

        extern ClassList< KeyCallback* > keyDownCallBacks;
        extern ClassList< KeyCallback* > keyUpCallBacks;

        void Down(unsigned char key, int x, int y);
        void Up(unsigned char key, int x, int y);
    }
}

#endif // RENDERER_KEY_H_INCLUDED
