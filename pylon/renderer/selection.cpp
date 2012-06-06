#include "selection.h"

namespace Renderer
{
    namespace Selection
    {
        unsigned char * pixeldata = NULL;

        std::string lastsimname = "";
        std::string lastobjname = "";
        volatile bool lastwasselected = false;

        void Init( unsigned int x, unsigned int y )
        {
            pixeldata = new unsigned char[ ( x + 1 ) * ( y + 1 ) * 4 + 4 ];
            memset( pixeldata, 0, ( x + 1 ) * ( y + 1 ) * 4 + 4 );
        }

        void Resize( unsigned int x, unsigned int y )
        {
            unsigned char * tmpdata = pixeldata;
            pixeldata = new unsigned char[ ( x + 1 ) * ( y + 1 ) * 4 + 4 ];
            memset( pixeldata, 0, ( x + 1 ) * ( y + 1 ) * 4 + 4 );
            delete [] tmpdata;
        }

        /*
        // get color information from frame buffer
        int viewport[4];
        glGetIntegerv( GL_VIEWPORT, viewport );
        unsigned char * pixels = new unsigned char[ ( viewport[ 2 ] + 1 ) * ( viewport[ 3 ] + 1 ) * 4 + 4 ];
        glReadPixels( 0, 0, viewport[ 2 ], viewport[ 3 ], GL_RGBA, GL_UNSIGNED_BYTE, pixels );
        unsigned int pixelindex = 4 * ( x * viewport[ 2 ] + y );
        unsigned int simid = (pixels[ pixelindex + 0 ] << 8) | (pixels[ pixelindex + 1 ] << 0);
        unsigned int objid = (pixels[ pixelindex + 2 ] << 8) | (pixels[ pixelindex + 3 ] << 0);
        */

        void Retrieve()
        {
            int viewport[4];
            glGetIntegerv( GL_VIEWPORT, viewport );
            glReadPixels( 0, 0, viewport[ 2 ], viewport[ 3 ], GL_RGBA, GL_UNSIGNED_BYTE, Renderer::Selection::pixeldata );
        }

        void RetrieveAt( unsigned int x, unsigned int y )
        {
            int viewport[4];
            glGetIntegerv( GL_VIEWPORT, viewport );
            unsigned char dat[4] = { 0, 0, 0, 0 };
            glReadPixels( x, viewport[ 3 ] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, dat );
            unsigned int pixelindex = 4 * ( x * viewport[ 2 ] + viewport[ 3 ] - y );
            for( unsigned int i = 0; i < 4; ++i )
            {
                Renderer::Selection::pixeldata[ pixelindex + i ] = dat[ i ];
            }
        }

        void RetrieveAt( unsigned int x, unsigned int y, int* sim, int* obj )
        {
            int viewport[4];
            glGetIntegerv( GL_VIEWPORT, viewport );
            unsigned char dat[4] = { 0, 0, 0, 0 };
            glReadPixels( x, viewport[ 3 ] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, dat );
            unsigned int pixelindex = 4 * ( x * viewport[ 2 ] + viewport[ 3 ] - y );
            for( unsigned int i = 0; i < 4; ++i )
            {
                Renderer::Selection::pixeldata[ pixelindex + i ] = dat[ i ];
            }
            if( sim )
            {
                *sim = (int)(unsigned int)((dat[ 0 ] << 8) | (dat[ 1 ] << 0)) - 1;
            }
            if( obj )
            {
                *obj = (int)(unsigned int)((dat[ 2 ] << 8) | (dat[ 3 ] << 0)) - 1;
            }
        }

        int GetSimulation( unsigned int x, unsigned int y )
        {
            if( !Renderer::Selection::pixeldata )
            {
                return -2;
            }
            int viewport[4];
            glGetIntegerv( GL_VIEWPORT, viewport );
            unsigned int pixelindex = 4 * ( x * viewport[ 2 ] + y );
            return ((Renderer::Selection::pixeldata[ pixelindex + 0 ] << 8) | (Renderer::Selection::pixeldata[ pixelindex + 1 ] << 0)) - 1;
        }

        int GetObject( unsigned int x, unsigned int y )
        {
            if( !Renderer::Selection::pixeldata )
            {
                return -2;
            }
            int viewport[4];
            glGetIntegerv( GL_VIEWPORT, viewport );
            unsigned int pixelindex = 4 * ( x * viewport[ 2 ] + y );
            return ((Renderer::Selection::pixeldata[ pixelindex + 2 ] << 8) | (Renderer::Selection::pixeldata[ pixelindex + 3 ] << 0)) - 1;
        }

        void DoMouseSelection()
        {
            Renderer::Draw::PickDraw();
            int simnum = -1, objnum = -1;
            Renderer::Selection::RetrieveAt( Mouse::X, Mouse::Y, &simnum, &objnum );
            if( simnum >= 0 && objnum >= 0 )
            {
                Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation( (unsigned int)simnum );
                if( sim )
                {
                    POGEL::PHYSICS::SOLID * obj = sim->getObject( (unsigned int)objnum );
                    if( obj )
                    {
                        Renderer::Selection::lastwasselected = true;
                        Renderer::Selection::lastsimname = sim->getName();
                        Renderer::Selection::lastobjname = obj->getsname();
                        //cout << "\tSimulation: \"" << sim->getName() << "\", Object: \"" << obj->getsname() << "\"" << endl;
                    }
                    else
                    {
                        Renderer::Selection::lastwasselected = false;
                        //cout << "\tSimulation: \"" << sim->getName() << "\"" << endl;
                    }
                }
                else
                {
                    Renderer::Selection::lastwasselected = false;
                }
            }
            else
            {
                Renderer::Selection::lastwasselected = false;
            }
            glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        }

    }
}
