#ifndef _POINT_CLASS_H
#define _POINT_CLASS_H

#include <stdio.h>
#include <math.h>

//class POGEL::POINT;
//class POGEL::VECTOR;
//class POGEL::VERTEX;

#include "misc_class.h"
#include "../pogel_internals.h"

namespace POGEL {
class POINT {
    public:
        float x;
        float y;
        float z;

        POINT();
        POINT(float,float,float);
        POINT(float);

        POINT(std::string s);

        void get_values(float*,float*,float*);
        void set_values(float,float,float);

        void print();

        std::string toString();

        void draw();
        void draw(unsigned int);
        void draw(unsigned int, POGEL::COLOR);
        void drawto(POGEL::POINT);

        void translate();

        float distance(POGEL::POINT p);

        POGEL::POINT operator*(float a);
        POGEL::POINT operator/(float a);

        POGEL::POINT operator*(POGEL::POINT p);
        POGEL::POINT operator/(POGEL::POINT p);

        POGEL::POINT operator+(POGEL::POINT p);
        POGEL::POINT operator-(POGEL::POINT p);
        POGEL::POINT& operator=(const POGEL::POINT& p);

        POGEL::POINT& operator*=(const float& a);
        POGEL::POINT& operator/=(const float& a);

        POGEL::POINT& operator*=(const POGEL::POINT& p);
        POGEL::POINT& operator/=(const POGEL::POINT& p);

        POGEL::POINT& operator+=(const POGEL::POINT& p);
        POGEL::POINT& operator-=(const POGEL::POINT& p);

        bool operator==(POGEL::POINT p);
        bool operator!=(POGEL::POINT p);

        bool isbad();
};

class VECTOR: public POGEL::POINT {
    public:
        VECTOR();
        VECTOR(float,float,float);
        VECTOR(POGEL::POINT);
        VECTOR(POGEL::POINT,POGEL::POINT);

        VECTOR(std::string s);

        void normalize();
        POGEL::VECTOR normal();
        void anglenormalize();
        POGEL::VECTOR anglenormal();
        float getdistance();
        float getangle(POGEL::VECTOR,POGEL::VECTOR);
        float getangle(POGEL::VECTOR);
        POGEL::VECTOR& dodotproduct(POGEL::VECTOR);
        float dotproduct(POGEL::VECTOR);
        void frompoints(POGEL::POINT,POGEL::POINT);

        POGEL::POINT topoint();

        POGEL::VECTOR operator*(float a);
        POGEL::VECTOR operator/(float a);

        POGEL::VECTOR operator*(POGEL::VECTOR p);
        POGEL::VECTOR operator/(POGEL::VECTOR p);

        POGEL::VECTOR operator+(POGEL::VECTOR p);
        POGEL::VECTOR operator-(POGEL::VECTOR p);

        POGEL::VECTOR& operator=(const POGEL::VECTOR p);

        POGEL::VECTOR& operator*=(const float& a);
        POGEL::VECTOR& operator/=(const float& a);

        POGEL::VECTOR& operator*=(const POGEL::VECTOR& p);
        POGEL::VECTOR& operator/=(const POGEL::VECTOR& p);

        POGEL::VECTOR& operator+=(const POGEL::VECTOR& p);
        POGEL::VECTOR& operator-=(const POGEL::VECTOR& p);

        bool operator==(POGEL::VECTOR p);
        bool operator!=(POGEL::VECTOR p);
};

class VERTEX: public POGEL::POINT {
    public:
        float u;
        float v;
        POGEL::COLOR color;
        POGEL::VECTOR normal;
        bool usable;

        VERTEX();
        VERTEX(float a, float b, float c, float s, float t);
        VERTEX(float a, float b, float c);
        VERTEX(POGEL::POINT p);

        VERTEX(std::string s);

        std::string toString();

        void get_values(float *a, float *b, float *c, float *s, float *t);
        void set_values(float a, float b, float c, float s, float t);

        void get_point_values(float *a, float *b, float *c);
        void set_point_values(float a, float b, float c);

        void get_tex_values(float *s, float *t);
        void set_tex_values(float s, float t);

        void scroll_tex_values(float s, float t);

        POGEL::POINT topoint();

        POGEL::VERTEX operator*(float a);
        POGEL::VERTEX operator/(float a);

        POGEL::VERTEX operator*(POGEL::VERTEX p);
        POGEL::VERTEX operator/(POGEL::VERTEX p);

        POGEL::VERTEX operator+(POGEL::VERTEX p);
        POGEL::VERTEX operator-(POGEL::VERTEX p);
        POGEL::VERTEX& operator=(const POGEL::VERTEX& p);

        POGEL::VERTEX& operator*=(const float& a);
        POGEL::VERTEX& operator/=(const float& a);

        POGEL::VERTEX& operator*=(const POGEL::VERTEX& p);
        POGEL::VERTEX& operator/=(const POGEL::VERTEX& p);

        POGEL::VERTEX& operator+=(const POGEL::VERTEX& p);
        POGEL::VERTEX& operator-=(const POGEL::VERTEX& p);
};
}

#endif /* _POINT_CLASS_H */
