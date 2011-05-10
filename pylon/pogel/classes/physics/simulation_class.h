#ifndef _SIMULATION_CLASS_H
#define _SIMULATION_CLASS_H

namespace POGEL {
namespace PHYSICS {
class SIMULATION;
}
}

#include "physics.h"
#include "dynamics_class.h"
#include "solid_class.h"

#define				BUPMAX						10

#define				THREADSOK					1

/*class coll {
	POGEL::POINT p;
	POGEL::VECTOR v[2];
	unsigned long obj[2];
};*/

class POGEL::PHYSICS::SIMULATION : public POGEL::PHYSICS::DYNAMICS {
	private:
		unsigned int properties; // the mushed properties
		unsigned long stepstaken;
		#ifdef THREADSOK
		unsigned int threads;
		#endif
		//coll collisionindex[numobjects][numobjects];
		unsigned char collitters;
	protected:
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
			if(POGEL::hasproperty(POGEL_BOUNDING)) ot->draw();
			glLineWidth(1);
			#endif

		}
	public:
		float precision;
		bool deactivation;
		unsigned long inactive_index;

		SIMULATION();

		void setCollItters(unsigned char i) {
			collitters = i;
			if(collitters < 1) collitters = 1;
		}

		void setThreadsNum(unsigned int t) {
			#ifdef THREADSOK
			threads = t;
			if(threads > 1) FORCEfastAccessList();
			#endif
		}

		unsigned int numThreads() {
			#ifdef THREADSOK
			return threads;
			#else
			return 1;
			#endif
		}

		unsigned long getStepsTaken() { return stepstaken; }

		void addpulls(unsigned long, unsigned long);
		void addpulls();
		void checkcollisions();
		void collincrement();
		void stepobjs();

		void increment();

		bool processcollision(POGEL::PHYSICS::SOLID*,POGEL::PHYSICS::SOLID*);

		bool processGENERAL_GENERAL(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*);
		bool processCONVEX_CONVEX(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*);
		bool processCONCAVE_CONCAVE(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*);
		bool processSPHERE_SPHERE(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*);

		bool processCONCAVESPHERE_SPHERE(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*);
		bool processSPHERE_GENERAL(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*);
		bool processSPHERE_CONVEXGENERAL(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*);
		bool processSPHERE_CONCAVEGENERAL(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*);
		bool processCONCAVESPHERE_GENERAL(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*);
		bool processCONCAVESPHERE_CONVEXGENERAL(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*);


		void reactcollision(POGEL::PHYSICS::SOLID*, POGEL::PHYSICS::SOLID*, POGEL::VECTOR, POGEL::VECTOR, POGEL::POINT);

		//friend void checkcollisions(POGEL::PHYSICS::SIMULATION* sim);
};

bool boundingcheck(POGEL::PHYSICS::SOLID *obj1, POGEL::PHYSICS::SOLID *obj2);

#endif /* _SIMULATION_CLASS_H */

