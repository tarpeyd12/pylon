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

#ifndef TIMER_H_INCLUDED
#include "timer.h"
#endif // TIMER_H_INCLUDED

namespace Renderer
{
    extern POGEL::POINT camrot;
    extern POGEL::POINT prot;
    extern POGEL::POINT campos;
    extern POGEL::POINT ppos;

    extern Timer *timer30;

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
#include "quad.h"
#include "hud.h"

#endif // RENDERER_H_INCLUDED
