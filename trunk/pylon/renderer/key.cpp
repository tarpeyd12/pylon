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

        ClassList< KeyCallback* > keyDownCallBacks;
        ClassList< KeyCallback* > keyUpCallBacks;

        void Down( unsigned char key, int x, int y )
        {
            if( Renderer::Key::keys[ key ] == true )
            {
                //return;
            }
            last = key;
            Renderer::Key::keys[ key ] = true;
            Renderer::Key::lastpressed[ key ] = (float)POGEL::GetTimePassed();
            Renderer::Key::mousepospress[ key ][ 0 ] = x;
            Renderer::Key::mousepospress[ key ][ 1 ] = y;

            unsigned int numcallbacks = keyDownCallBacks.length();
            for( unsigned int i = 0; i < numcallbacks; ++i )
            {
                if( !keyDownCallBacks[ i ] )
                {
                    continue;
                }
                if( keyDownCallBacks[ i ]->remove )
                {
                    KeyCallback * func = keyDownCallBacks[ i ];
                    keyDownCallBacks.replace( i, NULL );
                    delete func;
                    continue;
                }
                keyDownCallBacks[ i ]->operator()( key, x, y, Renderer::Key::lastpressed[ key ] );
            }
        }

        void Up( unsigned char key, int x, int y )
        {
            if( Renderer::Key::keys[ key ] == false )
            {
                //return;
            }
            Renderer::Key::keys[ key ] = false;
            Renderer::Key::lastreleased[ key ] = (float)POGEL::GetTimePassed();
            Renderer::Key::mouseposrelease[ key ][ 0 ] = x;
            Renderer::Key::mouseposrelease[ key ][ 1 ] = y;

            unsigned int numcallbacks = keyUpCallBacks.length();
            for( unsigned int i = 0; i < numcallbacks; ++i )
            {
                if( !keyUpCallBacks[ i ] )
                {
                    continue;
                }
                if( keyUpCallBacks[ i ]->remove )
                {
                    KeyCallback * func = keyUpCallBacks[ i ];
                    keyUpCallBacks.replace( i, NULL );
                    delete func;
                    continue;
                }
                keyUpCallBacks[ i ]->operator()( key, x, y, Renderer::Key::lastreleased[ key ] );
            }
        }
    }
}
