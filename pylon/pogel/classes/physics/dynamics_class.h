#ifndef _DYNAMICS_CLASS_H
#define _DYNAMICS_CLASS_H

namespace POGEL {
namespace PHYSICS {
class DYNAMICS;
}
}

//#include "../../templates/templates.h"
#include "../../templates/octree_template.h"
#include "solid_class.h"
#include "../../templates/classlist_template.h"
#include "../../templates/bitlist.h"
#include "physics.h"
#include "singularity_class.h"

#define             DYNAMICS_HAS_MAGNETIC_OBJECT            1
#define             DYNAMICS_LIGHTWEIGHT_ONLY               2
#define             DYNAMICS_DRAW_BY_INDEX                  4

class POGEL::PHYSICS::DYNAMICS
{
    private:
        unsigned int properties; // the mushed properties
    protected:
        CLASSLIST<POGEL::PHYSICS::SOLID*> objects;
        unsigned long numobjects;

        POGEL::PHYSICS::GRAVITYCLUSTER objectmasses;

        POGEL::PHYSICS::GRAVITYCLUSTER singularities;
        POGEL::PHYSICS::FLOW gusts;

        POGEL::OCTREE<POGEL::PHYSICS::SOLID> *ot;
        CLASSLIST<POGEL::PHYSICS::SOLID*> *oltmp;

        CLASSLIST<unsigned int> *objIndicies;

        virtual void buildot();
        void destroyot();

    public:
        unsigned long boundingskips;

        POGEL::VECTOR gravity;
        float air_dencity;

        DYNAMICS();
        ~DYNAMICS();

        POGEL::OCTREE<POGEL::PHYSICS::SOLID>* getotree();

        PROPERTIES_METHODS;

        void FORCEfastAccessList();

        unsigned long numobjs();
        POGEL::PHYSICS::SOLID* objs(unsigned long a);
        CLASSLIST<POGEL::PHYSICS::SOLID*> objslst();

        unsigned long addsingularity(POGEL::PHYSICS::SINGULARITY sig);
        void addsingularities(POGEL::PHYSICS::SINGULARITY* sig, unsigned long num);

        unsigned long addfan(POGEL::PHYSICS::FAN fan);
        void addfans(POGEL::PHYSICS::FAN* fan, unsigned long num);

        POGEL::PHYSICS::SOLID* getSolid(char*);
        POGEL::PHYSICS::SOLID* getSolid(std::string);

        unsigned long addSolid(POGEL::PHYSICS::SOLID*);
        unsigned long addSolidHoldGravity(POGEL::PHYSICS::SOLID*);
        void addSolids(POGEL::PHYSICS::SOLID**,unsigned long);

        void addSolidsGravity(POGEL::PHYSICS::SOLID*);

        void removeSolid(POGEL::PHYSICS::SOLID*);
        void removeSolidKeepGravity(POGEL::PHYSICS::SOLID*);
        void removeSolid(char* n);

        void clearAllSolids();

        virtual POGEL::VECTOR getpull(POGEL::PHYSICS::SOLID*);

        virtual void increment();

        virtual void draw();

        void drawGravityGrid(float, float, POGEL::POINT, unsigned int);

        friend class POGEL::PHYSICS::SIMULATION;
};

#endif /* _SIMULATION_CLASS_H */
