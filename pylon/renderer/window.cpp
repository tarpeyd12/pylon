#include "window.h"

namespace Renderer
{
    namespace Window
    {
        namespace Size
        {
            int width;
            int height;
        }

        void Create(std::string name , int x, int y, int pos_x, int pos_y)
        {
            Renderer::Window::Size::width = x;
            Renderer::Window::Size::height = y;
            glutInitWindowSize(x,y);
            glutInitWindowPosition(pos_x,pos_y);
            glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

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

        void Resize(int width, int height)
        {
            Renderer::Window::Size::width = width;
            Renderer::Window::Size::height = height;

            const float ar = (float) width / (float) height;

            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            gluPerspective(45.0, ar, 0.01, 1000.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity() ;
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
            glEnable(GL_DEPTH_TEST);
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        }
    }
}
