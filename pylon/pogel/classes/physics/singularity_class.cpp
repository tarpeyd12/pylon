#include <string.h>

#include "singularity_class.h"

POGEL::PHYSICS::SINGULARITY::SINGULARITY()
{
    center = POGEL::POINT();
    intencity = 0.0f;
    active = true;
    notpointing = true;
}

POGEL::PHYSICS::SINGULARITY::SINGULARITY( const POGEL::POINT& p, float i )
{
    center = p;
    intencity = i;
    active = true;
    notpointing = true;
}

POGEL::PHYSICS::SINGULARITY::SINGULARITY( POGEL::POINT * p, float * i )
{
    pcenter = p;
    pintencity = i;
    active = true;
    notpointing = false;
}

POGEL::PHYSICS::SINGULARITY::SINGULARITY( float x, float y, float z, float i )
{
    center = POGEL::POINT( x, y, z );
    intencity = i;
    active = true;
    notpointing = true;
}

POGEL::PHYSICS::FAN::FAN() : POGEL::PHYSICS::SINGULARITY()
{
    direction = POGEL::VECTOR();
}

POGEL::PHYSICS::FAN::FAN( const POGEL::POINT& p, const POGEL::VECTOR& v, float i ) : POGEL::PHYSICS::SINGULARITY( p, i )
{
    direction = v;
}

POGEL::PHYSICS::FAN::FAN( float x, float y, float z, const POGEL::VECTOR& v, float i ) : POGEL::PHYSICS::SINGULARITY( x, y, z, i )
{
    direction = v;
}

POGEL::PHYSICS::FAN::FAN( const POGEL::POINT& p, float x, float y, float z, float i ) : POGEL::PHYSICS::SINGULARITY( p, i )
{
    direction = POGEL::VECTOR( x, y, z );
}

POGEL::PHYSICS::FAN::FAN( float x, float y, float z, float vx, float vy, float vz, float i ) : POGEL::PHYSICS::SINGULARITY( x, y, z, i )
{
    direction=POGEL::VECTOR( vx, vy, vz );
}

POGEL::PHYSICS::GRAVITYCLUSTER::GRAVITYCLUSTER()
{
    numsingularities = 0;
    singularities = new CLASSLIST<POGEL::PHYSICS::SINGULARITY>();
}

POGEL::PHYSICS::GRAVITYCLUSTER::~GRAVITYCLUSTER()
{
    singularities->clear();
    if( singularities )
    {
        delete singularities;
    }
    singularities = NULL;
    numsingularities = 0;
}

unsigned long
POGEL::PHYSICS::GRAVITYCLUSTER::addsingularity( const POGEL::PHYSICS::SINGULARITY& sig )
{
    singularities->add( sig );
    return numsingularities++;
}

void
POGEL::PHYSICS::GRAVITYCLUSTER::addsingularities( POGEL::PHYSICS::SINGULARITY * sig, unsigned long num )
{
    if( !sig )
    {
        POGEL::fatality( POGEL_FATALITY_NULL_ARRAY_POINTER_RETNUM, "%s to Singularity(s).", POGEL_FATALITY_NULL_ARRAY_POINTER_STRING );
    }
    for( unsigned long i = 0; i < num; ++i )
    {
        addsingularity( sig[ i ] );
    }
}

POGEL::PHYSICS::FLOW::FLOW()
{
    numgusts = 0;
}

POGEL::PHYSICS::FLOW::FLOW( POGEL::POINT * waypoints, unsigned long num, bool forwards )
{
    if( !waypoints )
    {
        POGEL::fatality( POGEL_FATALITY_NULL_ARRAY_POINTER_RETNUM, "%s to Point(s).", POGEL_FATALITY_NULL_ARRAY_POINTER_STRING );
    }
    generatecurve( waypoints, num, forwards );
}

POGEL::PHYSICS::FLOW::~FLOW()
{
    gusts.clear();
}

unsigned long
POGEL::PHYSICS::FLOW::addfan( const POGEL::PHYSICS::FAN& fan )
{
    gusts.add( fan );
    return numgusts++;
}

void
POGEL::PHYSICS::FLOW::addfans( POGEL::PHYSICS::FAN * fan, unsigned long num )
{
    if( !fan )
    {
        POGEL::fatality( POGEL_FATALITY_NULL_ARRAY_POINTER_RETNUM, "%s to Fan(s).", POGEL_FATALITY_NULL_ARRAY_POINTER_STRING );
    }
    for( unsigned long i = 0; i < num; ++i )
    {
        addfan( fan[ i ] );
    }
}

void
POGEL::PHYSICS::FLOW::generatecurve( POGEL::POINT * waypoints, unsigned long num, bool forwards )
{
    if( !waypoints )
    {
        POGEL::fatality( POGEL_FATALITY_NULL_ARRAY_POINTER_RETNUM, "%s to Point(s).", POGEL_FATALITY_NULL_ARRAY_POINTER_STRING );
    }
    for( unsigned long i = 0; i < num; ++i )
    {
        unsigned int index1 = ( i + ( forwards ? 0 : 1 ) ) % num;
        unsigned int index2 = ( i + ( forwards ? 1 : 0 ) ) % num;
        POGEL::VECTOR v( waypoints[ index1 ], waypoints[ index2 ] );
        v.normalize();
        addfan( POGEL::PHYSICS::FAN( waypoints[ i ], v, waypoints[ index1 ].distance( waypoints[ index2 ] ) ) );
    }
}
