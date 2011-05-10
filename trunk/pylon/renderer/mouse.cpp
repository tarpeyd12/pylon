#include "renderer.h"

namespace Renderer
{
    namespace Mouse
    {
        int X;
        int Y;
        int static_x;
        int static_y;
        int button;
        int state = 1;

        int prev_x;
        int prev_y;


        void Rotation()
        {
            if(Renderer::Mouse::state == GLUT_DOWN && Renderer::Mouse::button == GLUT_LEFT_BUTTON)
            {
                float x = ((float(-1*(Renderer::Mouse::static_y-Renderer::Mouse::Y))/float(Renderer::Window::Size::height))*180 + Renderer::prot.x);
                float y = ((float(-1*(Renderer::Mouse::static_x-Renderer::Mouse::X))/float(Renderer::Window::Size::width))*360 + Renderer::prot.y);
                Renderer::camrot = POGEL::POINT(x,y,camrot.z);
            }
        }

        void Translation()
        {
            if(Renderer::Mouse::state == GLUT_DOWN && Renderer::Mouse::button == GLUT_RIGHT_BUTTON)
            {
                float z = float(Renderer::Mouse::static_y-Renderer::Mouse::Y) + Renderer::ppos.z;
                Renderer::campos = POGEL::POINT(campos.x,campos.y, z);
            }
        }

        void Moved(int x, int y)
        {
            Renderer::Mouse::X = x;
            Renderer::Mouse::Y = y;
        }

        void Clicked(int button, int state, int x, int y)
        {
            if(state == GLUT_UP)
            {
                Renderer::Mouse::prev_x = x;
                Renderer::Mouse::prev_y = y;
            }
            if(state == GLUT_DOWN)
            {
                Renderer::prot = Renderer::camrot;
                Renderer::ppos = Renderer::campos;
                Renderer::Mouse::static_x = Renderer::Mouse::X = x;
                Renderer::Mouse::static_y = Renderer::Mouse::Y = y;
            }
            Renderer::Mouse::button = button;
            Renderer::Mouse::state = state;
        }
    }
}
