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
    void Display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        Renderer::Window::toFrustum();

        POGEL::IncrementFps();
        if(POGEL::frames%10 == 0)
            POGEL::PrintFps();

        //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        //glEnable(GL_BLEND);
        //glDisable(GL_DEPTH_TEST);

        glTranslatef(campos.x,campos.y,campos.z);
        glRotatef( Renderer::camrot.x,  1.0f, 0.0f, 0.0f );
        glRotatef( Renderer::camrot.y,  0.0f, 1.0f, 0.0f );
        glRotatef( Renderer::camrot.z,  0.0f, 0.0f, 1.0f );
        //glTranslatef(campos.x,campos.y,campos.z);

        if(Renderer::SingleThreaded)
        {
            if(!Renderer::HaltPhysics)
                Renderer::Incriment();
            if(Renderer::SciptCall != NULL)
                Renderer::SciptCall();
            else
                exit(-1);
        }

        if(!drawLock)
        {
            for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
                if(Renderer::Physics::simulations[i]->canDraw())
                {
                    if(Renderer::Physics::simulations[i]->isdyn())
                        static_cast<POGEL::PHYSICS::DYNAMICS*>(Renderer::Physics::simulations[i]->getSim())->draw();
                    else
                        static_cast<POGEL::PHYSICS::SIMULATION*>(Renderer::Physics::simulations[i]->getSim())->draw();
                }
        }

        Renderer::Window::toOrtho();

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        //glEnable( GL_ALPHA_TEST );
        //glAlphaFunc( GL_GREATER, 0.5f );

        Renderer::HUD::updateQuadCycle();
        Renderer::HUD::removeQuadCycle();
        Renderer::HUD::addQuadCycle();

        if(Renderer::HUD::clearNextCycle)
        {
            if(POGEL::hasproperty(POGEL_DEBUG))
                cout << "Hud cleared at frame:" << POGEL::frames << endl;
            Renderer::HUD::Clear();
            Renderer::HUD::clearNextCycle = false;
        }

        Renderer::HUD::draw();

        glutSwapBuffers();

        Renderer::Window::toFrustum();

        // TODO: make the image building mechanism into a function.
        if(POGEL::imglstlen() > 0)
        {
            unsigned int i = POGEL::frames%POGEL::imglstlen();
            if(!POGEL::lstimg(i)->isbuilt())
            {
                if(!FileLoader::checkfile(POGEL::lstimg(i)->getFileID())) {
                    if(POGEL::hasproperty(POGEL_DEBUG))
                        cout << "extracting " << POGEL::lstimg(i)->getFileID() << endl;
                    FileLoader::ArchiveHandler::extractKnownFile(POGEL::lstimg(i)->getFileID());
                }
                if(FileLoader::checkfile(POGEL::lstimg(i)->getFileID()))
                {
                    if(POGEL::hasproperty(POGEL_DEBUG))
                        cout << endl << "building unbuilt image: " << POGEL::lstimg(i)->toString() << endl;
                    POGEL::lstimg(i)->loadandbuild();
                }
            }
        }

        Renderer::timer30->sleep();
    }
}
