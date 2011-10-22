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

	vct[0].frompoints(vertex[0].topoint(),vertex[1].topoint());
	vct[0].normalize();
	vct[1].frompoints(vertex[0].topoint(),vertex[2].topoint());
	vct[1].normalize();

	vct[0].dodotproduct(vct[1]);
	normal=vct[0];
	normal.normalize();
	bounding = POGEL::BOUNDING(BOUNDING_TRIANGLE);
	makebounding();
};

void POGEL::TRIANGLE::load(POGEL::VERTEX* verts,POGEL::IMAGE *tex,unsigned int prop) {
	if(verts!=NULL)
		load(verts[0],verts[1],verts[2],tex,prop);
	else printf("triangle loading failed, null pointer to vertex array.\n");
};

void POGEL::TRIANGLE::scroll_tex_values(float s, float t) {
	for(int i=0;i<3;i++) vertex[i].scroll_tex_values(s,t);
};

POGEL::TRIANGLE POGEL::TRIANGLE::transform(POGEL::MATRIX* m) {
	POGEL::TRIANGLE t(vertex, texture, properties);
	m->transformTriangle(&t);
	t.makebounding();
	return t;
};

POGEL::POINT POGEL::TRIANGLE::middle() {
	POGEL::POINT p;
	p.x=(vertex[0].x+vertex[1].x+vertex[2].x)/3;
	p.y=(vertex[0].y+vertex[1].y+vertex[2].y)/3;
	p.z=(vertex[0].z+vertex[1].z+vertex[2].z)/3;
	return p;
};

bool POGEL::TRIANGLE::isinfront(POGEL::POINT p) {
    POGEL::VECTOR vect;
    vect = hasproperty(TRIANGLE_INVERT_NORMALS) ? normal*-1.0f : normal;
    return vect.dotproduct(p+middle()) < 0.0f;
};

bool POGEL::TRIANGLE::distcheck(POGEL::POINT p, float dist) {
	POGEL::POINT closest = middle();
	POGEL::POINT points[] = {
		middle(), \
		vertex[0].topoint(), \
		vertex[1].topoint(), \
		vertex[2].topoint(), \
		((vertex[0]+vertex[1])/2.0f).topoint(), \
		((vertex[0]+vertex[2])/2.0f).topoint(), \
		((vertex[1]+vertex[2])/2.0f).topoint(), \
		(vertex[0].topoint()+closest)/2.0f, \
		(vertex[1].topoint()+closest)/2.0f, \
		(vertex[2].topoint()+closest)/2.0f
	};

	for(int i=0;i<1;i++)
		if(p.distance(points[i]) <= dist)
			return true;
	return false;
};

float POGEL::TRIANGLE::distance(POGEL::POINT p) {
	POGEL::POINT mid = middle();
	float dist = 0.0f;// p.distance(mid);
	POGEL::POINT points[] = {
		mid, \
		vertex[0].topoint(), \
		vertex[1].topoint(), \
		vertex[2].topoint(), \
		((vertex[0]+vertex[1])/2.0f).topoint(), \
		((vertex[0]+vertex[2])/2.0f).topoint(), \
		((vertex[1]+vertex[2])/2.0f).topoint(), \
		(vertex[0].topoint()+mid)/2.0f, \
		(vertex[1].topoint()+mid)/2.0f, \
		(vertex[2].topoint()+mid)/2.0f
	};

	for(int i=0;i<10;i++)
		if(p.distance(points[i]) < dist)
			dist = p.distance(points[i]);
		//dist += p.distance(points[i]);
	return dist/10.0f;
};

void POGEL::TRIANGLE::makebounding() {
	bounding.clear();
	POGEL::POINT mid = middle();
	for(int i=0;i<3;i++)
		bounding.addpoint(mid, vertex[i].topoint());
	bounding.fin();
};

bool POGEL::TRIANGLE::isClear() {
    if( texture != NULL )
        return texture->isClear() || hasproperty(TRIANGLE_TRANSPARENT);
    else if(POGEL::getNullImage() != NULL)
        return POGEL::getNullImage()->isClear() || hasproperty(TRIANGLE_TRANSPARENT);
    return hasproperty(TRIANGLE_TRANSPARENT);
};

void POGEL::TRIANGLE::draw()
{
    #ifdef OPENGL

    // draw the triangle's bounding box
    if ( POGEL::hasproperty(POGEL_BOUNDING) )
        bounding.draw( POGEL::POINT() );

    // set up the texture to use.
    POGEL::IMAGE* nullImage = POGEL::getNullImage();
    bool usingTexture = true;
    if ( texture != NULL && texture->getbase() != (unsigned int)NULL )
        texture->set();
    else if ( nullImage != NULL && nullImage->getbase() != (unsigned int)NULL )
        nullImage->set();
    else
        usingTexture = false;

    // enable or disable lighting
    if (
        ( hasproperty(TRIANGLE_LIT) || hasproperty(TRIANGLE_VERTEX_NORMALS) ) &&
        !POGEL::hasproperty(POGEL_WIREFRAME)
    )
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);

    // set the transparency
    bool blendEnabled = false;
    if ( hasproperty(TRIANGLE_TRANSPARENT) )
    {
        blendEnabled = glIsEnabled( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glEnable( GL_BLEND );
    }

    // begin either a solid face or lines for wireframe
    if ( POGEL::hasproperty(POGEL_WIREFRAME) )
        glBegin(GL_LINES);
    else
        glBegin(GL_TRIANGLES);

    // if using triangles flat normal set it
    if ( hasproperty(TRIANGLE_LIT) && !hasproperty(TRIANGLE_VERTEX_NORMALS) )
        glNormal3f( normal.x, normal.y, normal.z );

    // this for loop is somehwat confusing, 4 times for wireframe, 3 for solid
    unsigned int max = POGEL::hasproperty(POGEL_WIREFRAME) ? 4 : 3;
    // loop from 3:4 to 0 or 0 to 3:4, because opengl uses CW or CCW to
    //  determine the front/back of the triangle.
    for (
        unsigned int i = hasproperty(TRIANGLE_INVERT_NORMALS) ? max : 0 ;
        hasproperty(TRIANGLE_INVERT_NORMALS) ? i > 0 : i < max ;
        hasproperty(TRIANGLE_INVERT_NORMALS) ? i-- : i++
    )
    {
        // depretiated but might still be relevent later ...
        if ( vertex[i%3].usable )
        {
            // the triangle will not be colored if GL_LIGHTING is enabled,
            //  don't know why.
            // set the color
            if ( hasproperty(TRIANGLE_COLORED) )
                vertex[i%3].color.set();
            else
                POGEL::COLOR( 1, 1, 1, 1 ).set();

            // light the verticies
            if (
                !hasproperty(TRIANGLE_LIT) &&
                hasproperty(TRIANGLE_VERTEX_NORMALS)
            )
                glNormal3f(
                           vertex[i%3].normal.x,
                           vertex[i%3].normal.y,
                           vertex[i%3].normal.z
                );

            // set the verticies' texture coordanates
            if ( usingTexture )
                glTexCoord2f( vertex[i%3].u, vertex[i%3].v );

            // set the vertex
            glVertex3f( vertex[i%3].x, vertex[i%3].y, vertex[i%3].z );
        }
    }

    // end GL_TRIANGLES or GL_LINES
    glEnd();

    // disable the transparency
    if ( hasproperty(TRIANGLE_TRANSPARENT) )
    {
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        if( !blendEnabled )
            glDisable( GL_BLEND );
    }

    #endif
};
