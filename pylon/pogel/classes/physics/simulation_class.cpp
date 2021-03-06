#include <string.h>

#include "simulation_class.h"
#include "../threads.h"

/* Just remember, in here, there is usualy no method to the madenss. */

void
POGEL::PHYSICS::SIMULATION::buildot()
{
    oltmp = new CLASSLIST< POGEL::PHYSICS::SOLID * >();
    //while(oltmp->length() < objects.length())
        //oltmp->add(objects[oltmp->length()]);
    //oltmp->add(objects[oltmp->length()]);
    oltmp->add( objects );
    ot = new POGEL::OCTREE< POGEL::PHYSICS::SOLID >( oltmp, 1, true );
    ot->grow();
    /*#ifdef THREADSOK
        if (threads > 1 )
        {
            ot->FORCEfastlist();
        }
    #endif*/
    #ifdef OPENGL
        if( POGEL::hasproperty(POGEL_BOUNDING) && POGEL::hasproperty(POGEL_ANCESTORY) )
        {
            glLineWidth( 2 );
            ot->draw();
            glLineWidth( 1 );
        }
    #endif
}

POGEL::PHYSICS::SIMULATION::SIMULATION() : POGEL::PHYSICS::DYNAMICS()
{
    precision=0.01f;
    deactivation = false;
    inactive_index = 25;
    stepstaken = 0;
    collitters = 2;
    #ifdef THREADSOK
    if( THREADSOK )
    {
        threads = THREADSOK;
    }
    else
    {
        threads = 1;
    }
    #endif
}

void
POGEL::PHYSICS::SIMULATION::addpulls( unsigned long s, unsigned long e )
{
    float r = ( POGEL::hasproperty(POGEL_TIMEBASIS) ? POGEL::GetSecondsPerFrame() : 1.0f );
    unsigned int numObjects = numobjs();
    for( unsigned long a = s; a < e && a < numObjects; ++a )
    {
        POGEL::PHYSICS::SOLID * object = objects[ a ];
        if( object->hasOption(PHYSICS_SOLID_VOLITAL) && !object->hasOption(PHYSICS_SOLID_STATIONARY) )
        {
            if(
                (
                    deactivation
                    &&
                    (
                        (
                            (object->direction+object->force).getdistance() <= precision*r
                            &&
                            object->sameposlegacy(precision*r, inactive_index)
                        )
                        &&
                        object->stepstaken > object->trailsize
                        &&
                        stepstaken > 100
                        &&
                        object->stepstaken > inactive_index
                    )
                    //||
                    //object->napping()
                )
            )
            {
                object->direction = POGEL::VECTOR();
                if( !object->napping() )
                {
                    object->forcegetbounding();
                    object->sleep();
                }
            }
            else if( !deactivation )
            {
                object->direction += getpull( object );
                if( object->napping() )
                {
                    object->wake();
                }
            }
            else if( object->napping() )
            {

            }
            else
            {
                object->direction += getpull( object );
                if( object->napping() )
                {
                    object->wake();
                }
            }

            // TODO: get the air friction to work with timing
            float airslowdown = ( ( object->behavior.air_friction * air_dencity ) / PARTICLE_SLOWDOWN ) + 1.0f;
            object->spin /= airslowdown;
            object->direction /= airslowdown;
        }
        //object->increment();
        //object->step();
        object->clearForce();
    }
}

#ifdef THREADSOK
class thdat
{
    public:
        POGEL::PHYSICS::SIMULATION* sim;
        unsigned int first, last;
        thdat( POGEL::PHYSICS::SIMULATION * s, unsigned int f, unsigned int l )
        {
            sim = s;
            first = f;
            last = l;
        }

        ~thdat()
        {
            sim = NULL;
        }
};

THREADTYPE
pullrun( THREADARGS data )
{
    thdat *dat = (thdat*)data;
    dat->sim->addpulls( dat->first, dat->last );
    //delete dat;
    return NULL;
}
#endif

void
POGEL::PHYSICS::SIMULATION::addpulls()
{
    #ifdef THREADSOK
    if( threads > 1 )
    {
        if( threads > numobjs() )
        {
            threads = numobjs();
        }
        POGEL::THREAD * tharr = new POGEL::THREAD[ threads ];
        float objsPerThread = float( numobjs() ) / float( threads );
        unsigned int numObjsChecked = 0;
        for( unsigned int i = 0; i < threads; ++i )
        {
            tharr[ i ].setThread( pullrun );
            unsigned int first = (unsigned int)( float( i ) * objsPerThread );
            unsigned int last = (unsigned int)( float( i + 1 ) * objsPerThread );
            numObjsChecked += last - first;
            tharr[ i ].setData( new thdat( this, first, last ) );
            tharr[ i ].startThread();
        }
        if( numObjsChecked < numobjs() )
        {
            addpulls( numObjsChecked, numobjs() );
        }
        for( unsigned int i = 0; i < threads; ++i )
        {
            tharr[ i ].joinThread();
            void * data = tharr[ i ].getData();
            if( data )
            {
                delete (thdat*)data;
            }
            tharr[ i ].setData( NULL );
        }
        delete [] tharr;
    }
    else
    #endif
    {
        addpulls( 0, numobjects );
    }
}

inline
bool
objectIntersectionProcessing( POGEL::PHYSICS::SIMULATION * sim, unsigned long a, unsigned long b )
{
    POGEL::PHYSICS::SOLID * obja = sim->objs( a );
    POGEL::PHYSICS::SOLID * objb = sim->objs( b );
    if( a != b && boundingcheck( obja, objb ) )
    {
        bool ret = false;
        if( sim->processcollision( obja, objb ) )
        {
            if( obja->callback != NULL )
            {
                char* n = new char[strlen(objb->getname())+1];
                memset(n, '\0', strlen(objb->getname())+1);
                strcpy(n, objb->getname());
                (*obja->callback)(obja, n);
                delete [] n;
            }
            if( objb->callback != NULL )
            {
                char* n = new char[strlen(obja->getname())+1];
                memset(n, '\0', strlen(obja->getname())+1);
                strcpy(n, obja->getname());
                (*objb->callback)(objb, n);
                delete [] n;
            }
            if( obja->napping() )
            {
                obja->wake();
            }
            if( objb->napping() )
            {
                objb->wake();
            }

            ret = true;
        }

        if( POGEL::hasproperty( POGEL_PAIRS ) && b > a )
        {
            if(obja->hasOption(PHYSICS_SOLID_CONCAVE) && obja->hasOption(PHYSICS_SOLID_SPHERE))
            {
                POGEL::VECTOR vr(obja->position, objb->position);
                vr.normalize();
                vr *= obja->bounding.maxdistance;
                vr += obja->position;
                POGEL::LINE(vr.topoint(),objb->position,1,POGEL::COLOR(1,.75,.75,1)).draw();
            }
            else if(objb->hasOption(PHYSICS_SOLID_CONCAVE) && objb->hasOption(PHYSICS_SOLID_SPHERE))
            {
                POGEL::VECTOR vr(objb->position, obja->position);
                vr.normalize();
                vr *= objb->bounding.maxdistance;
                vr += objb->position;
                POGEL::LINE(obja->position,vr.topoint(),1,POGEL::COLOR(1,.75,.75,1)).draw();
            }
            else if( obja->hasOption( PHYSICS_SOLID_CONCAVE ) )
            {

            }
            else if( objb->hasOption( PHYSICS_SOLID_CONCAVE ) )
            {

            }
            else
            {
                POGEL::LINE(obja->position,objb->position,1,POGEL::COLOR(1,.75,.75,1)).draw();
            }
        }

        return ret;
    }
    return false;
}

inline
void
checkcollision( POGEL::PHYSICS::SIMULATION* sim, unsigned long s, unsigned long e, unsigned long o, unsigned long recnum )
{
    if( recnum >= sim->getCollItters() )
    {
        return;
    }

    //unsigned long sim_numobjs = sim->numobjs();

    for( unsigned long a = s; a < e && a < sim->numobjs(); ++a )
    {
        POGEL::PHYSICS::SOLID * obj_a = sim->objs( a );
        if( !obj_a->napping() || obj_a->hasOption( PHYSICS_SOLID_STATIONARY ) )
        {
            CLASSLIST<unsigned int> *objs = sim->getotree()->releventIndicies(obj_a->bounding);
            if( obj_a->hasOption( PHYSICS_SOLID_CONCAVE ) )
            {
                for( unsigned long b = 0; b < sim->numobjs(); ++b )
                {
                    if( o != a && o != b && objectIntersectionProcessing( sim, a, b ) && !sim->objs( b )->hasOption(PHYSICS_SOLID_STATIONARY))
                    {
                        obj_a->makebounding();
                        checkcollision( sim, b, b + 1, a, recnum + 1 );
                    }
                }
            }
            else if( objs )
            {
                //unsigned int objs_length = objs->length();
                for( unsigned long b = 0; b < objs->length(); ++b )
                {
                    unsigned int obj_b = objs->get( b );
                    if( o != a && o != obj_b && obj_b < sim->numobjs() && objectIntersectionProcessing( sim, a, obj_b ) && !sim->objs( obj_b )->hasOption( PHYSICS_SOLID_STATIONARY ) )
                    {
                        sim->objs( obj_b )->makebounding();
                        checkcollision( sim, obj_b, obj_b + 1, a, recnum + 1 );
                    }
                }
            }
            if( objs )
            {
                delete objs;
            }
            objs = NULL;
        }
    }
}

inline
void
checkcollision( POGEL::PHYSICS::SIMULATION * sim )
{
    checkcollision( sim, 0, sim->numobjs(), sim->numobjs(), 0 );
}

#ifdef THREADSOK
THREADTYPE
collrun( THREADARGS data )
{
    thdat *dat = (thdat*)data;
    checkcollision( dat->sim, dat->first, dat->last, dat->sim->numobjs(), 0 );
    //delete dat;
    return NULL;
}
#endif

void
POGEL::PHYSICS::SIMULATION::checkcollisions()
{
    #ifdef THREADSOK
    if( threads > 1 )
    {
        if( threads > numobjs() )
        {
            threads = numobjs();
        }
        POGEL::THREAD * tharr = new POGEL::THREAD[ threads ];
        float objsPerThread = float( numobjs() ) / float( threads );
        unsigned int numObjsChecked = 0;
        for( unsigned int i = 0; i < threads; ++i )
        {
            tharr[ i ].setThread( collrun );
            unsigned int first = (unsigned int)( float( i ) * objsPerThread );
            unsigned int last = (unsigned int)( float( i + 1 ) * objsPerThread );
            numObjsChecked += last - first;
            tharr[ i ].setData( new thdat( this, first, last ) );
            tharr[ i ].startThread();
        }
        if( numObjsChecked < numobjs() )
        {
            checkcollision( this, numObjsChecked, numobjs(), numobjs(), 0 );
        }
        for( unsigned int i = 0; i < threads; ++i )
        {
            tharr[ i ].joinThread();
            void * data = tharr[ i ].getData();
            if( data )
            {
                delete (thdat*)data;
            }
            tharr[ i ].setData( NULL );
        }
        delete [] tharr;
    }
    else
    #endif
    {
        checkcollision( this );
    }
}

void
POGEL::PHYSICS::SIMULATION::stepobjs()
{
    unsigned long l = objects.length();
    for( unsigned long a = 0; a < l; ++a )
    {
        if( !objects[ a ]->napping() )
        {
            objects[ a ]->step();
        }
        else
        if( objects[ a ]->function )
        {
            (*objects[ a ]->function)( objects[ a ] );
        }
        if( objects.length() < l )
        {
            --l;
            --a;
        }
    }
}

void
POGEL::PHYSICS::SIMULATION::collincrement()
{
    checkcollisions();
}

void
POGEL::PHYSICS::SIMULATION::increment()
{
    destroyot();
    buildot();

    addpulls();
    collincrement();
    stepobjs();
    ++stepstaken;
}

