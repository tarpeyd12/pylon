#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#ifndef RENDERER_H_INCLUDED
#include "renderer.h"
#endif // RENDERER_H_INCLUDED

namespace Renderer
{
    namespace Window
    {
        namespace Size
        {
            extern int width;
            extern int height;
        }

        void Create(std::string name = "Window", int x = 640, int y = 480, int pos_x = 10, int pos_y = 10);
        void Resize(int width, int height);

        void toOrtho();
        void toFrustum();
    }
}

#endif // WINDOW_H_INCLUDED
