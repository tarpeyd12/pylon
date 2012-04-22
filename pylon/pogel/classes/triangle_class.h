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
            POGEL::VERTEX vertex[3];      // the 3 verticies of the triangle
            POGEL::VECTOR vertnormals[3]; // pre-transformed normals per-vertex for animation
            POGEL::BOUNDING bounding;     // triangles bounding box
            POGEL::VECTOR normal;         // the whole triangles normal vector
        private:
            POGEL::POINT trimid;          // the middle of the triangle, for speed, pre-calculated
        public:
            int ivertex[3];               // indexes to 3 verticies used for animation
            unsigned int ivertlength;     // number of things in the list of verticies
            POGEL::VERTEX * pvertex;      // pointer to the list of verticies used for animation
            POGEL::IMAGE * texture;       // a pointer to the image to use as the texture
        private:
            unsigned int properties;      // the mushed options, for lighting coloring ect.
            bool usetrimid;               // pre-calculated center is accurate
        public:

            TRIANGLE() : ivertlength( 0 ), pvertex( NULL ), texture( NULL ), usetrimid( false )
            {
                memset( &ivertex, -1, sizeof(ivertex) );
            }
            TRIANGLE( const POGEL::POINT&, const POGEL::POINT&, const POGEL::POINT& );
            TRIANGLE( const POGEL::VERTEX&, const POGEL::VERTEX&, const POGEL::VERTEX&, POGEL::IMAGE*, unsigned int );
            TRIANGLE( const POGEL::POINT&, const POGEL::POINT&, const POGEL::POINT&, POGEL::IMAGE*, unsigned int );
            TRIANGLE( POGEL::VERTEX*, POGEL::IMAGE*, unsigned int );
            TRIANGLE( POGEL::VERTEX*, unsigned int, int, int, int, POGEL::IMAGE*, unsigned int );

            TRIANGLE( const std::string&, POGEL::IMAGE* );
            TRIANGLE( const std::string& );

            ~TRIANGLE();

            inline void updateVert();

            inline void load( const POGEL::VERTEX&, const POGEL::VERTEX&, const POGEL::VERTEX&, POGEL::IMAGE*, unsigned int );
            inline void load( POGEL::VERTEX*, POGEL::IMAGE*, unsigned int );

            inline void settexture( POGEL::IMAGE* );
            inline POGEL::IMAGE* gettexture() const;

            PROPERTIES_METHODS;

            inline std::string toString();

            inline void scroll_tex_values(float,float);

            inline void print() const;

            inline POGEL::LINE getEdge( unsigned int l ) const;

            POGEL::TRIANGLE transform( POGEL::MATRIX* );

            inline POGEL::POINT middle();
            inline POGEL::POINT middle() const;

            inline bool isinfront( const POGEL::POINT& ) const;

            inline bool distcheck( const POGEL::POINT&, float) const;

            inline float distance( const POGEL::POINT& ) const;

            inline void makebounding();

            inline POGEL::POINT getposition();
            inline POGEL::POINT getposition() const;
            inline POGEL::BOUNDING getbounding() const;

            inline bool isClear() const;

            inline bool settriangletexture() const;
            inline void initializetriangledraw() const;
            inline void drawgeometry() const;
            inline void finalizetriangledraw() const;

            void draw() const;

            inline POGEL::TRIANGLE& operator = ( const POGEL::TRIANGLE& );

            friend class POGEL::MATRIX;
    };

    void drawTriangleList( TRIANGLE * face, unsigned int numfaces );
    void drawTriangleList( void * list, unsigned int length, TRIANGLE * (*accessor)(void*,unsigned int) );

    template < class Accessor >
    inline void drawTriangleList( void * list, unsigned int length, Accessor accessor );

}

#include "triangle_class_inline.h"

#endif /* _TRIANGLE_CLASS_H */
