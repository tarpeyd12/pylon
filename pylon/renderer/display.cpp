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

        /*if(Renderer::Mouse::state == GLUT_DOWN)
        {
            POGEL::LINE(
                        POGEL::POINT(Renderer::Mouse::X,Renderer::Mouse::Y,0),
                        POGEL::POINT(Renderer::Mouse::static_x,Renderer::Mouse::static_y,0)
                        ).draw();
        }*/


        //Renderer::Quad(0,0,128,128,POGEL::requestImage("{[Data/default_2.bmp],[2]}")).draw();

        //int qd = -1;
        //if(POGEL::frames%2==0) qd = Renderer::HUD::addQuad(new Renderer::Quad(0,0,128,128,POGEL::requestImage("{[Data/default_2.bmp],[2]}")));
        //else qd = Renderer::HUD::addQuad(new Renderer::Quad(128,128,128*2,128*2,POGEL::requestImage("{[Data/default_2.bmp],[1]}")));
        //cout << "*****************" << qd << endl;
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        //glEnable( GL_ALPHA_TEST );
        //glAlphaFunc( GL_GREATER, 0.5f );

        Renderer::HUD::removeQuadCycle();

        if(Renderer::HUD::clearNextCycle)
        {
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
