#ifndef _MATRIX_CLASS_H
#define _MATRIX_CLASS_H

#ifdef OPENGL
#include <GL/gl.h>
#endif
#include <math.h>

namespace POGEL
{
    class MATRIX;
}

#include "quat_class.h"
#include "point_class.h"
#include "triangle_class.h"
#include "../pogel_internals.h"

#ifndef PI
    #define PI 3.14159265358979323846
#endif

//#define				MATRIX_ROTATE_XYZ				2
//#define				MATRIX_ROTATE_ZYX				4
//#define				MATRIX_ROTATE_FIRST				8
//#define				MATRIX_

#define				MATRIX_CONSTRUCT_X_ROTATION		0
#define				MATRIX_CONSTRUCT_Y_ROTATION		1
#define				MATRIX_CONSTRUCT_Z_ROTATION		2

#define				MATRIX_CONSTRUCT_ROTATION		0
#define				MATRIX_CONSTRUCT_TRANSLATION	1
#define				MATRIX_CONSTRUCT_SCALE			2

namespace POGEL
{
    //float RadiansToDegrees(float);
    //float DegreesToRadians(float);

    inline float
    RadiansToDegrees(float r)
    {
        // does what it says
        return (r / PI) * 180.0f;
    }

    inline float
    DegreesToRadians(float d)
    {
        // ditto
        return (d / 180.0f) * PI;
    }

    class MATRIX
    {
        public:
            float matrix[16];

            MATRIX();
            MATRIX(float*);
            MATRIX(const POGEL::MATRIX&);
            MATRIX(float,int);
            MATRIX(POGEL::POINT,int);
            MATRIX(POGEL::VECTOR,float);
            MATRIX(POGEL::POINT,POGEL::POINT);

            ~MATRIX()
            {

            }

            void get()
            {
                #ifdef OPENGL
                    glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
                #endif
            }

            void set(float*);
            void set(const POGEL::MATRIX&);

            POGEL::POINT getposition() const;
            POGEL::POINT getrotation() const;

            float *getcolumn(int) const;
            float *getrow(int) const;

            inline float getvalue(int c, int r) const
            {
                return matrix[c*4+r];
            }

            inline void  setvalue(int c, int r, float v)
            {
                matrix[c*4+r]=v;
            }

            void multiplyby(float);
            void raistopower(int);

            float determinant() const;
            bool invert();

            void print() const;

            inline void transformPoint(POGEL::POINT*);
            inline POGEL::POINT transformPoint(const POGEL::POINT&) const;

            inline void transformVector(POGEL::VECTOR*);
            inline POGEL::VECTOR transformVector(const POGEL::VECTOR&) const;

            inline void transformVertex(POGEL::VERTEX*);
            inline POGEL::VERTEX transformVertex(const POGEL::VERTEX&) const;

            void transformTriangle(POGEL::TRIANGLE*);
            POGEL::TRIANGLE transformTriangle(const POGEL::TRIANGLE&) const;

            QUAT toquat() const;

            void fromaxis(const POGEL::VECTOR&,float);

            POGEL::MATRIX operator+(const POGEL::MATRIX&) const;
            POGEL::MATRIX operator-(const POGEL::MATRIX&) const;
            POGEL::MATRIX operator*(const POGEL::MATRIX&) const;
            POGEL::MATRIX operator*(float a) const;
            POGEL::MATRIX operator/(float a) const;
            POGEL::MATRIX& operator=(const POGEL::MATRIX&);

            //friend class QUAT;
    };
}

inline void
POGEL::MATRIX::transformPoint(POGEL::POINT* p)
{
    POGEL::POINT tmp( *p );
    p->x = tmp.x * matrix[ 0] + tmp.y * matrix[ 4] + tmp.z * matrix[ 8] + matrix[12];
    p->y = tmp.x * matrix[ 1] + tmp.y * matrix[ 5] + tmp.z * matrix[ 9] + matrix[13];
    p->z = tmp.x * matrix[ 2] + tmp.y * matrix[ 6] + tmp.z * matrix[10] + matrix[14];
}

inline POGEL::POINT
POGEL::MATRIX::transformPoint(const POGEL::POINT& p) const
{
    return POGEL::POINT(p.x * matrix[ 0] + p.y * matrix[ 4] + p.z * matrix[ 8] + matrix[12],
                        p.x * matrix[ 1] + p.y * matrix[ 5] + p.z * matrix[ 9] + matrix[13],
                        p.x * matrix[ 2] + p.y * matrix[ 6] + p.z * matrix[10] + matrix[14]);
}

inline void
POGEL::MATRIX::transformVector(POGEL::VECTOR* v)
{
    // transforms the VECTOR 'v' by the rotation of the matrix
    POGEL::VECTOR tmp( *v );
    v->x = tmp.x * matrix[ 0] + tmp.y * matrix[ 4] + tmp.z * matrix[ 8];
    v->y = tmp.x * matrix[ 1] + tmp.y * matrix[ 5] + tmp.z * matrix[ 9];
    v->z = tmp.x * matrix[ 2] + tmp.y * matrix[ 6] + tmp.z * matrix[10];
}

inline POGEL::VECTOR
POGEL::MATRIX::transformVector(const POGEL::VECTOR& v) const
{
    // transforms the VECTOR 'v' by the rotation of the matrix
    return POGEL::VECTOR(v.x * matrix[ 0] + v.y * matrix[ 4] + v.z * matrix[ 8],
                         v.x * matrix[ 1] + v.y * matrix[ 5] + v.z * matrix[ 9],
                         v.x * matrix[ 2] + v.y * matrix[ 6] + v.z * matrix[10]);
}

inline void
POGEL::MATRIX::transformVertex(POGEL::VERTEX* v)
{
    // get the vector from center to vertex v, then get its length,
    // normalize it, transform it myltiply it by the vector length,
    // then use that as the new vertex. or do the same as converting a vector 'cause it's simpler
    POGEL::POINT tmp( *v );
    v->x = tmp.x * matrix[ 0] + tmp.y * matrix[ 4] + tmp.z * matrix[ 8] + matrix[12];
    v->y = tmp.x * matrix[ 1] + tmp.y * matrix[ 5] + tmp.z * matrix[ 9] + matrix[13];
    v->z = tmp.x * matrix[ 2] + tmp.y * matrix[ 6] + tmp.z * matrix[10] + matrix[14];
    // now transform the normal vector
    transformVector(&v->normal);
}

inline POGEL::VERTEX
POGEL::MATRIX::transformVertex(const POGEL::VERTEX& v) const
{
    POGEL::VERTEX tmp( v );
    tmp.x = v.x * matrix[ 0] + v.y * matrix[ 4] + v.z * matrix[ 8] + matrix[12];
    tmp.y = v.x * matrix[ 1] + v.y * matrix[ 5] + v.z * matrix[ 9] + matrix[13];
    tmp.z = v.x * matrix[ 2] + v.y * matrix[ 6] + v.z * matrix[10] + matrix[14];
    // now transform the normal vector
    tmp.normal = transformVector( v.normal );
    return tmp;
}

#endif /* _MATRIX_CLASS_H */
