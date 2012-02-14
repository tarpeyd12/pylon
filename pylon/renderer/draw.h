#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#ifndef RENDERER_H_INCLUDED
#include "renderer.h"
#endif // RENDERER_H_INCLUDED

#include "physics.h"

namespace Renderer
{
    namespace Draw
    {

        void Draw();

        void PerfectDraw();

        void SimpleDraw();

    }
}

#endif // DRAW_H_INCLUDED
