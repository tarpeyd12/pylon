#ifndef CMD_H_INCLUDED
#define CMD_H_INCLUDED

#ifndef RENDERER_H_INCLUDED
#include "renderer.h"
#endif // RENDERER_H_INCLUDED

namespace Renderer
{
    namespace CMD
    {
        extern int argumentCount;
        extern char **argumentList;

        void get(int argc, char *argv[]);
    }
}

#endif // CMD_H_INCLUDED