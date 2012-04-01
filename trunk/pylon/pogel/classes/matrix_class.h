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
    float RadiansToDegrees(float);
    float DegreesToRadians(float);

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
            void set(POGEL::MATRIX);

            POGEL::POINT getposition();
            POGEL::POINT getrotation();

            float *getcolumn(int);
            float *getrow(int);

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

            float determinant();
            bool invert();

            void print();

            void transformPoint(POGEL::POINT*);
            POGEL::POINT transformPoint(POGEL::POINT);

            void transformVector(POGEL::VECTOR*);
            POGEL::VECTOR transformVector(POGEL::VECTOR);

            void transformVertex(POGEL::VERTEX*);
            POGEL::VERTEX transformVertex(POGEL::VERTEX);

            void transformTriangle(POGEL::TRIANGLE*);
            POGEL::TRIANGLE transformTriangle(POGEL::TRIANGLE);

            QUAT toquat();

            void fromaxis(POGEL::VECTOR,float);

            POGEL::MATRIX operator+(POGEL::MATRIX);
            POGEL::MATRIX operator-(POGEL::MATRIX);
            POGEL::MATRIX operator*(POGEL::MATRIX);
            POGEL::MATRIX operator*(float a);
            POGEL::MATRIX operator/(float a);
            POGEL::MATRIX& operator=(const POGEL::MATRIX&);

            //friend class QUAT;
    };
}

#endif /* _MATRIX_CLASS_H */
