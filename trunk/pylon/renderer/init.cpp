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
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        //glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);

        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);

        // TODO: make flexable/dynamic lighting in scripting/modeling
        const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

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

        //bob = NULL;
        //std::string ojdat = ObjectLoader::getobjectformfile("Platonic 0","C3dObjectPlatonic","Data/Default.wld");
        //gr = new ObjectLoader::Object::_BaseObject(ojdat);
        //bob = gr->toObject();

        Renderer::HUD::Init();

        glutSetCursor(GLUT_CURSOR_NONE);

        //int qd = Renderer::HUD::addQuad(new Renderer::Quad(0,0,0,0,NULL));
        //Renderer::HUD::removeQuad(qd);
        //cout << "**********" << qd << endl;

        POGEL::InitFps();

        Renderer::timer30 = new Timer(30); // 30 fps
    }
}
