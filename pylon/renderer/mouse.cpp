#include "renderer.h"

namespace Renderer
{
    namespace Mouse
    {
        volatile int X;
        volatile int Y;
        volatile int static_x;
        volatile int static_y;
        volatile int button;
        volatile int state = 1;

        volatile int prev_x;
        volatile int prev_y;


        void Rotation()
        {
            if(Renderer::Mouse::state == GLUT_DOWN && Renderer::Mouse::button == GLUT_LEFT_BUTTON)
            {
                float x = ((float(-1*(Renderer::Mouse::static_y-Renderer::Mouse::Y))/float(Renderer::Window::Size::height))*180 + Renderer::Camera::prot.x);
                float y = ((float(-1*(Renderer::Mouse::static_x-Renderer::Mouse::X))/float(Renderer::Window::Size::width))*360 + Renderer::Camera::prot.y);
                Renderer::Camera::camrot = POGEL::POINT(x,y,Renderer::Camera::camrot.z);
            }
        }

        void Translation()
        {
            if(Renderer::Mouse::state == GLUT_DOWN && Renderer::Mouse::button == GLUT_RIGHT_BUTTON)
            {
                float z = float(Renderer::Mouse::static_y-Renderer::Mouse::Y) + Renderer::Camera::ppos.z;
                Renderer::Camera::campos = POGEL::POINT(Renderer::Camera::campos.x,Renderer::Camera::campos.y, z);
            }
        }

        void Moved(int x, int y)
        {
            Renderer::Mouse::X = x;
            Renderer::Mouse::Y = y;
        }

        void Clicked(int button, int state, int x, int y)
        {
            if( state == GLUT_UP )
            {
                Renderer::Mouse::prev_x = x;
                Renderer::Mouse::prev_y = y;
            }
            if( state == GLUT_DOWN )
            {
                Renderer::Camera::prot = Renderer::Camera::camrot;
                Renderer::Camera::ppos = Renderer::Camera::campos;
                Renderer::Mouse::static_x = Renderer::Mouse::X = x;
                Renderer::Mouse::static_y = Renderer::Mouse::Y = y;
            }
            Renderer::Mouse::button = button;
            Renderer::Mouse::state = state;
        }
    }
}
