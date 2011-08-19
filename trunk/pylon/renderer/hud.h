#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include "quad.h"

#define     NUM_QUAD_SLOTS      4096

namespace Renderer
{
    namespace HUD
    {
        extern Renderer::Quad* quadList[NUM_QUAD_SLOTS];
        extern unsigned int lastKnownQuad; // = 0

        extern int quadDeletionQueue[NUM_QUAD_SLOTS];
        extern unsigned int lastQuadDeletionQueue; // = 0

        extern bool clearNextCycle; // = false

        void Init();

        void Clear();

        int addQuad(Renderer::Quad*);
        int updateQuad(Renderer::Quad*,int);
        int removeQuad(unsigned int);

        int removeQuadCycle();

        int checkQuad(unsigned int);

        void draw();
    }
}

#endif // HUD_H_INCLUDED
