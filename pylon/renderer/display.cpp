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
        if(Renderer::SingleThreaded)
        {
            if(!Renderer::HaltPhysics)
                Renderer::Incriment();
            if(Renderer::SciptCall != NULL)
                Renderer::SciptCall();
            else
                exit(-1);
        }

        POGEL::IncrementFps();
        if(POGEL::frames%10 == 0)
            POGEL::PrintFps();

        //Renderer::Mouse::Rotation();
        //Renderer::Mouse::Translation();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        Renderer::Window::toFrustum();

        //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        //glEnable(GL_BLEND);
        //glDisable(GL_DEPTH_TEST);

        glTranslatef(campos.x,campos.y,campos.z);
        glRotatef( Renderer::camrot.x,  1.0f, 0.0f, 0.0f );
        glRotatef( Renderer::camrot.y,  0.0f, 1.0f, 0.0f );
        glRotatef( Renderer::camrot.z,  0.0f, 0.0f, 1.0f );
        //glTranslatef(campos.x,campos.y,campos.z);
        /*if(bob != NULL)
        {
            //bob->position = POGEL::POINT();
            bob->position = gr->frame(POGEL::GetTimePassed()).getpos();
            bob->draw();
        }*/

        if(!drawLock)
        {
            for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
                if(Renderer::Physics::simulations[i]->isdyn())
                    static_cast<POGEL::PHYSICS::DYNAMICS*>(Renderer::Physics::simulations[i]->getSim())->draw();
                else
                    static_cast<POGEL::PHYSICS::SIMULATION*>(Renderer::Physics::simulations[i]->getSim())->draw();
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

        if(POGEL::imglstlen() > 0)
        {
            unsigned int i = POGEL::frames%POGEL::imglstlen();
            if(!POGEL::lstimg(i)->isbuilt())
            {
                POGEL::lstimg(i)->build();
                if(POGEL::hasproperty(POGEL_DEBUG))
                    cout << "\n"/*endl*/ << "building unbuilt image: " << POGEL::lstimg(i)->toString() << "\n";
            }
        }

        Renderer::timer30->sleep();
    }
}
