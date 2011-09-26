#include "renderer.h"

#ifdef _POSIX_C_SOURCE
#undef _POSIX_C_SOURCE
#endif
#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#endif

#include "../objectloader/objectloader.h"

#include "hud.h"

namespace Renderer
{
    // do not edit
    // *******************************
    POGEL::POINT camrot;
    POGEL::POINT prot;

    POGEL::POINT campos;
    POGEL::POINT ppos;

    POGEL::OBJECT* bob;
    ObjectLoader::Object::_BaseObject* gr;

    Renderer::Timing::Timer* timer30;

    bool HaltPhysics = false;

    bool SingleThreaded = false;
    void (*SciptCall)(void) = NULL;

    // do not tamper with drawLock
    bool drawLock = false;

    // *******************************

    void Idle()
    {
        glutPostRedisplay();
    }

    void Incriment()
    {
        for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
        {
            if(Renderer::Physics::simulations[i]->inc())
            {
                if(Renderer::Physics::simulations[i]->isdyn())
                {
                    POGEL::PHYSICS::DYNAMICS* sim = static_cast<POGEL::PHYSICS::DYNAMICS*>(Renderer::Physics::simulations[i]->getSim());
                    if(sim->numobjs())
                        sim->increment();
                }
                else
                {
                    POGEL::PHYSICS::SIMULATION* sim = static_cast<POGEL::PHYSICS::SIMULATION*>(Renderer::Physics::simulations[i]->getSim());
                    if(sim->numobjs())
                        sim->increment();
                }
            }
        }
    }
}
