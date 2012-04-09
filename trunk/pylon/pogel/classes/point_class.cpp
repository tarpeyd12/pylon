#include <math.h>
#include "point_class.h"

POGEL::POINT::POINT() : x( 0.0f ), y( 0.0f ), z( 0.0f )
{
    //x = y = z = 0.0f;
}

POGEL::POINT::POINT( float a, float b, float c ) : x( a ), y( b ), z( c )
{
    /*x=a;
    y=b;
    z=c;*/
}

POGEL::POINT::POINT( float a ) : x( a ), y( a ), z( a )
{
    //x = y = z = a;
}

POGEL::POINT::POINT( const std::string& s )
{
    sscanf( s.c_str(), "{[%f],[%f],[%f]}", &x, &y, &z );
}

POGEL::VECTOR::VECTOR()
{
    //x = y = z = 0.0f;
}

POGEL::VECTOR::VECTOR(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
}

POGEL::VECTOR::VECTOR(POGEL::POINT p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}

POGEL::VECTOR::VECTOR(POGEL::POINT p1, POGEL::POINT p2)
{
    this->frompoints(p1, p2);
}

POGEL::VECTOR::VECTOR(std::string s)
{
    sscanf(s.c_str(), "{[%f],[%f],[%f]}", &x, &y, &z);
}

POGEL::VERTEX::VERTEX()
{
    //x=y=z=u=v=0.0f;
    u=v=0.0f;
    //boneID = boneIDs[0] = boneIDs[1] = boneIDs[2] = -1;
    boneID = -1;
    //weights[0] = weights[1] = weights[2] = 0;
    usable=true;
}

POGEL::VERTEX::VERTEX(float a, float b, float c, float s, float t) : POGEL::POINT(a,b,c)
{
    /*x=a;
    y=b;
    z=c;*/
    u=s;
    v=t;
    boneID = boneIDs[0] = boneIDs[1] = boneIDs[2] = -1;
    weights[0] = weights[1] = weights[2] = 0;
    usable=true;
}

POGEL::VERTEX::VERTEX(float a, float b, float c) : POGEL::POINT(a,b,c)
{
    /*x=a;
    y=b;
    z=c;*/
    u = v = 0.0f;
    boneID = boneIDs[0] = boneIDs[1] = boneIDs[2] = -1;
    weights[0] = weights[1] = weights[2] = 0;
    usable = true;
}

POGEL::VERTEX::VERTEX(const POGEL::POINT& p) : POGEL::POINT(p)
{
    /*x=p.x;
    y=p.y;
    z=p.z;*/
    u = v = 0.0f;
    boneID = boneIDs[0] = boneIDs[1] = boneIDs[2] = -1;
    weights[0] = weights[1] = weights[2] = 0;
    usable=true;
}

POGEL::VERTEX::VERTEX(std::string s)
{
    std::string n = POGEL::getStringComponentLevel('{','}', s, "0 0");
    std::string c = POGEL::getStringComponentLevel('{','}', s, "0 1");
    std::string fmt = "{[%f],[%f],[%f],[%f],[%f],"+n+","+c+"}";
    sscanf(s.c_str(), fmt.c_str(), &x, &y, &z, &u, &v);
    normal = POGEL::VECTOR(n);
    color = POGEL::COLOR(c);
    boneID = boneIDs[0] = boneIDs[1] = boneIDs[2] = -1;
    weights[0] = weights[1] = weights[2] = 0;
    usable=true;
}

POGEL::KEY::KEY() : POGEL::POINT(), time( 0.0f )
{
    //time = x = y = z = 0.0f;
}

POGEL::KEY::KEY(const POGEL::POINT& p, float t) : POGEL::POINT( p ), time( t )
{
    /*time = t;
    x = p.x;
    y = p.y;
    z = p.z;*/
}

POGEL::TANGENT::TANGENT() : in(), out()
{
    //in = out = POGEL::POINT();
}

POGEL::TANGENT::TANGENT( const POGEL::POINT& i, const POGEL::POINT& o) : in( i ), out( o )
{
    /*in = i;
    out = o;*/
}
