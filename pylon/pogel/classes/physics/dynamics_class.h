#ifndef _DYNAMICS_CLASS_H
#define _DYNAMICS_CLASS_H

namespace POGEL {
namespace PHYSICS {
class DYNAMICS;
}
}

#include "../../templates/templates.h"
#include "physics.h"
#include "singularity_class.h"
#include "solid_class.h"

#define				DYNAMICS_HAS_MAGNETIC_OBJECT			1
#define             DYNAMICS_LIGHTWEIGHT_ONLY               2

class POGEL::PHYSICS::DYNAMICS {
	private:
		unsigned int properties; // the mushed properties
	protected:
		//POGEL::PHYSICS::SOLID** objects;
		HASHLIST<POGEL::PHYSICS::SOLID*> objects;
		unsigned long numobjects;

		POGEL::PHYSICS::GRAVITYCLUSTER objectmasses;

		POGEL::PHYSICS::GRAVITYCLUSTER singularities;
		POGEL::PHYSICS::FLOW gusts;

		POGEL::OCTREE<POGEL::PHYSICS::SOLID> *ot;
		HASHLIST<POGEL::PHYSICS::SOLID*> *oltmp;

		void buildot() {
			oltmp = new HASHLIST<POGEL::PHYSICS::SOLID*>();
			oltmp->add(&objects);
			ot = new POGEL::OCTREE<POGEL::PHYSICS::SOLID>(oltmp, 1, true);
			ot->grow();
			#ifdef THREADSOK
			if(threads > 1)
				ot->FORCEfastlist();
			#endif
			#ifdef OPENGL
			glLineWidth(2);
			if(POGEL::hasproperty(POGEL_BOUNDING) && POGEL::hasproperty(POGEL_ANCESTORY)) ot->draw();
			glLineWidth(1);
			#endif
		}

		void destroyot() {
			if(ot != NULL) {
				delete ot;
				ot = NULL;
			}
			if(oltmp != NULL) {
				delete oltmp;
				oltmp = NULL;
			}
		}

	public:
		unsigned long boundingskips;

		POGEL::VECTOR gravity;
		float air_dencity;

		DYNAMICS();
		~DYNAMICS() {
			//if(objects) delete[] objects;
			objects.clear();
			destroyot();
		}

		POGEL::OCTREE<POGEL::PHYSICS::SOLID>* getotree() {
			return ot;
		}

		PROPERTIES_METHODS;

		void FORCEfastAccessList() {
			HASHLIST<POGEL::PHYSICS::SOLID*> l;
			while(objects.length()) { l.add(objects[objects.length()-1]); objects.remove(objects.length()-1); }
			objects.FORCEresizeInternalList(1);
			while(l.length()) { objects.add(l[l.length()-1]); l.remove(l.length()-1); }
		}

		unsigned long numobjs() { return objects.length(); }
		POGEL::PHYSICS::SOLID* objs(unsigned long a) { return objects[a]; }
		HASHLIST<POGEL::PHYSICS::SOLID*> objslst() { return objects; }

		unsigned long addsingularity(POGEL::PHYSICS::SINGULARITY sig) {return singularities.addsingularity(sig);}
		void addsingularities(POGEL::PHYSICS::SINGULARITY* sig, unsigned long num) {singularities.addsingularities(sig,num);}

		unsigned long addfan(POGEL::PHYSICS::FAN fan) {return gusts.addfan(fan);}
		void addfans(POGEL::PHYSICS::FAN* fan, unsigned long num) {gusts.addfans(fan,num);}

		POGEL::PHYSICS::SOLID* getSolid(char*);

		unsigned long addSolid(POGEL::PHYSICS::SOLID*);
		unsigned long addSolidHoldGravity(POGEL::PHYSICS::SOLID*);
		void addSolids(POGEL::PHYSICS::SOLID**,unsigned long);

		void addSolidsGravity(POGEL::PHYSICS::SOLID*);

		void removeSolid(POGEL::PHYSICS::SOLID*);
		void removeSolidKeepGravity(POGEL::PHYSICS::SOLID*);
		void removeSolid(char* n) {
			removeSolid(getSolid(n));
		}

		void clearAllSolids() {
            numobjects = 0;
            objects.clear();
            objectmasses.clearAll();
		}

		virtual POGEL::VECTOR getpull(POGEL::PHYSICS::SOLID*);

		virtual void increment();

		virtual void draw();

		void drawGravityGrid(float, float, POGEL::POINT, unsigned int);

		//void build();

		friend class POGEL::PHYSICS::SIMULATION;
};

#endif /* _SIMULATION_CLASS_H */
