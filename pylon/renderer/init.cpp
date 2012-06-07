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
    void Init()
    {
        using namespace Renderer;

        glClearColor(.5,.5,.5,.5);
        //glClearColor(0,0,0,0);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glEnable(GL_TEXTURE_2D);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_FASTEST);
        //glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_NORMALIZE);

        glEnable(GL_COLOR_MATERIAL);

        glEnable(GL_LIGHTING);

        // TODO: make flexable/dynamic lighting in scripting/modeling
        const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

        glEnable(GL_LIGHT0);

        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
        const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
        const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat high_shininess[] = { 100.0f };

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

        Renderer::HUD::Init();

        if(!POGEL::hasproperty(POGEL_DEBUG))
            glutSetCursor(GLUT_CURSOR_NONE);

        POGEL::InitFps();

        //glEnable( GL_MULTISAMPLE );
        //glSampleCoverage(0.5,GL_FALSE);

        if( Renderer::SingleThreaded )
        {
            //POGEL::addproperty(POGEL_TIMEBASIS);
        }

        //POGEL::addproperty(POGEL_TIMEBASIS);

        Renderer::timer30 = new Timing::Timer(25,"Renderer"); // 25 fps
    }
}
