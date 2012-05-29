#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "triangle_class.h"
#include "physics/physics.h"

/*POGEL::TRIANGLE::TRIANGLE() : ivertlength( 0 ), pvertex( NULL ), texture( NULL ), usetrimid( false )
{
    memset(&ivertex,-1,sizeof(ivertex));
}*/

POGEL::TRIANGLE::TRIANGLE( const POGEL::POINT& a, const POGEL::POINT& b, const POGEL::POINT& c )
 : ivertlength( 0 ), pvertex( NULL )
{
    ivertex[ 0 ] = ivertex[ 1 ] = ivertex[ 2 ] = -1;
    load( POGEL::VERTEX( a ), POGEL::VERTEX( b ), POGEL::VERTEX( c ), NULL, 0 );
}

POGEL::TRIANGLE::TRIANGLE( const POGEL::VERTEX& a, const POGEL::VERTEX& b, const POGEL::VERTEX& c, POGEL::IMAGE* tex, unsigned int prop )
 : ivertlength( 0 ), pvertex( NULL )
{
    ivertex[ 0 ] = ivertex[ 1 ] = ivertex[ 2 ] = -1;
    load( a, b, c, tex, prop );
}

POGEL::TRIANGLE::TRIANGLE( const POGEL::POINT& a, const POGEL::POINT& b, const POGEL::POINT& c, POGEL::IMAGE* tex, unsigned int prop )
 : ivertlength( 0 ), pvertex( NULL )
{
    ivertex[ 0 ] = ivertex[ 1 ] = ivertex[ 2 ] = -1;
    load( POGEL::VERTEX( a ), POGEL::VERTEX( b ), POGEL::VERTEX( c ), tex, prop );
}

POGEL::TRIANGLE::TRIANGLE( POGEL::VERTEX* verts, POGEL::IMAGE* tex, unsigned int prop )
 : ivertlength( 0 ), pvertex( NULL )
{
    ivertex[ 0 ] = ivertex[ 1 ] = ivertex[ 2 ] = -1;
    load( verts, tex, prop );
}

POGEL::TRIANGLE::TRIANGLE( POGEL::VERTEX * vertlist, unsigned int vl, int a, int b, int c, POGEL::IMAGE * tex, unsigned int prop )
 : ivertlength( vl ), pvertex( vertlist )
{
    ivertex[ 0 ] = a;
    ivertex[ 1 ] = b;
    ivertex[ 2 ] = c;
    POGEL::VERTEX p1( a >= 0 && a < (int)vl ? vertlist[a] : POGEL::VERTEX() );
    POGEL::VERTEX p2( b >= 0 && b < (int)vl ? vertlist[b] : POGEL::VERTEX() );
    POGEL::VERTEX p3( c >= 0 && c < (int)vl ? vertlist[c] : POGEL::VERTEX() );
    load( p1, p2, p3, tex, prop );
}


POGEL::TRIANGLE::TRIANGLE( const std::string& s, POGEL::IMAGE* im )
 : ivertlength( 0 ), pvertex( NULL ), texture( im ), usetrimid( true )
{
    ivertex[ 0 ] = ivertex[ 1 ] = ivertex[ 2 ] = -1;
    sscanf(s.c_str(), "{[%u],", &this->properties);
    for( unsigned int i = 0; i < 3; ++i )
    {
        char* vt = POGEL::string("0 %d",i);
        std::string v = POGEL::getStringComponentLevel('{','}', s, vt);
        vertex[i] = POGEL::VERTEX(v);
        #ifndef _WIN32
        free(vt);
        #endif
    }
    normal = POGEL::VECTOR(POGEL::getStringComponentLevel('{','}', s, "0 3"));
    trimid = ( vertex[ 0 ] + vertex[ 1 ] + vertex[ 2 ] ) / 3.0f;
}

POGEL::TRIANGLE::TRIANGLE( const std::string& s )
 : ivertlength( 0 ), pvertex( NULL ), usetrimid( true )
{
    ivertex[ 0 ] = ivertex[ 1 ] = ivertex[ 2 ] = -1;
    sscanf(s.c_str(), "{[%u],", &this->properties);
    for( unsigned int i = 0; i < 3; ++i )
    {
        char* vt = POGEL::string("0 %d",i);
        std::string v = POGEL::getStringComponentLevel('{','}', s, std::string(vt));
        vertex[ i ] = POGEL::VERTEX(v);
        #ifndef _WIN32
        free(vt);
        #endif
    }
    normal = POGEL::VECTOR(POGEL::getStringComponentLevel('{','}', s, "0 3"));
    texture = POGEL::requestImage(POGEL::getStringComponentLevel('{','}', s, "0 4"));
    trimid = ( vertex[ 0 ] + vertex[ 1 ] + vertex[ 2 ] ) / 3.0f;
}

POGEL::TRIANGLE::~TRIANGLE()
{
    /*texture = NULL;
    pvertex = NULL;
    ivertlength = 0;*/
}

POGEL::TRIANGLE
POGEL::TRIANGLE::transform( POGEL::MATRIX* m )
{
    //updateVert();
    POGEL::TRIANGLE t( vertex, texture, properties );
    m->transformTriangle( &t );
    t.makebounding();
    usetrimid = false;
    return t;
}

void
POGEL::TRIANGLE::drawgeometrysolidcolor(const POGEL::COLOR& color) const
{
    glColor4f( color.r, color.g, color.b, color.a );
    if( POGEL::properties & POGEL_WIREFRAME )
    {
        glVertex3f( vertex[ 0 ].x, vertex[ 0 ].y, vertex[ 0 ].z );
        glVertex3f( vertex[ 1 ].x, vertex[ 1 ].y, vertex[ 1 ].z );
        glVertex3f( vertex[ 2 ].x, vertex[ 2 ].y, vertex[ 2 ].z );
        glVertex3f( vertex[ 0 ].x, vertex[ 0 ].y, vertex[ 0 ].z );
        return;
    }
    glVertex3f( vertex[ 0 ].x, vertex[ 0 ].y, vertex[ 0 ].z );
    glVertex3f( vertex[ 1 ].x, vertex[ 1 ].y, vertex[ 1 ].z );
    glVertex3f( vertex[ 2 ].x, vertex[ 2 ].y, vertex[ 2 ].z );
    return;
}

void
POGEL::TRIANGLE::drawgeometryvertexonly() const
{
    if( POGEL::properties & POGEL_WIREFRAME )
    {
        glVertex3f( vertex[ 0 ].x, vertex[ 0 ].y, vertex[ 0 ].z );
        glVertex3f( vertex[ 1 ].x, vertex[ 1 ].y, vertex[ 1 ].z );
        glVertex3f( vertex[ 2 ].x, vertex[ 2 ].y, vertex[ 2 ].z );
        glVertex3f( vertex[ 0 ].x, vertex[ 0 ].y, vertex[ 0 ].z );
        return;
    }
    glVertex3f( vertex[ 0 ].x, vertex[ 0 ].y, vertex[ 0 ].z );
    glVertex3f( vertex[ 1 ].x, vertex[ 1 ].y, vertex[ 1 ].z );
    glVertex3f( vertex[ 2 ].x, vertex[ 2 ].y, vertex[ 2 ].z );
    return;
}

void
POGEL::TRIANGLE::draw() const
{
    #ifdef OPENGL

    // set up the texture to use.
    if ( texture && texture->getbase() != (unsigned int)NULL && texture->isbuilt() )
    {
        texture->set();
    }
    else
    {
        POGEL::IMAGE * nullImage = POGEL::getNullImage();
        if ( nullImage && nullImage->getbase() != (unsigned int)NULL && nullImage->isbuilt() )
        {
            nullImage->set();
            //texture = nullImage;
        }
        else
        {
            return;
        }
    }

    bool b_bounding   = POGEL::hasproperty( POGEL_BOUNDING );
    bool b_wireframe  = POGEL::hasproperty( POGEL_WIREFRAME );

    //updateVert();

    // draw the triangle's bounding box
    if ( b_bounding )
    {
        bounding.draw( POGEL::POINT() );
    }

    bool b_lit         = this->hasproperty( TRIANGLE_LIT );
    bool b_vertnorms   = this->hasproperty( TRIANGLE_VERTEX_NORMALS );
    bool b_doublesided = this->hasproperty( TRIANGLE_DOUBLESIDED );
    bool b_transparent = this->hasproperty( TRIANGLE_TRANSPARENT );

    // enable or disable lighting
    if ( b_lit || b_vertnorms )
    {
        glEnable( GL_LIGHTING );
    }
    else
    {
        glDisable( GL_LIGHTING );
    }

    if ( !b_doublesided )
    {
        glEnable( GL_CULL_FACE );
        glCullFace( GL_BACK );
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
    }
    else if ( glIsEnabled( GL_CULL_FACE ) )
    {
        glDisable( GL_CULL_FACE );
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    }

    // set the transparency
    bool blendEnabled = false;
    if ( b_transparent )
    {
        blendEnabled = glIsEnabled( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glEnable( GL_BLEND );
    }

    // begin either a solid face or lines for wireframe
    if ( b_wireframe )
    {
        glBegin( GL_LINES );
    }
    else
    {
        glBegin( GL_TRIANGLES );
    }

    drawgeometry();

    // end GL_TRIANGLES or GL_LINES
    glEnd();

    // disable the transparency
    if ( b_transparent )
    {
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        if( !blendEnabled )
        {
            glDisable( GL_BLEND );
        }
    }

    #endif
}

void
POGEL::drawTriangleList( POGEL::TRIANGLE * face, unsigned int numfaces )
{
    if( !face || !numfaces )
    {
        return;
    }

    bool texgood = face[ 0 ].settriangletexture();
    face[ 0 ].initializetriangledraw();

    GLenum mode;// = GL_TRIANGLES;

    if ( POGEL::hasproperty( POGEL_WIREFRAME ) )
    {
        mode = GL_LINES;
    }
    else
    {
        mode = GL_TRIANGLES;
    }

    unsigned int currentproperties, previousproperties = face[ 0 ].getproperties();
    POGEL::IMAGE * currentimage, * previousimage = face[ 0 ].texture;

    glBegin( mode );

    for( unsigned int i = 0; i < numfaces; ++i )
    {
        currentproperties = face[ i ].getproperties();
        currentimage = face[ i ].texture;

        if( texgood && currentproperties == previousproperties && currentimage == previousimage )
        {
            face[ i ].drawgeometry();
        }
        else
        {
            if( !texgood && currentimage == previousimage )
            {
                previousproperties = currentproperties;
                previousimage = currentimage;
                continue;
            }

            glEnd();

            if( currentimage != previousimage )
            {
                texgood = face[ i ].settriangletexture();
            }

            if( currentproperties != previousproperties )
            {
                face[ i-1 ].finalizetriangledraw();
                face[ i ].initializetriangledraw();
            }

            glBegin( mode );
            face[ i ].drawgeometry();
        }

        previousproperties = currentproperties;
        previousimage = currentimage;
    }

    glEnd();

    face[ numfaces-1 ].finalizetriangledraw();
}

void
POGEL::drawTriangleList( void * list, unsigned int length, TRIANGLE * (*accessor)(void*,unsigned int) )
{
    if( !list || !length )
    {
        return;
    }

    bool texgood = accessor( list, 0 )->settriangletexture();
    accessor( list, 0 )->initializetriangledraw();

    GLenum mode;// = GL_TRIANGLES;

    if ( POGEL::hasproperty( POGEL_WIREFRAME ) )
    {
        mode = GL_LINES;
    }
    else
    {
        mode = GL_TRIANGLES;
    }

    unsigned int currentproperties, previousproperties = accessor( list, 0 )->getproperties();
    POGEL::IMAGE * currentimage, * previousimage = accessor( list, 0 )->texture;

    glBegin( mode );

    for( unsigned int i = 0; i < length; ++i )
    {
        currentproperties = accessor( list, i )->getproperties();
        currentimage = accessor( list, i )->texture;

        if( texgood && currentproperties == previousproperties && currentimage == previousimage )
        {
            accessor( list, i )->drawgeometry();
        }
        else
        {
            if( !texgood && currentimage == previousimage )
            {
                previousproperties = currentproperties;
                previousimage = currentimage;
                continue;
            }

            glEnd();

            if( currentimage != previousimage )
            {
                texgood = accessor( list, i )->settriangletexture();
            }

            if( currentproperties != previousproperties )
            {
                accessor( list, i-1 )->finalizetriangledraw();
                accessor( list, i )->initializetriangledraw();
            }

            glBegin( mode );

            accessor( list, i )->drawgeometry();
        }

        previousproperties = currentproperties;
        previousimage = currentimage;
    }

    glEnd();

    accessor( list, length-1 )->finalizetriangledraw();
}

void
POGEL::drawTriangleListColored( POGEL::TRIANGLE * face, unsigned int numfaces, const unsigned char* color )
{
    if( !face || !numfaces )
    {
        return;
    }

    GLenum mode;// = GL_TRIANGLES;

    if ( POGEL::hasproperty( POGEL_WIREFRAME ) )
    {
        mode = GL_LINES;
    }
    else
    {
        mode = GL_TRIANGLES;
    }

    unsigned int currentproperties, previousproperties = face[ 0 ].getproperties();

    if ( !(previousproperties & TRIANGLE_DOUBLESIDED) )
    {
        glEnable( GL_CULL_FACE );
        if( (previousproperties & TRIANGLE_INVERT_NORMALS) )
            glCullFace( GL_FRONT );
        else
            glCullFace( GL_BACK );
    }
    else if ( glIsEnabled( GL_CULL_FACE ) )
    {
        glDisable( GL_CULL_FACE );
    }

    glColor4ub( color[ 0 ], color[ 1 ], color[ 2 ], color[ 3 ] );

    glBegin( mode );

    for( unsigned int i = 0; i < numfaces; ++i )
    {
        currentproperties = face[ i ].getproperties();

        if( currentproperties == previousproperties )
        {
            face[ i ].drawgeometryvertexonly();
        }
        else
        {
            glEnd();

            if( currentproperties != previousproperties )
            {
                if ( !(currentproperties & TRIANGLE_DOUBLESIDED) )
                {
                    glEnable( GL_CULL_FACE );
                    if( (currentproperties & TRIANGLE_INVERT_NORMALS) )
                        glCullFace( GL_FRONT );
                    else
                        glCullFace( GL_BACK );
                }
                else if ( glIsEnabled( GL_CULL_FACE ) )
                {
                    glDisable( GL_CULL_FACE );
                }
            }

            glBegin( mode );
            face[ i ].drawgeometryvertexonly();
        }

        previousproperties = currentproperties;
    }

    glEnd();
}
