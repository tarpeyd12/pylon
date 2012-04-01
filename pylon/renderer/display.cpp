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
            POGEL::SetFramerateThrotle(POGEL::GetSecondsPerFrame());

            if(!Renderer::HaltPhysics)
                Renderer::Physics::Incriment();
            if(Renderer::SciptCall != NULL)
                Renderer::SciptCall();
            else
            {
                std::cout << "Renderer::SciptCall has derefferenced to NULL. Exiting..." << std::endl;
                exit(-1);
            }
        }

        if(Renderer::drawLock)
            return;

        Renderer::RenderAllSubRenderers();

        glClearColor(.5,.5,.5,0.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        Renderer::Window::toFrustum();

        POGEL::IncrementFps();
        if(POGEL::frames%10 == 0)
            POGEL::PrintFps();

        //glTranslatef(campos.x,campos.y,campos.z);
        glRotatef( Renderer::Camera::camrot.x,  1.0f, 0.0f, 0.0f );
        glRotatef( Renderer::Camera::camrot.y,  0.0f, 1.0f, 0.0f );
        glRotatef( Renderer::Camera::camrot.z,  0.0f, 0.0f, 1.0f );
        glTranslatef(
                     Renderer::Camera::campos.x,
                     Renderer::Camera::campos.y,
                     Renderer::Camera::campos.z
                     );


        //Renderer::Draw::SimpleDraw();
        Renderer::Draw::Draw();
        //Renderer::Draw::PerfectDraw();

        Renderer::Window::toOrtho();

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        //glEnable( GL_ALPHA_TEST );
        //glAlphaFunc( GL_GREATER, 0.5f );

        Renderer::HUD::removeQuadCycle();
        Renderer::HUD::addQuadCycle();
        Renderer::HUD::clearQuadsCycle();
        Renderer::HUD::updateQuadCycle();

        Renderer::HUD::draw();

        glutSwapBuffers();

        Renderer::Window::toFrustum();

        if(!Renderer::drawLock)
            Renderer::timer30->sleep();
    }
}
