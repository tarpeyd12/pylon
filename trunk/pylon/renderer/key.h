#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#ifndef RENDERER_H_INCLUDED
#include "renderer.h"
#endif // RENDERER_H_INCLUDED

namespace Renderer
{
    namespace Key
    {
        extern char keys[256];

        extern char last;

        void Down(unsigned char key, int x, int y);
        void Up(unsigned char key, int x, int y);
    }
}

#endif // KEY_H_INCLUDED
