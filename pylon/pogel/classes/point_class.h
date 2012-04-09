#ifndef _POINT_CLASS_H
#define _POINT_CLASS_H

#include <stdio.h>
#include <math.h>

#include "misc_class.h"
#include "../pogel_internals.h"

namespace POGEL
{
    class POINT
    {
        public:
            float x;
            float y;
            float z;

            POINT();
            POINT( float, float, float );
            POINT( float );

            POINT( const std::string& );

            inline void get_values( float*, float*, float* ) const;
            inline void set_values( float, float, float );

            inline void print() const;

            inline std::string toString() const;

            inline void draw() const;
            inline void draw( unsigned int ) const;
            inline void draw( unsigned int, const POGEL::COLOR& ) const;
            inline void drawto( const POGEL::POINT& ) const;

            inline void translate() const;

            inline float distance( const POGEL::POINT& ) const;
            inline float distancesquared( const POGEL::POINT& ) const;

            inline POGEL::POINT operator*( float ) const;
            inline POGEL::POINT operator/( float ) const;

            inline POGEL::POINT operator*( const POGEL::POINT& ) const;
            inline POGEL::POINT operator/( const POGEL::POINT& ) const;

            inline POGEL::POINT operator+( const POGEL::POINT& ) const;
            inline POGEL::POINT operator-( const POGEL::POINT& ) const;

            inline POGEL::POINT& operator=( const POGEL::POINT& );

            inline POGEL::POINT& operator*=( const float& );
            inline POGEL::POINT& operator/=( const float& );

            inline POGEL::POINT& operator*=( const POGEL::POINT& );
            inline POGEL::POINT& operator/=( const POGEL::POINT& );

            inline POGEL::POINT& operator+=( const POGEL::POINT& );
            inline POGEL::POINT& operator-=( const POGEL::POINT& );

            inline bool operator==( const POGEL::POINT& ) const;
            inline bool operator!=( const POGEL::POINT& ) const;

            inline bool isbad() const;
    };

    class VECTOR : public POGEL::POINT
    {
        public:
            VECTOR();
            VECTOR(float,float,float);
            VECTOR(POGEL::POINT);
            VECTOR(POGEL::POINT,POGEL::POINT);

            VECTOR(std::string s);

            inline void normalize();
            inline POGEL::VECTOR normal() const;
            inline void anglenormalize();
            inline POGEL::VECTOR anglenormal() const;
            inline float getdistance() const;
            inline float getangle( const POGEL::VECTOR&, const POGEL::VECTOR& );
            inline float getangle( const POGEL::VECTOR& );
            inline POGEL::VECTOR& dodotproduct( const POGEL::VECTOR& );
            inline float dotproduct( const POGEL::VECTOR&) const;
            inline void frompoints( const POGEL::POINT&, const POGEL::POINT& );

            inline POGEL::POINT topoint() const;

            inline POGEL::VECTOR operator*(float a);
            inline POGEL::VECTOR operator/(float a);

            inline POGEL::VECTOR operator*( const POGEL::VECTOR& p) const;
            inline POGEL::VECTOR operator/( const POGEL::VECTOR& p) const;

            inline POGEL::VECTOR operator+( const POGEL::VECTOR& p) const;
            inline POGEL::VECTOR operator-( const POGEL::VECTOR& p) const;

            inline POGEL::VECTOR& operator=(const POGEL::VECTOR & p);

            inline POGEL::VECTOR& operator*=(const float& a);
            inline POGEL::VECTOR& operator/=(const float& a);

            inline POGEL::VECTOR& operator*=(const POGEL::VECTOR& p);
            inline POGEL::VECTOR& operator/=(const POGEL::VECTOR& p);

            inline POGEL::VECTOR& operator+=(const POGEL::VECTOR& p);
            inline POGEL::VECTOR& operator-=(const POGEL::VECTOR& p);

            inline bool operator==( const POGEL::VECTOR& p) const;
            inline bool operator!=( const POGEL::VECTOR& p) const;
    };

    class VERTEX : public POGEL::POINT
    {
        public:
            POGEL::COLOR color;
            POGEL::VECTOR normal;
            int boneIDs[3];
            float u;
            float v;
            int boneID;
            unsigned char weights[3];
            bool usable;

            VERTEX();
            VERTEX(float a, float b, float c, float s, float t);
            VERTEX(float a, float b, float c);
            VERTEX(const POGEL::POINT& p);

            VERTEX(std::string s);

            inline std::string toString();

            inline void get_values(float *a, float *b, float *c, float *s, float *t);
            inline void set_values(float a, float b, float c, float s, float t);

            inline void get_point_values(float *a, float *b, float *c);
            inline void set_point_values(float a, float b, float c);

            inline void get_tex_values(float *s, float *t);
            inline void set_tex_values(float s, float t);

            inline void scroll_tex_values(float s, float t);

            inline POGEL::POINT topoint();

            inline POGEL::VERTEX operator*(float a) const;
            inline POGEL::VERTEX operator/(float a) const;

            inline POGEL::VERTEX operator*(POGEL::VERTEX p) const;
            inline POGEL::VERTEX operator/(POGEL::VERTEX p) const;

            inline POGEL::VERTEX operator+(POGEL::VERTEX p) const;
            inline POGEL::VERTEX operator-(POGEL::VERTEX p) const;

            inline POGEL::VERTEX& operator=(const POGEL::VERTEX& p);
            inline POGEL::VERTEX& operator=(const POGEL::POINT& p);

            inline POGEL::VERTEX& operator*=(const float& a);
            inline POGEL::VERTEX& operator/=(const float& a);

            inline POGEL::VERTEX& operator*=(const POGEL::VERTEX& p);
            inline POGEL::VERTEX& operator/=(const POGEL::VERTEX& p);

            inline POGEL::VERTEX& operator+=(const POGEL::VERTEX& p);
            inline POGEL::VERTEX& operator-=(const POGEL::VERTEX& p);
    };

    class KEY : public POGEL::POINT
    {
        public:
            float time;
            KEY();
            KEY( const POGEL::POINT&, float );
    };

    class TANGENT
    {
        public:
            POGEL::POINT in;
            POGEL::POINT out;
            TANGENT();
            TANGENT( const POGEL::POINT&, const POGEL::POINT& );
    };
}

#include "point_class_inline.h"

#endif /* _POINT_CLASS_H */
