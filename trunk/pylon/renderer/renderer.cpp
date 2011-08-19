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
    // do not tamper with camrot, prot, campos nor ppos.
    POGEL::POINT camrot;
    POGEL::POINT prot;

    POGEL::POINT campos;
    POGEL::POINT ppos;

    POGEL::OBJECT* bob;
    ObjectLoader::Object::_BaseObject* gr;

    Renderer::Timer* timer30;

    // do not tamper with drawLock
    bool drawLock = false;

    void Idle()
    {
        glutPostRedisplay();
    }

    void Incriment()
    {
        for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
        {
            if(!Renderer::Physics::simulations[i]->inc())
                continue;
            if(Renderer::Physics::simulations[i]->isdyn())
                static_cast<POGEL::PHYSICS::DYNAMICS*>(Renderer::Physics::simulations[i]->getSim())->increment();
            else
                static_cast<POGEL::PHYSICS::SIMULATION*>(Renderer::Physics::simulations[i]->getSim())->increment();
        }
    }
}
