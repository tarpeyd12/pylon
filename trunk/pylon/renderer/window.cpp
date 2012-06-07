#include "window.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

namespace Renderer
{
    namespace Window
    {
        namespace Size
        {
            int width;
            int height;
        }

        void Create( std::string name , int x, int y, int pos_x, int pos_y )
        {
            Renderer::Window::Size::width = x;
            Renderer::Window::Size::height = y;

            Renderer::Selection::Init( x, y );

            glutInitWindowSize( x, y );
            glutInitWindowPosition(pos_x,pos_y);
            glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA );

            glutCreateWindow(name.c_str());

            glutReshapeFunc(Renderer::Window::Resize);
            glutDisplayFunc(Renderer::Display);
            glutKeyboardFunc(Renderer::Key::Down);
            glutKeyboardUpFunc(Renderer::Key::Up);
            glutIdleFunc(Renderer::Idle);

            glutMouseFunc(&Renderer::Mouse::Clicked);
            glutMotionFunc(&Renderer::Mouse::Moved);
            glutPassiveMotionFunc(&Renderer::Mouse::Moved);
        }

        void Resize( int width, int height )
        {
            Renderer::Window::Size::width = width;
            Renderer::Window::Size::height = height;

            Renderer::Selection::Resize( width, height );

            const float ar = (float) width / (float) height;

            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            gluPerspective(45.0f, ar, 0.01f, 100.0f);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }

        void toOrtho()
        {
            glDisable(GL_DEPTH_TEST);
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0, Renderer::Window::Size::width, Renderer::Window::Size::height, 0, -1000, 1000);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }

        void toFrustum()
        {
            int width = Renderer::Window::Size::width;
            int height = Renderer::Window::Size::height;

            const float ar = (float) width / (float) height;

            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            gluPerspective(45.0f, ar, 0.1f, 1000.0f);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glEnable(GL_DEPTH_TEST);
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        }
    }
}
