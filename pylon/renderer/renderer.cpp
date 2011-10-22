#include "renderer.h"

#ifdef _POSIX_C_SOURCE
#undef _POSIX_C_SOURCE
#endif
#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#endif

//#include "../objectloader/objectloader.h"

//#include "../pogel/pogel.h"

#include "hud.h"

namespace Renderer
{
    // do not edit
    // *******************************
    POGEL::OBJECT* bob;
    //ObjectLoader::Object::_BaseObject* gr;

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

    void BuildImages()
    {
        if(POGEL::imglstlen() > 0)
        {
            unsigned int i = POGEL::frames%POGEL::imglstlen();
            if(!POGEL::lstimg(i)->isbuilt())
            {
                if(!FileLoader::checkfile(POGEL::lstimg(i)->getFileID())) {
                    if(POGEL::hasproperty(POGEL_DEBUG))
                        cout << "extracting: \"" << POGEL::lstimg(i)->getFileID() << "\"" << endl;
                    FileLoader::ArchiveHandler::extractKnownFile(POGEL::lstimg(i)->getFileID());
                }
                if(FileLoader::checkfile(POGEL::lstimg(i)->getFileID()))
                {
                    if(POGEL::hasproperty(POGEL_DEBUG))
                        cout << endl << "building unbuilt image: \"" << POGEL::lstimg(i)->toString() << "\"" << endl;
                    POGEL::lstimg(i)->loadandbuild();
                }
            }
        }
    }
}
