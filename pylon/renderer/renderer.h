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
#include "../objectloader/objectloader.h"

#include "timer.h"

namespace Renderer
{
    extern Timing::Timer *timer30;

    extern volatile bool DoExit;
    extern volatile int ExitValue;

    extern volatile bool HaltPhysics;

    extern bool SingleThreaded;
    extern void (*SciptCall)(void);

    extern volatile bool drawLock;

    extern Threads::Mutex drawLockMutex;
    extern Threads::Mutex calcLockMutex;

    //extern POGEL::OBJECT * bob;

    void Init();

    void Idle();

    void Display();

    void BuildImage(unsigned int);
    void BuildImages();
    void BuildAllImages();

    POGEL::IMAGE* requestImage(std::string);
}

#include "camera.h"
#include "draw.h"
#include "mouse.h"
#include "window.h"
#include "key.h"
#include "cmd.h"
#include "quad.h"
#include "hud.h"
#include "light.h"
#include "physics.h"
#include "subrenderer.h"
#include "selection.h"


#endif // RENDERER_H_INCLUDED
