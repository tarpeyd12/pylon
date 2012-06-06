#include "key.h"

namespace Renderer
{
    namespace Key
    {
        volatile bool keys[256];

        volatile float lastpressed[256];
        volatile float lastreleased[256];

        volatile int mousepospress[256][2];
        volatile int mouseposrelease[256][2];

        volatile char last;

        void Down( unsigned char key, int x, int y )
        {
            last = key;
            Renderer::Key::keys[ key ] = true;
            Renderer::Key::lastpressed[ key ] = (float)POGEL::GetTimePassed();
            Renderer::Key::mousepospress[ key ][ 0 ] = x;
            Renderer::Key::mousepospress[ key ][ 1 ] = y;
        }

        void Up( unsigned char key, int x, int y )
        {
            Renderer::Key::keys[ key ] = false;
            Renderer::Key::lastreleased[ key ] = (float)POGEL::GetTimePassed();
            Renderer::Key::mouseposrelease[ key ][ 0 ] = x;
            Renderer::Key::mouseposrelease[ key ][ 1 ] = y;
        }
    }
}
