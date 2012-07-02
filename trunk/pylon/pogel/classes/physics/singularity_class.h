#ifndef _SINGULARITY_CLASS_H
#define _SINGULARITY_CLASS_H

#include <stdlib.h>

namespace POGEL
{
    namespace PHYSICS
    {
        class SINGULARITY;
        class FAN;
        class FLOW;
        class GRAVITYCLUSTER;
    }
}

#include "../../templates/classlist_template.h"
#include "physics.h"
#include "../point_class.h"

//#define         GRAVITYCONSTANT         ((float)pow(10.0f, -11.0f)*6.673f)
#define         GRAVITYCONSTANT         0.00000000006673

class POGEL::PHYSICS::SINGULARITY
{
    protected:
        bool notpointing;
    public:
        bool active;

        POGEL::POINT *pcenter;
        POGEL::POINT center;

        float *pintencity;
        float intencity;

        SINGULARITY();
        SINGULARITY( const POGEL::POINT& p, float i );
        SINGULARITY( POGEL::POINT * p, float * i );
        SINGULARITY( float x, float y, float z, float i );

        inline
        POGEL::POINT
        getCenter() const
        {
            if( notpointing )
            {
                return center;
            }
            return *pcenter;
        }

        inline
        float
        getIntencity() const
        {
            if( notpointing )
            {
                return intencity;
            }
            return *pintencity;
        }

        inline
        POGEL::POINT
        getposition() const
        {
            return getCenter();
        }

        inline
        POGEL::BOUNDING
        getbounding() const
        {
            POGEL::POINT c = getCenter();
            return POGEL::BOUNDING( 0, c.x,c.x, c.y,c.y, c.z,c.z );
        }

        virtual
        inline
        POGEL::VECTOR
        getpull( const POGEL::POINT& p, float mass ) const
        {
            if( !active )
            {
                return POGEL::VECTOR();
            }
            POGEL::POINT center = getCenter();
            if( p == center )
            {
                return POGEL::VECTOR();
            }
            float dist = p.distance( center );
            if( isnan( dist ) || !isfinite( dist ) )
            {
                return POGEL::VECTOR();
            }
            //if( dist*dist > 0.00001 && 1/(dist*dist) > 0.00001 )
            {
                POGEL::VECTOR v( p, center );
                v.normalize();
                v *= getIntencity() * mass * GRAVITYCONSTANT;
                v /= dist * dist;
                if( mass < 0.0 )
                {
                    v *= -1.0;
                }
                return v;
            }
            return POGEL::VECTOR();
        }
};

class POGEL::PHYSICS::FAN : public POGEL::PHYSICS::SINGULARITY
{
    public:
        POGEL::VECTOR direction;
        POGEL::VECTOR *pdirection;

        FAN();
        FAN( const POGEL::POINT& p, const POGEL::VECTOR& v, float i );
        FAN( float x, float y, float z, const POGEL::VECTOR& v, float i );
        FAN( const POGEL::POINT& p, float x, float y, float z, float i );
        FAN( float x, float y, float z, float vx, float vy, float vz, float i );

        inline
        POGEL::VECTOR
        getDirection() const
        {
            if( notpointing )
            {
                return direction;
            }
            return *pdirection;
        }

        inline
        POGEL::VECTOR
        getpull( const POGEL::POINT& p, float mass ) const
        {
            if( active )
            {
                return ( ( getDirection() * getIntencity() ) / p.distance( getCenter() ) ) / ( mass + 1.0f );
            }
            return POGEL::VECTOR();
        }
};

class POGEL::PHYSICS::GRAVITYCLUSTER
{
    private:
        CLASSLIST< POGEL::PHYSICS::SINGULARITY > * singularities;
        unsigned long numsingularities;
    public:

        GRAVITYCLUSTER();
        ~GRAVITYCLUSTER();

        unsigned long addsingularity( const POGEL::PHYSICS::SINGULARITY& );
        void addsingularities( POGEL::PHYSICS::SINGULARITY*, unsigned long );

        inline
        void
        remove( unsigned long i )
        {
            singularities->remove( i );
            --numsingularities;
        }

        inline
        void
        clearAll()
        {
            numsingularities = 0;
            singularities->clear();
            if( singularities )
            {
                delete singularities;
            }
            singularities = new CLASSLIST<POGEL::PHYSICS::SINGULARITY>();
        }

        inline
        POGEL::VECTOR
        getpull( const POGEL::POINT& p, float mass ) const
        {
            if( !numsingularities )
            {
                return POGEL::VECTOR();
            }
            POGEL::VECTOR v = singularities->get( 0 ).getpull( p, mass );
            for( unsigned int i = 1; i < numsingularities; ++i )
            {
                v += singularities->get( i ).getpull( p, mass );
            }
            return v;
        }

        /*inline
        POGEL::VECTOR
        fgetpull(POGEL::POINT p, float mass, HASHLIST<POGEL::OCTREE<POGEL::PHYSICS::SOLID>*> *otlst) {

            if(numsingularities==0) return POGEL::VECTOR();
            POGEL::VECTOR v;
            for(unsigned int i=0;i<numsingularities;++i) v+=singularities[i].getpull(p, mass);
            return v;
        }*/

        inline
        POGEL::PHYSICS::GRAVITYCLUSTER&
        operator = ( const POGEL::PHYSICS::GRAVITYCLUSTER& g )
        {
            if( singularities )
            {
                singularities->clear();
                delete singularities;
            }
            singularities = g.singularities;
            numsingularities = g.numsingularities;
            return *this;
        }
};

class POGEL::PHYSICS::FLOW
{
    private:
        CLASSLIST<POGEL::PHYSICS::FAN> gusts;
        unsigned long numgusts;
    public:

        FLOW();
        FLOW( POGEL::POINT * waypoints, unsigned long num, bool forwards );
        ~FLOW();

        unsigned long addfan( const POGEL::PHYSICS::FAN& );
        void addfans( POGEL::PHYSICS::FAN *, unsigned long );
        void generatecurve( POGEL::POINT *, unsigned long, bool );

        inline
        void
        remove( unsigned long i )
        {
            gusts.remove( i );
            --numgusts;
        }

        inline
        POGEL::VECTOR
        getpull( const POGEL::POINT& p, float mass ) const
        {
            if( !numgusts )
            {
                return POGEL::VECTOR();
            }
            POGEL::VECTOR v;
            unsigned int diff = 0;
            for( unsigned int i = 0; i < numgusts; ++i )
            {
                if( gusts[ i ].active )
                {
                    v += gusts[ i ].getpull( p, mass );
                }
                else
                {
                    ++diff;
                }
            }
            if( diff < numgusts )
            {
                return v / ( (float)numgusts - (float)diff );
            }
            return POGEL::VECTOR();
        }
};

#endif /* _SINGULARITY_CLASS_H */

