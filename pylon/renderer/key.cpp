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

        ClassList< KeyCallback * > keyDownCallBacks;
        ClassList< KeyCallback * > keyUpCallBacks;

        KeyCallback::KeyCallback()
        {
            remove = false;
            haskeyfilters = false;
            memset((void*)keyfilter,(unsigned int)(false),sizeof(bool)*256);
        }

        bool KeyCallback::hasKeyFilters() const
        {
            return haskeyfilters;
        }

        bool KeyCallback::hasKeyFiltered( unsigned char c ) const
        {
            if( haskeyfilters )
            {
                return keyfilter[ c ];
            }
            return true;
        }

        void KeyCallback::setKeyFilter( unsigned char c, bool v )
        {
            haskeyfilters = true;
            keyfilter[ c ] = v;
        }

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

            cout << "Key '" << key  << "' pressed at position (" << x << "," << y << ") at time " << Renderer::Key::lastpressed[ key ] << endl;

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
                if( keyDownCallBacks[ i ]->hasKeyFiltered( key ) )
                {
                    keyDownCallBacks[ i ]->operator()( key, x, y, Renderer::Key::lastpressed[ key ] );
                }
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

            cout << "Key '" << key << "' released at position (" << x << "," << y << ") at time " << Renderer::Key::lastreleased[ key ] << endl;

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
                if( keyUpCallBacks[ i ]->hasKeyFiltered( key ) )
                {
                    keyUpCallBacks[ i ]->operator()( key, x, y, Renderer::Key::lastreleased[ key ] );
                }
            }
        }
    }
}
