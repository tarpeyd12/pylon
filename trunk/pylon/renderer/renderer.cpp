#include "renderer.h"

#ifdef _POSIX_C_SOURCE
#undef _POSIX_C_SOURCE
#endif
#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#endif
#include "../objectloader/objectloader.h"

namespace Renderer
{
    // do not tamper with camrot, prot, campos nor ppos.
    POGEL::POINT camrot;
    POGEL::POINT prot;

    POGEL::POINT campos;
    POGEL::POINT ppos;

    POGEL::OBJECT* bob;
    ObjectLoader::Object::Platonic* gr;

    float lastdur;

    // do not tamper with drawLock
    bool drawLock = false;

    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    void Init()
    {
        using namespace Renderer;
        glClearColor(0,0,0,0);
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        //glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);

        //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        //glEnable(GL_BLEND);
        //glDisable(GL_DEPTH_TEST);

        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        bob = NULL;
        //std::string ojdat = ObjectLoader::getobjectformfile("Platonic 0","C3dObjectSphere","Data/bob.wld");
        //gr = new ObjectLoader::Object::Platonic(ojdat);
        //bob = gr->toObject();

        POGEL::InitFps();
        lastdur = POGEL::GetTimePassed();
    }

    void Idle()
    {
        glutPostRedisplay();
    }

    void Display()
    {
        POGEL::IncrementFps();
        POGEL::PrintFps();

        //Renderer::Mouse::Rotation();
        //Renderer::Mouse::Translation();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        Renderer::Window::toOrtho();
        if(Renderer::Mouse::state == GLUT_DOWN)
        {
            POGEL::LINE(
                        POGEL::POINT(Renderer::Mouse::X,Renderer::Mouse::Y,0),
                        POGEL::POINT(Renderer::Mouse::static_x,Renderer::Mouse::static_y,0)
                        ).draw();
        }

        Renderer::Window::toFrustum();

        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);

        glTranslatef(campos.x,campos.y,campos.z);
        glRotatef( Renderer::camrot.x,  1.0f, 0.0f, 0.0f );
        glRotatef( Renderer::camrot.y,  0.0f, 1.0f, 0.0f );
        glRotatef( Renderer::camrot.z,  0.0f, 0.0f, 1.0f );
        if(bob != NULL)
        {
            bob->position = POGEL::POINT();
            bob->draw();
        }

        if(!drawLock)
            for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
                if(Renderer::Physics::simulations[i]->isdyn())
                    static_cast<POGEL::PHYSICS::DYNAMICS*>(Renderer::Physics::simulations[i]->getSim())->draw();
                else
                    static_cast<POGEL::PHYSICS::SIMULATION*>(Renderer::Physics::simulations[i]->getSim())->draw();

        float curdur = POGEL::GetTimePassed();
        if(1.0/(curdur-lastdur) > 60)
            usleep(1000000/60.0-(curdur - lastdur));
        else if(curdur == lastdur)
            usleep(1000000/60.0);
        lastdur = POGEL::GetTimePassed();

        glutSwapBuffers();

        if(POGEL::frames % 1000 == 0 || POGEL::frames < 100)
        {
            bool bob = false;
            for(unsigned int i = 0; i < POGEL::imglstlen(); i++)
                if(!POGEL::lstimg(i)->isbuilt())
                {
                    POGEL::lstimg(i)->build();
                    if(POGEL::hasproperty(POGEL_DEBUG))
                        cout << endl << "building unbuilt image: " << POGEL::lstimg(i)->toString();
                    bob = true;
                }
            if(bob && POGEL::hasproperty(POGEL_DEBUG))
                cout << endl;
        }
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
