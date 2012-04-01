#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "triangle_class.h"
#include "physics/physics.h"

POGEL::TRIANGLE::TRIANGLE()
{
    texture=NULL;
    vertex[0] = vertex[1] = vertex[2] = POGEL::VECTOR();
    trimid = POGEL::POINT();
    usetrimid = false;
    pvertex = NULL;
    ivertex[0] = ivertex[1] = ivertex[2] = -1;
    vertnormals[0] = vertnormals[1] = vertnormals[2] = normal = POGEL::VECTOR();
    ivertlength = 0;
}

POGEL::TRIANGLE::TRIANGLE(POGEL::POINT a,POGEL::POINT b,POGEL::POINT c)
{
    pvertex = NULL;
    ivertex[0] = ivertex[1] = ivertex[2] = -1;
    ivertlength = 0;
    load(POGEL::VERTEX(a),POGEL::VERTEX(b),POGEL::VERTEX(c),NULL,0);
}

POGEL::TRIANGLE::TRIANGLE(POGEL::VERTEX a,POGEL::VERTEX b,POGEL::VERTEX c,POGEL::IMAGE *tex,unsigned int prop)
{
    pvertex = NULL;
    ivertex[0] = ivertex[1] = ivertex[2] = -1;
    ivertlength = 0;
    load(a,b,c,tex,prop);
}

POGEL::TRIANGLE::TRIANGLE(POGEL::POINT a,POGEL::POINT b,POGEL::POINT c,POGEL::IMAGE *tex,unsigned int prop)
{
    pvertex = NULL;
    ivertex[0] = ivertex[1] = ivertex[2] = -1;
    ivertlength = 0;
    load(POGEL::VERTEX(a),POGEL::VERTEX(b),POGEL::VERTEX(c),tex,prop);
}

POGEL::TRIANGLE::TRIANGLE(POGEL::VERTEX* verts,POGEL::IMAGE *tex,unsigned int prop)
{
    pvertex = NULL;
    ivertex[0] = ivertex[1] = ivertex[2] = -1;
    ivertlength = 0;
    load(verts,tex,prop);
}

POGEL::TRIANGLE::TRIANGLE(POGEL::VERTEX * vertlist, unsigned int vl, int a, int b, int c, POGEL::IMAGE * tex, unsigned int prop)
{
    //if( vertlist == NULL ||  vl == 0 )
        //throw -1;
    ivertex[0] = a;
    ivertex[1] = b;
    ivertex[2] = c;
    ivertlength = vl;
    pvertex = vertlist;
    POGEL::VERTEX p1 = a >= 0 && a < (int)vl ? vertlist[a] : POGEL::VERTEX();
    POGEL::VERTEX p2 = b >= 0 && b < (int)vl ? vertlist[b] : POGEL::VERTEX();
    POGEL::VERTEX p3 = c >= 0 && c < (int)vl ? vertlist[c] : POGEL::VERTEX();
    load(p1,p2,p3,tex,prop);
}


POGEL::TRIANGLE::TRIANGLE(std::string s, POGEL::IMAGE* im)
{
    pvertex = NULL;
    ivertex[0] = ivertex[1] = ivertex[2] = -1;
    ivertlength = 0;
    texture = im;
    sscanf(s.c_str(), "{[%u],", &this->properties);
    for(unsigned int i = 0; i < 3; i++)
    {
        char* vt = POGEL::string("0 %d",i);
        std::string v = POGEL::getStringComponentLevel('{','}', s, vt);
        vertex[i] = POGEL::VERTEX(v);
        #ifndef _WIN32
        free(vt);
        #endif
    }
    normal = POGEL::VECTOR(POGEL::getStringComponentLevel('{','}', s, "0 3"));
    trimid = (vertex[0]+vertex[1]+vertex[2])/3.0f;
    usetrimid = true;
}

POGEL::TRIANGLE::TRIANGLE(std::string s)
{
    pvertex = NULL;
    ivertex[0] = ivertex[1] = ivertex[2] = -1;
    ivertlength = 0;
    sscanf(s.c_str(), "{[%u],", &this->properties);
    for(unsigned int i = 0; i < 3; i++)
    {
        char* vt = POGEL::string("0 %d",i);
        std::string v = POGEL::getStringComponentLevel('{','}', s, std::string(vt));
        vertex[i] = POGEL::VERTEX(v);
        #ifndef _WIN32
        free(vt);
        #endif
    }
    normal = POGEL::VECTOR(POGEL::getStringComponentLevel('{','}', s, "0 3"));
    texture = POGEL::requestImage(POGEL::getStringComponentLevel('{','}', s, "0 4"));
    trimid = (vertex[0]+vertex[1]+vertex[2])/3.0f;
    usetrimid = true;
}

POGEL::TRIANGLE::~TRIANGLE()
{
    texture = NULL;
    if(pvertex != NULL)
    {
        //pvertex = NULL;
    }
    //ivertlength = 0;
}

void POGEL::TRIANGLE::updateVert()
{
    if(pvertex != NULL)
    {
        /*int count = 0;
        for(unsigned int i = 0; i < 3; i++)
        {
            int ind = ivertex[i];
            if(ind >= 0 )
            {
                vertex[i].x = pvertex[ind].x;
                vertex[i].y = pvertex[ind].y;
                vertex[i].z = pvertex[ind].z;
                count ++;
            }
        }
        if( count )*/
        {
            //if( !hasproperty(TRIANGLE_VERTEX_NORMALS) && hasproperty(TRIANGLE_LIT) )
            {
                POGEL::VECTOR vct[2];
                vct[0].frompoints(vertex[0],vertex[1]);
                vct[0].normalize();
                vct[1].frompoints(vertex[0],vertex[2]);
                vct[1].normalize();
                vct[0].dodotproduct(vct[1]);
                normal=vct[0].normal();
            }
            bounding = POGEL::BOUNDING(BOUNDING_TRIANGLE);
            trimid = (vertex[0]+vertex[1]+vertex[2])/3.0f;
            usetrimid = true;
            makebounding();
        }
    }
}

void POGEL::TRIANGLE::load(POGEL::VERTEX a,POGEL::VERTEX b,POGEL::VERTEX c,POGEL::IMAGE *tex,unsigned int prop)
{
    POGEL::VECTOR vct[2];

    vertex[0]=a;
    vertex[1]=b;
    vertex[2]=c;
    texture=tex;
    properties=prop;

    vct[0].frompoints(vertex[0],vertex[1]);
    vct[0].normalize();
    vct[1].frompoints(vertex[0],vertex[2]);
    vct[1].normalize();

    vct[0].dodotproduct(vct[1]);
    normal=vct[0].normal();
    bounding = POGEL::BOUNDING(BOUNDING_TRIANGLE);
    trimid = (vertex[0]+vertex[1]+vertex[2])/3.0f;
    usetrimid = true;
    makebounding();
}

void POGEL::TRIANGLE::load(POGEL::VERTEX* verts,POGEL::IMAGE *tex,unsigned int prop)
{
    if(verts)
    {
        load(verts[0],verts[1],verts[2],tex,prop);
    }
    else
    {
        printf("triangle loading failed, null pointer to vertex array.\n");
    }
}

void POGEL::TRIANGLE::settexture(POGEL::IMAGE *tex)
{
    texture=tex;
}

POGEL::IMAGE* POGEL::TRIANGLE::gettexture()
{
    return texture;
}

std::string POGEL::TRIANGLE::toString()
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

void POGEL::TRIANGLE::scroll_tex_values(float s, float t)
{
    vertex[0].scroll_tex_values(s,t);
    vertex[1].scroll_tex_values(s,t);
    vertex[2].scroll_tex_values(s,t);
}

void POGEL::TRIANGLE::print()
{
    //updateVert();
    printf("\n");
    vertex[0].topoint().print();
    printf("\n");
    vertex[1].topoint().print();
    printf("\n");
    vertex[2].topoint().print();
    printf("\n");
}

POGEL::LINE POGEL::TRIANGLE::getEdge(unsigned int l)
{
    //updateVert();
    return POGEL::LINE(vertex[l%3].topoint(), vertex[(l+1)%3].topoint());
}

POGEL::TRIANGLE POGEL::TRIANGLE::transform(POGEL::MATRIX* m)
{
    //updateVert();
    POGEL::TRIANGLE t(vertex, texture, properties);
    m->transformTriangle(&t);
    t.makebounding();
    usetrimid = false;
    return t;
}

POGEL::POINT POGEL::TRIANGLE::middle()
{
    //updateVert();
    if(!usetrimid)
    {
        trimid = (vertex[0]+vertex[1]+vertex[2])/3.0f;
        usetrimid = true;
    }
    return trimid;
}

bool POGEL::TRIANGLE::isinfront(POGEL::POINT p)
{
    POGEL::VECTOR vect = !hasproperty(TRIANGLE_INVERT_NORMALS) ? normal : normal*-1.0f;
    //return vect.getangle(POGEL::VECTOR(middle(),p).normal()) < 90.0f;
    return vect.dotproduct(p+middle()) < 0.0f;
}

bool POGEL::TRIANGLE::distcheck(POGEL::POINT p, float dist)
{
    POGEL::POINT closest = middle();
    POGEL::POINT points[] = {
        closest, \
        vertex[0], \
        vertex[1], \
        vertex[2], \
        (vertex[0]+vertex[1])/2.0f, \
        (vertex[0]+vertex[2])/2.0f, \
        (vertex[1]+vertex[2])/2.0f, \
        (vertex[0]+closest)/2.0f, \
        (vertex[1]+closest)/2.0f, \
        (vertex[2]+closest)/2.0f
    };

    for(int i=0;i<10;i++)
    {
        if(p.distance(points[i]) <= dist)
        {
            return true;
        }
    }
    return false;
}

float POGEL::TRIANGLE::distance(POGEL::POINT p)
{
    POGEL::POINT mid = middle();
    float dist = 0.0f;// p.distance(mid);
    POGEL::POINT points[] = {
        mid, \
        vertex[0], \
        vertex[1], \
        vertex[2], \
        (vertex[0]+vertex[1])/2.0f, \
        (vertex[0]+vertex[2])/2.0f, \
        (vertex[1]+vertex[2])/2.0f, \
        (vertex[0]+mid)/2.0f, \
        (vertex[1]+mid)/2.0f, \
        (vertex[2]+mid)/2.0f
    };

    for(int i=0;i<10;i++)
    {
        if(p.distance(points[i]) < dist)
        {
            dist = p.distance(points[i]);
        }
    }
    return dist;
}

void POGEL::TRIANGLE::makebounding()
{
    bounding.clear();
    POGEL::POINT mid = middle();
    bounding.addpoint(mid, vertex[0]);
    bounding.addpoint(mid, vertex[1]);
    bounding.addpoint(mid, vertex[2]);
    bounding.fin();
}

POGEL::POINT POGEL::TRIANGLE::getposition()
{
    return middle();
}

POGEL::BOUNDING POGEL::TRIANGLE::getbounding()
{
    return bounding;
}

bool POGEL::TRIANGLE::isClear() {
    bool b_transparent = hasproperty(TRIANGLE_TRANSPARENT);
    if( texture != NULL )
    {
        return texture->isClear() || b_transparent;
    }
    else
    {
        POGEL::IMAGE * nullImage = POGEL::getNullImage();
        if(nullImage != NULL)
        {
            return nullImage->isClear() || b_transparent;
        }
    }
    return b_transparent;
}

void POGEL::TRIANGLE::draw()
{
    #ifdef OPENGL

    // set up the texture to use.
    bool usingTexture = true;
    if ( texture != NULL && texture->getbase() != (unsigned int)NULL && texture->isbuilt() )
    {
        texture->set();
    }
    else
    {
        POGEL::IMAGE * nullImage = POGEL::getNullImage();
        if ( nullImage != NULL && nullImage->getbase() != (unsigned int)NULL && nullImage->isbuilt() )
        {
            nullImage->set();
            //texture = nullImage;
        }
        else
        {
            usingTexture = false;
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
    bool b_invertnorms = this->hasproperty( TRIANGLE_INVERT_NORMALS );
    bool b_doublesided = this->hasproperty( TRIANGLE_DOUBLESIDED );
    bool b_transparent = this->hasproperty( TRIANGLE_TRANSPARENT );
    bool b_colorised   = this->hasproperty( TRIANGLE_COLORED );

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

    // if using triangle's flat normal set it
    if ( b_lit && !b_vertnorms )
    {
        glNormal3f( normal.x, normal.y, normal.z );
    }

    // this for loop is somehwat confusing, 4 times for wireframe, 3 for solid
    unsigned int max = b_wireframe ? 4 : 3;
    // loop from 3:4 to 0 or 0 to 3:4, because opengl uses CW or CCW to
    //  determine the front/back of the triangle.
    for ( unsigned int i = b_invertnorms ? max : 0 ; b_invertnorms ? i > 0 : i < max ; b_invertnorms ? i-- : i++ )
    {
        unsigned int ind = i % 3;

        // depretiated but might still be relevent later ...
        if ( vertex[ind].usable )
        {
            // the triangle will not be colored if GL_LIGHTING is enabled,
            //  don't know why.
            // set the color
            if ( b_colorised )
            {
                vertex[ind].color.set();
            }
            else
            {
                POGEL::COLOR( 1, 1, 1, 1 ).set();
            }

            // light the verticies
            if ( b_vertnorms )
            {
                glNormal3f( vertex[ind].normal.x, vertex[ind].normal.y, vertex[ind].normal.z );
            }

            // set the verticies' texture coordanates
            //if ( usingTexture )
            {
                glTexCoord2f( vertex[ind].u, vertex[ind].v );
            }

            // set the vertex
            glVertex3f( vertex[ind].x, vertex[ind].y, vertex[ind].z );
        }
    }

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
POGEL::TRIANGLE::operator = (const POGEL::TRIANGLE& t)
{
    properties = t.properties;
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
    normal = t.normal;
    return *this;
}
