#include <math.h>
#include "point_class.h"

/*POGEL::POINT::POINT() : x( 0.0f ), y( 0.0f ), z( 0.0f )
{

}*/

/*POGEL::POINT::POINT( float a, float b, float c ) : x( a ), y( b ), z( c )
{

}*/

/*POGEL::POINT::POINT( float a ) : x( a ), y( a ), z( a )
{

}*/

POGEL::POINT::POINT( const std::string& s )
{
    sscanf( s.c_str(), "{[%f],[%f],[%f]}", &x, &y, &z );
}

/*POGEL::VECTOR::VECTOR()
{

}*/

/*POGEL::VECTOR::VECTOR( float a, float b, float c ) : POGEL::POINT(a,b,c)
{

}*/

/*POGEL::VECTOR::VECTOR( const POGEL::POINT& p )  : POGEL::POINT( p.x, p.y, p.z )
{

}*/

/*POGEL::VECTOR::VECTOR( const POGEL::POINT& p1, const POGEL::POINT& p2 )
{
    this->frompoints(p1, p2);
}*/

POGEL::VECTOR::VECTOR( const std::string& s )
{
    sscanf(s.c_str(), "{[%f],[%f],[%f]}", &x, &y, &z);
}

/*POGEL::VERTEX::VERTEX() : u( 0.0f ), v( 0.0f ), boneID( -1 ), usable( true )
{

}*/

/*POGEL::VERTEX::VERTEX(float a, float b, float c, float s, float t) : POGEL::POINT( a, b, c ), u( s ), v( t ), boneID( -1 ), usable( true )
{

}*/

/*POGEL::VERTEX::VERTEX(float a, float b, float c) : POGEL::POINT(a,b,c), u( 0.0f ), v( 0.0f ), boneID( -1 ), usable( true )
{

}*/

/*POGEL::VERTEX::VERTEX( const POGEL::POINT& p ) : POGEL::POINT( p ), u( 0.0f ), v( 0.0f ), boneID( -1 ), usable( true )
{

}*/

POGEL::VERTEX::VERTEX( const std::string& s )
{
    std::string n = POGEL::getStringComponentLevel('{','}', s, "0 0");
    std::string c = POGEL::getStringComponentLevel('{','}', s, "0 1");
    std::string fmt = "{[%f],[%f],[%f],[%f],[%f],"+n+","+c+"}";
    sscanf(s.c_str(), fmt.c_str(), &x, &y, &z, &u, &v);
    normal = POGEL::VECTOR( n );
    color = POGEL::COLOR( c );
    boneID = boneIDs[ 0 ] = boneIDs[ 1 ] = boneIDs[ 2 ] = -1;
    weights[ 0 ] = weights[ 1 ] = weights[ 2 ] = 0;
    usable = true;
}

/*POGEL::KEY::KEY() : time( 0.0f )
{

}*/

/*POGEL::KEY::KEY(const POGEL::POINT& p, float t ) : POGEL::POINT( p ), time( t )
{

}*/

/*POGEL::TANGENT::TANGENT() : in(), out()
{

}*/

/*POGEL::TANGENT::TANGENT( const POGEL::POINT& i, const POGEL::POINT& o ) : in( i ), out( o )
{

}*/
