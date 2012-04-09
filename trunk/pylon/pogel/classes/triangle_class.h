#ifndef _TRIANGLE_CLASS_H
#define _TRIANGLE_CLASS_H

namespace POGEL {
class TRIANGLE;
}

#include "point_class.h"
#include "line_class.h"
#include "image_class.h"
#include "matrix_class.h"
#include "bounding_class.h"
#include "../pogel_internals.h"

#define			TRIANGLE_LIT				2
#define			TRIANGLE_COLORED			4
#define			TRIANGLE_VERTEX_NORMALS		8
#define			TRIANGLE_INVERT_NORMALS		16
#define			TRIANGLE_TRANSPARENT		32
#define			TRIANGLE_DOUBLESIDED		64

namespace POGEL
{
    class TRIANGLE
    {
        public:
            POGEL::VERTEX vertex[3];     // the 3 verticies of the triangle
            POGEL::VECTOR vertnormals[3];
            POGEL::BOUNDING bounding;
            POGEL::VECTOR normal;        // the normal vector
        private:
            POGEL::POINT trimid;         // the middle of the reiangle
        public:
            int ivertex[3]; // pointers to 3 verticies used for animation
            unsigned int ivertlength; // number of things in the list of verticies
            POGEL::VERTEX * pvertex;  // pointers to the list of verticies used for animation
            POGEL::IMAGE * texture;      // a pointer to the image to use as the texture
        private:
            unsigned int properties;     // the mushed options
            bool usetrimid;              //
        public:

            TRIANGLE();
            TRIANGLE( const POGEL::POINT&, const POGEL::POINT&, const POGEL::POINT& );
            TRIANGLE( const POGEL::VERTEX&, const POGEL::VERTEX&, const POGEL::VERTEX&, POGEL::IMAGE*, unsigned int );
            TRIANGLE( const POGEL::POINT&, const POGEL::POINT&, const POGEL::POINT&, POGEL::IMAGE*, unsigned int );
            TRIANGLE( POGEL::VERTEX*, POGEL::IMAGE*, unsigned int );
            TRIANGLE( POGEL::VERTEX*, unsigned int, int, int, int, POGEL::IMAGE*, unsigned int );

            TRIANGLE( const std::string&, POGEL::IMAGE* );
            TRIANGLE( const std::string& );

            ~TRIANGLE();

            void updateVert();

            void load( const POGEL::VERTEX&, const POGEL::VERTEX&, const POGEL::VERTEX&, POGEL::IMAGE*, unsigned int );
            void load( POGEL::VERTEX*, POGEL::IMAGE*, unsigned int );

            void settexture( POGEL::IMAGE* );
            POGEL::IMAGE* gettexture() const;

            PROPERTIES_METHODS;

            std::string toString();

            void scroll_tex_values(float,float);

            void print() const;

            POGEL::LINE getEdge( unsigned int l ) const;

            POGEL::TRIANGLE transform( POGEL::MATRIX* );

            POGEL::POINT middle();
            POGEL::POINT middle() const;

            bool isinfront( const POGEL::POINT& ) const;

            bool distcheck( const POGEL::POINT&, float) const;

            float distance( const POGEL::POINT& ) const;

            void makebounding();

            POGEL::POINT getposition();
            POGEL::POINT getposition() const;
            POGEL::BOUNDING getbounding() const;

            bool isClear() const;

            inline void drawgeometry() const;

            void draw() const;

            POGEL::TRIANGLE& operator = ( const POGEL::TRIANGLE& );

            friend class POGEL::MATRIX;
    };

    void
    TRIANGLE::drawgeometry() const
    {
        // if using triangle's flat normal set it
        if ( properties & TRIANGLE_LIT && !( properties & TRIANGLE_VERTEX_NORMALS ) )
        {
            glNormal3f( normal.x, normal.y, normal.z );
        }

        if ( !properties & TRIANGLE_COLORED )
        {
            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
        }

        if( properties & TRIANGLE_INVERT_NORMALS )
        {
            for ( unsigned int a = 3; a > 0; --a )
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
                    glNormal3f( vertex[ i ].normal.x, vertex[ i ].normal.y, vertex[ i ].normal.z );
                }

                // set the verticies' texture coordanates
                glTexCoord2f( vertex[ i ].u, vertex[ i ].v );

                // set the vertex
                glVertex3f( vertex[ i ].x, vertex[ i ].y, vertex[ i ].z );
            }
        }
        else
        {
            for ( unsigned int i = 0; i < 3; ++i )
            {
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
                    glNormal3f( vertex[ i ].normal.x, vertex[ i ].normal.y, vertex[ i ].normal.z );
                }

                // set the verticies' texture coordanates
                glTexCoord2f( vertex[ i ].u, vertex[ i ].v );

                // set the vertex
                glVertex3f( vertex[ i ].x, vertex[ i ].y, vertex[ i ].z );
            }
        }

        if ( properties & TRIANGLE_COLORED )
        {
            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
        }
    }

}

#endif /* _TRIANGLE_CLASS_H */
