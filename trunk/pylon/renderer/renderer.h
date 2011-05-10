#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include "../pogel/pogel.h"
#include "../fileloader/fileloader.h"

namespace Renderer
{
    extern POGEL::POINT camrot;
    extern POGEL::POINT prot;
    extern POGEL::POINT campos;
    extern POGEL::POINT ppos;

    extern float lastdur;

    extern bool drawLock;

    void Init();

    void Idle();

    void Display();

    void Incriment();
}

#include "mouse.h"
#include "window.h"
#include "key.h"
#include "cmd.h"
#include "physics.h"

#endif // RENDERER_H_INCLUDED
