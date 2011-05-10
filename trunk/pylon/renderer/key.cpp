#include "key.h"

namespace Renderer
{
    namespace Key
    {
        char keys[256];

        void Down(unsigned char key, int x, int y)
        {
            if(key == (unsigned char)27)
                exit(0);
            Renderer::Key::keys[key] = true;
            glutPostRedisplay();
        }

        void Up(unsigned char key, int x, int y)
        {
            Renderer::Key::keys[key] = false;
            glutPostRedisplay();
        }
    }
}
