#include "bounding_class.h"

POGEL::BOUNDING::BOUNDING()
 : numpoints(0), isactual(true), maxdistance(0.0f), min(), max(), color(BOUNDING_DEFAULT_COLOR)
{
    /*maxdistance=0.0f;
    max=POGEL::POINT();
    min=POGEL::POINT();
    numpoints=0;
    color = BOUNDING_DEFAULT_COLOR;
    isactual = true;*/
}

POGEL::BOUNDING::BOUNDING( unsigned int type )
 : numpoints(0), isactual(true), maxdistance(0.0f), min(), max()
{
    /*maxdistance = 0.0f;
    max = POGEL::POINT();
    min = POGEL::POINT();
    numpoints = 0;
    isactual = true;*/
    switch( type )
    {
        case BOUNDING_OBJECT:
            color = BOUNDING_OBJECT_COLOR;
            break;
        case BOUNDING_TRIANGLE:
            color = BOUNDING_TRIANGLE_COLOR;
            break;
        default:
            color = BOUNDING_DEFAULT_COLOR;
            break;
    }
}

POGEL::BOUNDING::BOUNDING( float maximum, float gx, float lx, float gy, float ly, float gz, float lz )
 : numpoints(1), isactual(true), maxdistance(maximum), min(lx,ly,lz), max(gx,gy,gz), color(BOUNDING_DEFAULT_COLOR)
{
    /*maxdistance=maximum;
    max.x=gx;
    min.x=lx;
    max.y=gy;
    min.y=ly;
    max.z=gz;
    min.z=lz;
    numpoints=1;
    color = BOUNDING_DEFAULT_COLOR;
    isactual = true;*/
}

void
POGEL::BOUNDING::draw( const POGEL::POINT& mid ) const
{
    #ifdef OPENGL
    // 35 calls to OpenGL
    if( POGEL::properties & POGEL_BOUNDING )
    {
        glPushMatrix();
            glDisable( GL_TEXTURE_2D );
            glDisable( GL_LIGHTING );
            glColor4f( color.r, color.g, color.b, color.a );
            glTranslatef( mid.x, mid.y, mid.z );
            // the POGEL::LINE class cannot work here (besides its slow)
            glBegin( GL_LINES );
                glVertex3f( min.x, min.y, min.z ); glVertex3f( min.x, min.y, max.z );
                glVertex3f( min.x, max.y, min.z ); glVertex3f( min.x, max.y, max.z );
                glVertex3f( max.x, min.y, min.z ); glVertex3f( max.x, min.y, max.z );
                glVertex3f( max.x, max.y, min.z ); glVertex3f( max.x, max.y, max.z );
                glVertex3f( min.x, min.y, min.z ); glVertex3f( max.x, min.y, min.z );
                glVertex3f( min.x, max.y, min.z ); glVertex3f( max.x, max.y, min.z );
                glVertex3f( min.x, min.y, max.z ); glVertex3f( max.x, min.y, max.z );
                glVertex3f( min.x, max.y, max.z ); glVertex3f( max.x, max.y, max.z );
                glVertex3f( min.x, min.y, min.z ); glVertex3f( min.x, max.y, min.z );
                glVertex3f( min.x, min.y, max.z ); glVertex3f( min.x, max.y, max.z );
                glVertex3f( max.x, min.y, min.z ); glVertex3f( max.x, max.y, min.z );
                glVertex3f( max.x, min.y, max.z ); glVertex3f( max.x, max.y, max.z );
            glEnd();
            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
            glEnable( GL_LIGHTING );
            glEnable( GL_TEXTURE_2D );
        glPopMatrix();
    }
    #endif
}

void
POGEL::BOUNDING::draw() const
{
    #ifdef OPENGL
    // 32 calls to OpenGL
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_LIGHTING );
    glColor4f( color.r, color.g, color.b, color.a );
    glBegin( GL_QUADS );
        glVertex3f( min.x, min.y, min.z ); glVertex3f( max.x, min.y, min.z );
        glVertex3f( max.x, max.y, min.z ); glVertex3f( min.x, max.y, min.z );
        glVertex3f( min.x, min.y, max.z ); glVertex3f( max.x, min.y, max.z );
        glVertex3f( max.x, max.y, max.z ); glVertex3f( min.x, max.y, max.z );

        glVertex3f( min.x, min.y, min.z ); glVertex3f( max.x, min.y, min.z );
        glVertex3f( max.x, min.y, max.z ); glVertex3f( min.x, min.y, max.z );
        glVertex3f( min.x, max.y, min.z ); glVertex3f( max.x, max.y, min.z );
        glVertex3f( max.x, max.y, max.z ); glVertex3f( min.x, max.y, max.z );

        glVertex3f( min.x, min.y, min.z ); glVertex3f( min.x, max.y, min.z );
        glVertex3f( min.x, max.y, max.z ); glVertex3f( min.x, min.y, max.z );
        glVertex3f( max.x, min.y, min.z ); glVertex3f( max.x, max.y, min.z );
        glVertex3f( max.x, max.y, max.z ); glVertex3f( max.x, min.y, max.z );
    glEnd();
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    glEnable( GL_LIGHTING );
    glEnable( GL_TEXTURE_2D );
    #endif
}

