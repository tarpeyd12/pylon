#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "triangle_class.h"
#include "physics/physics.h"

POGEL::TRIANGLE::TRIANGLE()
 : ivertlength( 0 ), pvertex( NULL ), texture( NULL ), usetrimid( false )
{
    ivertex[ 0 ] = ivertex[ 1 ] = ivertex[ 2 ] = -1;
}

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
    texture = NULL;
    pvertex = NULL;
    ivertlength = 0;
}

void
POGEL::TRIANGLE::updateVert()
{
    if( pvertex )
    {
        POGEL::VECTOR vct0( vertex[ 0 ], vertex[ 1 ] );
        vct0.normalize();

        POGEL::VECTOR vct1( vertex[ 0 ], vertex[ 2 ] );
        vct1.normalize();

        vct0.dodotproduct( vct1 );
        normal = vct0.normal();

        trimid = ( vertex[ 0 ] + vertex[ 1 ] + vertex[ 2 ] ) / 3.0f;
        usetrimid = true;
        makebounding();
    }
}

void
POGEL::TRIANGLE::load( const POGEL::VERTEX& a, const POGEL::VERTEX& b, const POGEL::VERTEX& c, POGEL::IMAGE * tex, unsigned int prop )
{
    texture = tex;
    properties = prop;

    POGEL::VECTOR vct0( a, b );
    vct0.normalize();

    POGEL::VECTOR vct1( a, c );
    vct1.normalize();

    vct0.dodotproduct( vct1 );
    normal = vct0.normal();
    bounding.color = BOUNDING_TRIANGLE_COLOR;
    trimid = ( a + b + c ) / 3.0f;
    usetrimid = true;

    vertex[ 0 ] = a;
    vertex[ 1 ] = b;
    vertex[ 2 ] = c;

    makebounding();
}

void
POGEL::TRIANGLE::load( POGEL::VERTEX * verts,POGEL::IMAGE * tex,unsigned int prop )
{
    if( verts )
    {
        load( verts[ 0 ], verts[ 1 ], verts[ 2 ], tex, prop );
    }
    else
    {
        printf( "triangle loading failed, null pointer to vertex array.\n" );
    }
}

void
POGEL::TRIANGLE::settexture( POGEL::IMAGE* tex )
{
    texture = tex;
}

POGEL::IMAGE *
POGEL::TRIANGLE::gettexture() const
{
    return texture;
}

std::string
POGEL::TRIANGLE::toString()
{
    updateVert();
    char *p = POGEL::string("%u",properties);
    std::string s =
        "{"
            "[" + std::string(p)       + "],"
            ""  + vertex[0].toString() + ","
            ""  + vertex[1].toString() + ","
            ""  + vertex[2].toString() + ","
            ""  + normal.toString()    + ","
            ""  + (texture==NULL?"{IMAGE_NULL}":texture->toString()) + ""
        "}";
    free(p);
    return s;
}

void
POGEL::TRIANGLE::scroll_tex_values( float s, float t )
{
    vertex[ 0 ].scroll_tex_values( s, t );
    vertex[ 1 ].scroll_tex_values( s, t );
    vertex[ 2 ].scroll_tex_values( s, t );
}

void
POGEL::TRIANGLE::print() const
{
    //updateVert();
    printf("\n");
    vertex[ 0 ].print();
    printf("\n");
    vertex[ 1 ].print();
    printf("\n");
    vertex[ 2 ].print();
    printf("\n");
}

POGEL::LINE
POGEL::TRIANGLE::getEdge( unsigned int l ) const
{
    //updateVert();
    return POGEL::LINE( vertex[ l % 3 ], vertex[ ( l + 1 ) % 3 ] );
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

POGEL::POINT
POGEL::TRIANGLE::middle()
{
    if( !usetrimid )
    {
        trimid = ( vertex[ 0 ] + vertex[ 1 ] + vertex[ 2 ] ) / 3.0f;
        usetrimid = true;
    }
    return trimid;
}

POGEL::POINT
POGEL::TRIANGLE::middle() const
{
    if( usetrimid )
    {
        return trimid;
    }
    return ( vertex[ 0 ] + vertex[ 1 ] + vertex[ 2 ] ) / 3.0f;
}

bool
POGEL::TRIANGLE::isinfront( const POGEL::POINT& p ) const
{
    POGEL::VECTOR vect(normal);
    if( properties & TRIANGLE_INVERT_NORMALS )
    {
        vect *= -1.0f;
    }
    //return vect.getangle(POGEL::VECTOR(middle(),p).normal()) < 90.0f;
    return vect.dotproduct( p + middle() ) < 0.0f;
}

bool
POGEL::TRIANGLE::distcheck( const POGEL::POINT& p, float dist ) const
{
    POGEL::POINT mid( middle() );
    POGEL::POINT points[10] = {
        mid, \
        vertex[ 0 ], \
        vertex[ 1 ], \
        vertex[ 2 ], \
        ( vertex[ 0 ] + vertex[ 1 ] ) * 0.5f, \
        ( vertex[ 0 ] + vertex[ 2 ] ) * 0.5f, \
        ( vertex[ 1 ] + vertex[ 2 ] ) * 0.5f, \
        ( vertex[ 0 ] + mid ) * 0.5f, \
        ( vertex[ 1 ] + mid ) * 0.5f, \
        ( vertex[ 2 ] + mid ) * 0.5f
    };

    dist *= dist;

    for( unsigned int i = 0; i < 10; ++i )
    {
        if( p.distancesquared( points[ i ] ) <= dist )
        {
            return true;
        }
    }
    return false;
}

float
POGEL::TRIANGLE::distance( const POGEL::POINT& p) const
{
    POGEL::POINT mid( middle() );
    float dist( 0.0f );
    POGEL::POINT points[10] = {
        mid, \
        vertex[ 0 ], \
        vertex[ 1 ], \
        vertex[ 2 ], \
        ( vertex[ 0 ] + vertex[ 1 ] ) * 0.5f, \
        ( vertex[ 0 ] + vertex[ 2 ] ) * 0.5f, \
        ( vertex[ 1 ] + vertex[ 2 ] ) * 0.5f, \
        ( vertex[ 0 ] + mid ) * 0.5f, \
        ( vertex[ 1 ] + mid ) * 0.5f, \
        ( vertex[ 2 ] + mid ) * 0.5f
    };

    for( unsigned int i = 0; i < 10; ++i )
    {
        float d = p.distancesquared( points[ i ] );
        if( d < dist || !i )
        {
            dist = d;
        }
    }

    if( dist > 0.0f )
    {
        return (float)sqrt( dist );
    }

    return 0.0f;
}

void
POGEL::TRIANGLE::makebounding()
{
    bounding.clear();
    POGEL::POINT mid( middle() );
    bounding.addpoint( mid, vertex[ 0 ] );
    bounding.addpoint( mid, vertex[ 1 ] );
    bounding.addpoint( mid, vertex[ 2 ] );
    //bounding.fin();
}

POGEL::POINT
POGEL::TRIANGLE::getposition()
{
    return middle();
}

POGEL::POINT
POGEL::TRIANGLE::getposition() const
{
    return middle();
}

POGEL::BOUNDING
POGEL::TRIANGLE::getbounding() const
{
    return bounding;
}

bool
POGEL::TRIANGLE::isClear() const
{
    if( texture )
    {
        return texture->isClear() || properties & TRIANGLE_TRANSPARENT;
    }
    else
    {
        POGEL::IMAGE * nullImage = POGEL::getNullImage();
        if( nullImage )
        {
            return nullImage->isClear() || properties & TRIANGLE_TRANSPARENT;
        }
    }
    return properties & TRIANGLE_TRANSPARENT;
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

POGEL::TRIANGLE&
POGEL::TRIANGLE::operator = ( const POGEL::TRIANGLE& t )
{
    /*properties = t.properties;
    trimid = t.trimid;
    usetrimid = t.usetrimid;
    bounding = t.bounding;
    vertex[0] = t.vertex[0];
    vertex[1] = t.vertex[1];
    vertex[2] = t.vertex[2];
    ivertex[0] = t.ivertex[0];
    ivertex[1] = t.ivertex[1];
    ivertex[2] = t.ivertex[2];
    vertnormals[0] = t.vertnormals[0];
    vertnormals[1] = t.vertnormals[1];
    vertnormals[2] = t.vertnormals[2];
    pvertex = t.pvertex;
    ivertlength = t.ivertlength;
    texture = t.texture;
    normal = t.normal;*/
    memcpy( this, &t, sizeof( t ) );
    return *this;
}
