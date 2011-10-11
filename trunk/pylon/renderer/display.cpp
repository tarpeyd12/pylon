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

        //glTranslatef(campos.x,campos.y,campos.z);
        glRotatef( Renderer::Camera::camrot.x,  1.0f, 0.0f, 0.0f );
        glRotatef( Renderer::Camera::camrot.y,  0.0f, 1.0f, 0.0f );
        glRotatef( Renderer::Camera::camrot.z,  0.0f, 0.0f, 1.0f );
        glTranslatef(
                     Renderer::Camera::campos.x,
                     Renderer::Camera::campos.y,
                     Renderer::Camera::campos.z
                     );

        if(Renderer::SingleThreaded)
        {
            if(!Renderer::HaltPhysics)
                Renderer::Incriment();
            if(Renderer::SciptCall != NULL)
                Renderer::SciptCall();
            else
                exit(-1);
        }

        Renderer::Physics::Draw();

        Renderer::Window::toOrtho();

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        //glEnable( GL_ALPHA_TEST );
        //glAlphaFunc( GL_GREATER, 0.5f );

        Renderer::HUD::updateQuadCycle();
        Renderer::HUD::removeQuadCycle();
        Renderer::HUD::addQuadCycle();
        Renderer::HUD::clearQuadsCycle();

        Renderer::HUD::draw();

        glutSwapBuffers();

        Renderer::Window::toFrustum();

        Renderer::BuildImages();

        Renderer::timer30->sleep();
    }
}
