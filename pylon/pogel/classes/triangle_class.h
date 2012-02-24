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

namespace POGEL {
class TRIANGLE {
    private:
        unsigned int properties; // the mushed options
        POGEL::POINT trimid;
        bool usetrimid;
    public:
        POGEL::BOUNDING bounding;
        POGEL::VERTEX vertex[3]; // the 3 verticies of the triangle
        POGEL::IMAGE *texture; // a pointer to the image to use as the texture
        POGEL::VECTOR normal; // the normal vector

        TRIANGLE();
        TRIANGLE(POGEL::POINT,POGEL::POINT,POGEL::POINT);
        TRIANGLE(POGEL::VERTEX,POGEL::VERTEX,POGEL::VERTEX,POGEL::IMAGE*,unsigned int);
        TRIANGLE(POGEL::POINT,POGEL::POINT,POGEL::POINT,POGEL::IMAGE*,unsigned int);
        TRIANGLE(POGEL::VERTEX*,POGEL::IMAGE*,unsigned int);

        TRIANGLE(std::string, POGEL::IMAGE*);
        TRIANGLE(std::string);

        void load(POGEL::VERTEX,POGEL::VERTEX,POGEL::VERTEX,POGEL::IMAGE*,unsigned int);
        void load(POGEL::VERTEX*,POGEL::IMAGE*,unsigned int);

        void settexture(POGEL::IMAGE*);
        POGEL::IMAGE* gettexture();

        PROPERTIES_METHODS;

        std::string toString();

        void scroll_tex_values(float,float);

        void print();

        POGEL::LINE getEdge(unsigned int l);

        POGEL::TRIANGLE transform(POGEL::MATRIX*);

        POGEL::POINT middle();

        bool isinfront(POGEL::POINT);

        bool distcheck(POGEL::POINT, float);

        float distance(POGEL::POINT);

        void makebounding();

        POGEL::POINT getposition();
        POGEL::BOUNDING getbounding();

        bool isClear();

        void draw();
};
}

#endif /* _TRIANGLE_CLASS_H */
