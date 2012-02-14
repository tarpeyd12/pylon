#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "triangle_class.h"
#include "physics/physics.h"

POGEL::TRIANGLE::TRIANGLE(std::string s, POGEL::IMAGE* im) {
	texture = im;
	sscanf(s.c_str(), "{[%u],", &this->properties);
	for(int i = 0; i < 3; i++) {
		char* vt = POGEL::string("0 %d",i);
		std::string v = POGEL::getStringComponentLevel('{','}', s, vt);
		vertex[i] = POGEL::VERTEX(v);
		#ifndef _WIN32
        free(vt);
        #endif
	}
	normal = POGEL::VECTOR(POGEL::getStringComponentLevel('{','}', s, "0 3"));
};

POGEL::TRIANGLE::TRIANGLE(std::string s) {
	//texture = NULL;
	sscanf(s.c_str(), "{[%u],", &this->properties);
	for(int i = 0; i < 3; i++) {
		char* vt = POGEL::string("0 %d",i);
		std::string v = POGEL::getStringComponentLevel('{','}', s, std::string(vt));
		vertex[i] = POGEL::VERTEX(v);
		#ifndef _WIN32
        free(vt);
        #endif
	}
	normal = POGEL::VECTOR(POGEL::getStringComponentLevel('{','}', s, "0 3"));
	texture = POGEL::requestImage(POGEL::getStringComponentLevel('{','}', s, "0 4"));
};

void POGEL::TRIANGLE::load(POGEL::VERTEX a,POGEL::VERTEX b,POGEL::VERTEX c,POGEL::IMAGE *tex,unsigned int prop) {
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
	makebounding();
};

void POGEL::TRIANGLE::load(POGEL::VERTEX* verts,POGEL::IMAGE *tex,unsigned int prop) {
	if(verts!=NULL)
		load(verts[0],verts[1],verts[2],tex,prop);
	else printf("triangle loading failed, null pointer to vertex array.\n");
};

void POGEL::TRIANGLE::scroll_tex_values(float s, float t) {
	vertex[0].scroll_tex_values(s,t);
	vertex[1].scroll_tex_values(s,t);
	vertex[2].scroll_tex_values(s,t);
};

POGEL::TRIANGLE POGEL::TRIANGLE::transform(POGEL::MATRIX* m) {
	POGEL::TRIANGLE t(vertex, texture, properties);
	m->transformTriangle(&t);
	t.makebounding();
	return t;
};

POGEL::POINT POGEL::TRIANGLE::middle() {
	return (vertex[0]+vertex[1]+vertex[2])/3.0f;
};

bool POGEL::TRIANGLE::isinfront(POGEL::POINT p) {
    POGEL::VECTOR vect;
    vect = hasproperty(TRIANGLE_INVERT_NORMALS) ? normal*-1.0f : normal;
    return vect.dotproduct(p+middle()) < 0.0f;
};

bool POGEL::TRIANGLE::distcheck(POGEL::POINT p, float dist) {
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
		if(p.distance(points[i]) <= dist)
			return true;
	return false;
};

float POGEL::TRIANGLE::distance(POGEL::POINT p) {
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
		if(p.distance(points[i]) < dist)
			dist = p.distance(points[i]);
		//dist += p.distance(points[i]);
	return dist;//10.0f;
};

void POGEL::TRIANGLE::makebounding() {
	bounding.clear();
	POGEL::POINT mid = middle();
	bounding.addpoint(mid, vertex[0]);
	bounding.addpoint(mid, vertex[1]);
	bounding.addpoint(mid, vertex[2]);
	bounding.fin();
};

bool POGEL::TRIANGLE::isClear() {
    if( texture != NULL )
        return texture->isClear() || hasproperty(TRIANGLE_TRANSPARENT);
    else
    {
        POGEL::IMAGE * nullImage = POGEL::getNullImage();
        if(nullImage != NULL)
            return nullImage->isClear() || hasproperty(TRIANGLE_TRANSPARENT);
    }
    return hasproperty(TRIANGLE_TRANSPARENT);
};

void POGEL::TRIANGLE::draw()
{
    #ifdef OPENGL

    bool b_bounding   = POGEL::hasproperty( POGEL_BOUNDING );
    bool b_wireframe  = POGEL::hasproperty( POGEL_WIREFRAME );
    bool b_lit         = this->hasproperty( TRIANGLE_LIT );
    bool b_vertnorms   = this->hasproperty( TRIANGLE_VERTEX_NORMALS );
    bool b_invertnorms = this->hasproperty( TRIANGLE_INVERT_NORMALS );
    bool b_doublesided = this->hasproperty( TRIANGLE_DOUBLESIDED );
    bool b_transparent = this->hasproperty( TRIANGLE_TRANSPARENT );
    bool b_colorised   = this->hasproperty( TRIANGLE_COLORED );

    // draw the triangle's bounding box
    if ( b_bounding )
    {
        bounding.draw( POGEL::POINT() );
    }

    // set up the texture to use.
    bool usingTexture = true;
    if ( texture != NULL && texture->getbase() != (unsigned int)NULL )
    {
        texture->set();
    }
    else
    {
        POGEL::IMAGE * nullImage = POGEL::getNullImage();
        if ( nullImage != NULL && nullImage->getbase() != (unsigned int)NULL )
        {
            nullImage->set();
            texture = nullImage;
        }
        else
        {
            usingTexture = false;
            return;
        }
    }

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
    }
    else if ( glIsEnabled( GL_CULL_FACE ) )
    {
        glDisable( GL_CULL_FACE );
    }

    // set the transparency
    bool blendEnabled = false;
    if ( b_transparent )
    {
        blendEnabled = glIsEnabled( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        if ( !blendEnabled )
        {
            glEnable( GL_BLEND );
        }
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
            if ( !b_lit && b_vertnorms )
            {
                glNormal3f( vertex[ind].normal.x, vertex[ind].normal.y, vertex[ind].normal.z );
            }

            // set the verticies' texture coordanates
            if ( usingTexture )
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
};
