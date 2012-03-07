#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include "renderer.h"

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
