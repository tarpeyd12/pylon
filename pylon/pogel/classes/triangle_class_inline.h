void
POGEL::TRIANGLE::updateVert()
{
    //if( pvertex )
    {
        POGEL::VECTOR vct0( vertex[ 0 ], vertex[ 1 ] );
        //vct0.normalize();

        POGEL::VECTOR vct1( vertex[ 0 ], vertex[ 2 ] );
        //vct1.normalize();

        vct0.dodotproduct( vct1 );
        normal = vct0;//.normal();

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
        std::cout << "triangle loading failed, null pointer to vertex array." << std::endl;
        throw -1;
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

bool
POGEL::TRIANGLE::settriangletexture() const
{
    // set up the texture to use.
    if ( texture && texture->getbase() != (unsigned int)NULL && texture->isbuilt() )
    {
        texture->set();
        return true;
    }
    else
    {
        POGEL::IMAGE * nullImage = POGEL::getNullImage();
        if ( nullImage && nullImage->getbase() != (unsigned int)NULL && nullImage->isbuilt() )
        {
            nullImage->set();
            return true;
        }
    }
    return false;
}

void
POGEL::TRIANGLE::initializetriangledraw() const
{
    // enable or disable lighting
    if ( properties & TRIANGLE_LIT || properties & TRIANGLE_VERTEX_NORMALS )
    {
        glEnable( GL_LIGHTING );
    }
    else
    {
        glDisable( GL_LIGHTING );
    }

    if( POGEL::hasproperty( POGEL_NODOUBLESIDEDTRIANGLES ) )
    {
        glEnable( GL_CULL_FACE );
        if( (properties & TRIANGLE_INVERT_NORMALS) )
            glCullFace( GL_FRONT );
        else
            glCullFace( GL_BACK );
        //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, int(bool(properties & TRIANGLE_DOUBLESIDED)));
        //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
    }
    else
    {
        if ( !(properties & TRIANGLE_DOUBLESIDED) )
        {
            glEnable( GL_CULL_FACE );
            if( (properties & TRIANGLE_INVERT_NORMALS) )
                glCullFace( GL_FRONT );
            else
                glCullFace( GL_BACK );
            glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
        }
        else if ( glIsEnabled( GL_CULL_FACE ) )
        {
            glDisable( GL_CULL_FACE );
            glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
        }
    }

    // set the transparency
    if ( properties & TRIANGLE_TRANSPARENT )
    {
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glEnable( GL_BLEND );
    }
}

void
POGEL::TRIANGLE::finalizetriangledraw() const
{
    // disable the transparency
    if ( properties & TRIANGLE_TRANSPARENT )
    {
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        if( glIsEnabled( GL_BLEND ) )
        {
            glDisable( GL_BLEND );
        }
    }
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
}

void
POGEL::TRIANGLE::drawgeometry() const
{
    // if using triangle's flat normal set it
    if ( properties & TRIANGLE_LIT && !( properties & TRIANGLE_VERTEX_NORMALS ) )
    {
        if( POGEL::hasproperty( POGEL_NODOUBLESIDEDTRIANGLES ) && properties & TRIANGLE_INVERT_NORMALS )
        //if( properties & TRIANGLE_INVERT_NORMALS )
        glNormal3f( -normal.x, -normal.y, -normal.z );
        else
        glNormal3f( normal.x, normal.y, normal.z );
    }

    if ( !properties & TRIANGLE_COLORED )
    {
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    }

    unsigned int max = POGEL::properties & POGEL_WIREFRAME ? 4 : 3;

    for ( unsigned int a = 0; a < max; ++a )
    {
        unsigned int i = a % 3;

        // the triangle will not be colored if GL_LIGHTING is enabled,
        //  don't know why.
        // set the color
        if ( properties & TRIANGLE_COLORED )
        {
            glColor4f( vertex[ i ].color.r, vertex[ i ].color.g, vertex[ i ].color.b, vertex[ i ].color.a );
        }

        // light the verticies
        if ( properties & TRIANGLE_VERTEX_NORMALS )
        {
            if( POGEL::hasproperty( POGEL_NODOUBLESIDEDTRIANGLES ) && properties & TRIANGLE_INVERT_NORMALS )
            //if( properties & TRIANGLE_INVERT_NORMALS )
            glNormal3f( -vertex[ i ].normal.x, -vertex[ i ].normal.y, -vertex[ i ].normal.z );
            else
            glNormal3f( vertex[ i ].normal.x, vertex[ i ].normal.y, vertex[ i ].normal.z );
        }

        // set the verticies' texture coordanates
        glTexCoord2f( vertex[ i ].u, vertex[ i ].v );

        // set the vertex
        glVertex3f( vertex[ i ].x, vertex[ i ].y, vertex[ i ].z );
    }

    if ( properties & TRIANGLE_COLORED )
    {
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    }
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

template < class Accessor >
void
POGEL::drawTriangleList( void * list, unsigned int length, Accessor accessor )
{
    if( !list || !length )
    {
        return;
    }

    POGEL::TRIANGLE * curtri, * prevtri = accessor( list, 0 );

    bool texgood = prevtri->settriangletexture();
    prevtri->initializetriangledraw();

    GLenum mode;// = GL_TRIANGLES;

    if ( POGEL::properties & POGEL_WIREFRAME )
    {
        mode = GL_LINES;
    }
    else
    {
        mode = GL_TRIANGLES;
    }

    unsigned int currentproperties, previousproperties = prevtri->getproperties();
    POGEL::IMAGE * currentimage, * previousimage = prevtri->texture;

    glBegin( mode );

    for( unsigned int i = 0; i < length; ++i )
    {
        curtri = accessor( list, i );
        currentproperties = curtri->getproperties();
        currentimage = curtri->texture;

        if( texgood && currentproperties == previousproperties && currentimage == previousimage )
        {
            curtri->drawgeometry();
        }
        else
        {
            if( !texgood && currentimage == previousimage )
            {
                previousproperties = currentproperties;
                previousimage = currentimage;
                prevtri = curtri;
                continue;
            }

            glEnd();

            if( currentimage != previousimage )
            {
                texgood = curtri->settriangletexture();
            }

            if( currentproperties != previousproperties )
            {
                prevtri->finalizetriangledraw();
                curtri->initializetriangledraw();
            }

            glBegin( mode );

            curtri->drawgeometry();
        }

        previousproperties = currentproperties;
        previousimage = currentimage;
        prevtri = curtri;
    }

    glEnd();

    accessor( list, length-1 )->finalizetriangledraw();
}
