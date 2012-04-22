#include <string.h>

#include "dynamics_class.h"

void POGEL::PHYSICS::DYNAMICS::buildot()
{
    oltmp = new CLASSLIST<POGEL::PHYSICS::SOLID*>();
    //while(oltmp->length() < objects.length())
        //oltmp->add(objects[oltmp->length()]);
    //oltmp->add(objects[oltmp->length()]);
    oltmp->add(objects);
    ot = new POGEL::OCTREE<POGEL::PHYSICS::SOLID>(oltmp, 1, true);
    ot->grow();
    #ifdef OPENGL
        if(POGEL::hasproperty(POGEL_BOUNDING) && POGEL::hasproperty(POGEL_ANCESTORY))
        {
            glLineWidth(2);
            ot->draw();
            glLineWidth(1);
        }
    #endif
}

void POGEL::PHYSICS::DYNAMICS::destroyot()
{
    if(ot != NULL)
    {
        delete ot;
        ot = NULL;
    }
    if(oltmp != NULL)
    {
        delete oltmp;
        oltmp = NULL;
    }
}

POGEL::PHYSICS::DYNAMICS::DYNAMICS()
{
    properties = 0;
    numobjects = 0;
    boundingskips = 5;
    oltmp = NULL;
    ot = NULL;
    objIndicies = NULL;
}

POGEL::PHYSICS::DYNAMICS::~DYNAMICS()
{
    //clearAllSolids();
    destroyot();
}

POGEL::OCTREE<POGEL::PHYSICS::SOLID>* POGEL::PHYSICS::DYNAMICS::getotree()
{
    return ot;
}

void POGEL::PHYSICS::DYNAMICS::FORCEfastAccessList()
{
    /*HASHLIST<POGEL::PHYSICS::SOLID*> l;
    while(objects.length())
    {
        l.add(objects[objects.length()-1]);
        objects.remove(objects.length()-1);
    }
    objects.FORCEresizeInternalList(1);
    while(l.length())
    {
        objects.add(l[l.length()-1]);
        l.remove(l.length()-1);
    }*/
}

unsigned long POGEL::PHYSICS::DYNAMICS::numobjs()
{
    return objects.length();
}

POGEL::PHYSICS::SOLID* POGEL::PHYSICS::DYNAMICS::objs(unsigned long a)
{
    return objects[a];
}

CLASSLIST<POGEL::PHYSICS::SOLID*> POGEL::PHYSICS::DYNAMICS::objslst()
{
    return objects;
}

unsigned long POGEL::PHYSICS::DYNAMICS::addsingularity(POGEL::PHYSICS::SINGULARITY sig)
{
    return singularities.addsingularity(sig);
}

void POGEL::PHYSICS::DYNAMICS::addsingularities(POGEL::PHYSICS::SINGULARITY* sig, unsigned long num)
{
    singularities.addsingularities(sig,num);
}

unsigned long POGEL::PHYSICS::DYNAMICS::addfan(POGEL::PHYSICS::FAN fan)
{
    return gusts.addfan(fan);
}

void POGEL::PHYSICS::DYNAMICS::addfans(POGEL::PHYSICS::FAN* fan, unsigned long num)
{
    gusts.addfans(fan,num);
}

POGEL::PHYSICS::SOLID* POGEL::PHYSICS::DYNAMICS::getSolid(char* n)
{
    for(unsigned int i = 0; i < objects.length(); i++)
    {
        if( strlen(n) == strlen(objects[i]->getname()) && !strncmp(objects[i]->getname(), n, strlen(n)) )
        {
            return objects[i];
        }
    }
    return NULL;
}

POGEL::PHYSICS::SOLID* POGEL::PHYSICS::DYNAMICS::getSolid(std::string n)
{
    for(unsigned int i = 0; i < objects.length(); i++)
    {
        if( objects[i]->getsname().compare(n) == 0 )
        {
            return objects[i];
        }
    }
    return NULL;
}

unsigned long POGEL::PHYSICS::DYNAMICS::addSolid(POGEL::PHYSICS::SOLID* obj)
{
    if(obj->behavior.magnetic)
    {
        addproperty(DYNAMICS_HAS_MAGNETIC_OBJECT);
    }
    objectmasses.addsingularity(POGEL::PHYSICS::SINGULARITY(&obj->position, &obj->behavior.mass));
    obj->container = this;
    obj->makebounding();
    objects.add(obj);
    return numobjects++;
}

unsigned long POGEL::PHYSICS::DYNAMICS::addSolidHoldGravity(POGEL::PHYSICS::SOLID* obj)
{
    if(obj->behavior.magnetic)
    {
        addproperty(DYNAMICS_HAS_MAGNETIC_OBJECT);
    }
    obj->container = this;
    obj->makebounding();
    objects.add(obj);
    return numobjects++;
}

void POGEL::PHYSICS::DYNAMICS::addSolidsGravity(POGEL::PHYSICS::SOLID* obj)
{
    objectmasses.addsingularity(POGEL::PHYSICS::SINGULARITY(&obj->position, &obj->behavior.mass));
}

void POGEL::PHYSICS::DYNAMICS::addSolids(POGEL::PHYSICS::SOLID **obj, unsigned long num)
{
    if(obj == (POGEL::PHYSICS::SOLID**)NULL)
    {
        POGEL::fatality(POGEL_FATALITY_NULL_ARRAY_POINTER_RETNUM,"%s to Solid Object(s).",POGEL_FATALITY_NULL_ARRAY_POINTER_STRING);
    }
    for(unsigned long i=0;i<num;i++)
    {
        if(obj[i] == (POGEL::PHYSICS::SOLID*)NULL)
        {
            POGEL::fatality(POGEL_FATALITY_NULL_OBJECT_POINTER_RETNUM|POGEL_FATALITY_NULL_LIST_POINTER_RETNUM,"%s & %s to Solid Object.",POGEL_FATALITY_NULL_OBJECT_POINTER_STRING, POGEL_FATALITY_NULL_LIST_POINTER_STRING);
        }
        else
        {
            addSolid(obj[i]);
        }
    }
}

void POGEL::PHYSICS::DYNAMICS::removeSolid(POGEL::PHYSICS::SOLID* obj)
{
    if(obj == NULL)
    {
        return;
    }
    for(unsigned int i = 0; i < objects.length(); i++)
    {
        if(obj == objects[i])
        {
            objects[i]->container = NULL;
            objects.remove(i);
            objectmasses.remove(i);
            --numobjects;
            return;
        }
    }
}

void POGEL::PHYSICS::DYNAMICS::removeSolidKeepGravity(POGEL::PHYSICS::SOLID* obj)
{
    if(obj == NULL)
    {
        return;
    }
    for(unsigned int i = 0; i < objects.length(); i++)
    {
        if(obj == objects[i])
        {
            objects[i]->container = NULL;
            objects.remove(i);
            --numobjects;
            return;
        }
    }
}

void POGEL::PHYSICS::DYNAMICS::removeSolid(char* n)
{
    //removeSolid(getSolid(n));

    if( n == NULL || strlen(n) == 0 )
    {
        return;
    }
    for(unsigned int i = 0; i < objects.length(); i++)
    {
        if( strlen(n) == strlen(objects[i]->getname()) && !strncmp(objects[i]->getname(), n, strlen(n)) )
        {
            objects[i]->container = NULL;
            objects.remove(i);
            objectmasses.remove(i);
            numobjects--;
            return;
        }
    }
}

void POGEL::PHYSICS::DYNAMICS::clearAllSolids()
{
    for(unsigned int i = 0; i < objects.length(); ++i)
    {
        delete objects[i];
    }
    numobjects = 0;
    objects.clear();
    objectmasses.clearAll();
}

POGEL::VECTOR POGEL::PHYSICS::DYNAMICS::getpull(POGEL::PHYSICS::SOLID* obj)
{
    POGEL::VECTOR pull;

    // TODO: get the real magnetic physics ...
    if( hasproperty(DYNAMICS_HAS_MAGNETIC_OBJECT) )
    {
        for( unsigned long a = 0; a < numobjects; a++ )
        {
            // the magnetic charge attraction
            if( obj != objects[a] && obj->behavior.magnetic && objects[a]->behavior.magnetic )
            {
                //pull += POGEL::VECTOR(obj->position,objects[a]->position).normal()*(-obj->behavior.charge-objects[a]->behavior.charge);

                if( (obj->behavior.charge < 0.0f && objects[a]->behavior.charge > 0.0f) || (obj->behavior.charge > 0.0f && objects[a]->behavior.charge < 0.0f) )
                {
                    pull += (POGEL::VECTOR(obj->position, objects[a]->position).normal()*(fabs(obj->behavior.charge) + fabs(objects[a]->behavior.charge)))/(objects[a]->position.distance(obj->position));
                }
                else if( (obj->behavior.charge < 0.0f && objects[a]->behavior.charge < 0.0f) || (obj->behavior.charge > 0.0f && objects[a]->behavior.charge > 0.0f) )
                {
                    pull += (POGEL::VECTOR(objects[a]->position, obj->position).normal()*(fabs(obj->behavior.charge) + fabs(objects[a]->behavior.charge)))/(objects[a]->position.distance(obj->position));
                }
                else
                {

                }
            }
        }
    }

    pull += gusts.getpull(obj->position, obj->behavior.mass);
    pull += singularities.getpull(obj->position, obj->behavior.mass);
    pull += gravity * obj->behavior.mass;
    if ( !hasproperty(DYNAMICS_LIGHTWEIGHT_ONLY) )
    {
        pull += objectmasses.getpull(obj->position, obj->behavior.mass);
        //pull += ot->getpull(obj->position, obj->behavior.mass);
    }
    return pull;//*PARTICLE_SLOWDOWN;
}

void POGEL::PHYSICS::DYNAMICS::increment()
{
    /*destroyot();
    buildot();*/

    for( unsigned long a = 0; a < numobjects; a++ )
    {
        if( objects[a]->hasOption(PHYSICS_SOLID_VOLITAL) && !objects[a]->hasOption(PHYSICS_SOLID_STATIONARY) )
        {
            objects[a]->direction += getpull(objects[a]);
            float airslowdown = ( ( objects[a]->behavior.air_friction * air_dencity ) / PARTICLE_SLOWDOWN ) + 1.0f;
            objects[a]->spin /= airslowdown;
            objects[a]->direction /= airslowdown;
        }
        objects[a]->step();
    }
}

void POGEL::PHYSICS::DYNAMICS::draw()
{
    if( !hasproperty(DYNAMICS_DRAW_BY_INDEX) )
    {
        for( unsigned long i = 0; i < numobjects; i++ )
        {
            objects[i]->draw();
        }
    }
    else if( objIndicies != NULL )
    {
        // note: objIndicies->length(), may change its value mid loop.
        for( unsigned long i = 0; i < objIndicies->length(); i++ )
        {
            unsigned int c = objIndicies->get(i);
            if( c < numobjects )
            {
                POGEL::PHYSICS::SOLID* obj = objects[c];
                if( obj != NULL )
                {
                    obj->draw();
                }
            }
        }
    }
}

void POGEL::PHYSICS::DYNAMICS::drawGravityGrid(float mass, float sps, POGEL::POINT center, unsigned int grd)
{
    unsigned long numpoints = grd*grd*grd;
    POGEL::POINT prev_pv, prev_pv_a[grd], prev_pv_b[grd*grd];
    float pntms = mass*PARTICLE_SLOWDOWN_RATIO;
    for(unsigned long i = 0; i < numpoints; i++)
    {
        unsigned int imgrd = i%grd;
        POGEL::POINT p(
            (((float)(imgrd)*sps) - ((float(grd)*sps)/2.0f - sps/2.0f) +center.x),
            (((float)((i/grd)%grd)*sps) - ((float(grd)*sps)/2.0f - sps/2.0f) +center.y),
            ((float)(i/(grd*grd))*(sps) - sps*float(grd)/2.0f + sps/2.0f +center.z)
        );
        POGEL::VECTOR v = objectmasses.getpull(p, pntms)/(1);
        if(v.getdistance() > sps*2)
        {
            v = v.normal()*sps*2;
        }
        POGEL::COLOR c(1,.25,0,v.getdistance()/(sps*4));
        POGEL::POINT pv = p+v;
        if(c.a > 0.05 && c.a < sps*4)
        {
            pv.draw(4, c);
            if(imgrd)
                POGEL::LINE(prev_pv, pv, 2, c).draw();
            if((i/grd)%grd)
                POGEL::LINE(prev_pv_a[imgrd], pv, 2, c).draw();
            if(i/(grd*grd))
                POGEL::LINE(prev_pv_b[i%(grd*grd)], pv, 2, c).draw();
        }
        prev_pv_b[i%(grd*grd)] = prev_pv_a[imgrd] = prev_pv = pv;
    }
}



