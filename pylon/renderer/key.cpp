#include "key.h"

namespace Renderer
{
    namespace Key
    {
        volatile bool keys[256];

        volatile char last;

        void Down( unsigned char key, int x, int y )
        {
            //if(key == (unsigned char)27) exit(0);
            Renderer::Key::keys[ key ] = true;
            last = key;
            //glutPostRedisplay();
            x = y = 0;
        }

        void Up( unsigned char key, int x, int y )
        {
            Renderer::Key::keys[ key ] = false;
            //glutPostRedisplay();
            x = y = 0;
        }
    }
}
