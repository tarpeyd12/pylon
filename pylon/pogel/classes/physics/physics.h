#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "../triangle_class.h"
#include "../line_class.h"
#include "../../pogel_internals.h"

#define PHYSICS_NUMTRI_PROCESSED 1000

//#define PHYSICS_COLLISION_LOGSTATS

#define			PHYSICS_LINESOLID_COLLISION_FIRST			0
#define			PHYSICS_LINESOLID_COLLISION_LEAST			1
#define			PHYSICS_LINESOLID_COLLISION_GREATEST		2


namespace POGEL
{
    namespace PHYSICS
    {

        class BOUNDINGCONTAINER;

        class SINGULARITY;
        class FAN;

        class GRAVITYCLUSTER;
        class FLOW;

        class DYNAMICS;
        class SIMULATION;

        class SOLID;
        class SOLIDPHYSICALPROPERTIES;

        class FOUNTAIN;
        class MICROCOSM;

        bool line_triangle_collision( const POGEL::POINT&, const POGEL::POINT&, const POGEL::TRIANGLE&, POGEL::POINT*, POGEL::POINT* );
        bool ray_triangle_collision( const POGEL::POINT&, const POGEL::VECTOR&, const POGEL::TRIANGLE&, POGEL::POINT*, POGEL::POINT* );
        bool triangle_collision( const POGEL::TRIANGLE&, const POGEL::TRIANGLE&, POGEL::POINT*, POGEL::POINT* );
        bool solid_line_collision( int, POGEL::PHYSICS::SOLID*, const POGEL::POINT&, const POGEL::POINT&, POGEL::TRIANGLE*, POGEL::POINT*, POGEL::POINT* );
        bool solid_line_collision( POGEL::PHYSICS::SOLID*, const POGEL::POINT&, const POGEL::POINT&, POGEL::TRIANGLE*, POGEL::POINT*, POGEL::POINT* );
        bool solid_ray_collision( int, POGEL::PHYSICS::SOLID*, const POGEL::POINT&, const POGEL::VECTOR&, POGEL::TRIANGLE*, POGEL::POINT*, POGEL::POINT* );
        bool solid_collision( POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*, POGEL::POINT*, POGEL::VECTOR*, POGEL::VECTOR*, float* );

        float line_point_distance_BRUTE( const POGEL::POINT&, const POGEL::LINE&, POGEL::POINT* );
        float line_point_distance( const POGEL::POINT&, const POGEL::LINE&, POGEL::POINT* );

        float point_triangle_distance_BRUTE( const POGEL::POINT&, const POGEL::TRIANGLE&, POGEL::POINT* );
        float point_triangle_distance( const POGEL::POINT&, const POGEL::TRIANGLE&, POGEL::POINT* );

        inline float getvprime( float m1, float m2, float v1, float v2 );
        void calcElasticDirections( const POGEL::VECTOR&, POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*, POGEL::VECTOR* );

        inline float getvf( float m1, float m2, float v1, float v2, float cr );
        void calcInelasticDirections( const POGEL::VECTOR&, POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*, POGEL::VECTOR* );
    }
}

#endif /* _PHYSICS_H */
