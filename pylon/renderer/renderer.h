#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include "../pogel/pogel.h"
#include "../lists/lists.h"
#include "../fileloader/fileloader.h"

#ifndef TIMER_H_INCLUDED
#include "timer.h"
#endif // TIMER_H_INCLUDED

namespace Renderer
{
    extern Timing::Timer *timer30;

    extern bool HaltPhysics;

    extern bool SingleThreaded;
    extern void (*SciptCall)(void);

    extern bool drawLock;

    void Init();

    void Idle();

    void Display();

    void BuildImages();
}

#include "draw.h"
#include "camera.h"
#include "mouse.h"
#include "window.h"
#include "key.h"
#include "cmd.h"
#include "physics.h"
#include "quad.h"
#include "hud.h"
#include "light.h"

#endif // RENDERER_H_INCLUDED
