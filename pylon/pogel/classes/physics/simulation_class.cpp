#include <string.h>

#include "simulation_class.h"
#include "../threads.h"

/* Just remember, in here, there is usualy no method to the madenss. */

void POGEL::PHYSICS::SIMULATION::buildot()
{
    oltmp = new HASHLIST<POGEL::PHYSICS::SOLID*>();
    while(oltmp->length() < objects.length())
        oltmp->add(objects[oltmp->length()]);
    //oltmp->add(&objects);
    ot = new POGEL::OCTREE<POGEL::PHYSICS::SOLID>(oltmp, 1, true);
    ot->grow();
    #ifdef THREADSOK
        if(threads > 1)
        {
            ot->FORCEfastlist();
        }
    #endif
    #ifdef OPENGL
        if(POGEL::hasproperty(POGEL_BOUNDING) && POGEL::hasproperty(POGEL_ANCESTORY))
        {
            glLineWidth(2);
            ot->draw();
            glLineWidth(1);
        }
    #endif
}

POGEL::PHYSICS::SIMULATION::SIMULATION() : POGEL::PHYSICS::DYNAMICS() {
    precision=0.01f;
    deactivation = false;
    inactive_index = 25;
    stepstaken = 0;
    collitters = 2;
    #ifdef THREADSOK
    if(THREADSOK)
    {
        threads = THREADSOK;
    }
    else
    {
        threads = 1;
    }
    #endif
};

void POGEL::PHYSICS::SIMULATION::addpulls(unsigned long s, unsigned long e) {
	float r = (POGEL::hasproperty(POGEL_TIMEBASIS) ? POGEL::GetSecondsPerFrame() : 1);
	for(unsigned long a = s; a < e && a < numobjs(); a++) {
		if(objects[a]->hasOption(PHYSICS_SOLID_VOLITAL) && !objects[a]->hasOption(PHYSICS_SOLID_STATIONARY)) {

			if(
				(
					deactivation
					&&
					(
						(
							(objects[a]->direction+objects[a]->force).getdistance() <= precision*r
							&&
							objects[a]->sameposlegacy(precision*r, inactive_index)
						)
						&&
						objects[a]->stepstaken > objects[a]->trailsize
						&&
						stepstaken > 100
						&&
						objects[a]->stepstaken > inactive_index
					)
					//||
					//objects[a]->napping()
				)
			) {
				objects[a]->direction = POGEL::VECTOR();
				if(!objects[a]->napping()) { objects[a]->forcegetbounding(); objects[a]->sleep(); }
			}
			else if(!deactivation) {
				objects[a]->direction += getpull(objects[a]);
				if(objects[a]->napping()) objects[a]->wake();
			}
			else if(objects[a]->napping()) { }
			else {
				objects[a]->direction += getpull(objects[a]);
				if(objects[a]->napping()) objects[a]->wake();
			}

			// TODO: get the air friction to work with timing
			float airslowdown = ( ( objects[a]->behavior.air_friction * air_dencity ) / PARTICLE_SLOWDOWN ) + 1.0f;
			objects[a]->spin /= airslowdown;
			objects[a]->direction /= airslowdown;
		}
		//objects[a]->increment();
		//objects[a]->step();
		objects[a]->clearForce();
	}
};

#ifdef THREADSOK
class thdat {
	public:
		POGEL::PHYSICS::SIMULATION* sim;
		unsigned int itt, nth;
		thdat(POGEL::PHYSICS::SIMULATION* s, unsigned int i, unsigned int n) { sim = s; itt = i; nth = n; }
		~thdat() { }
};

THREADTYPE pullrun(THREADARGS data) {
	thdat *dat = (thdat*)data;
	//printf("calculating: %u to %u\n", dat->itt*dat->nth, (dat->itt+1)*dat->nth);
	dat->sim->addpulls(dat->itt*dat->nth, (dat->itt+1)*dat->nth + (dat->itt==dat->sim->numThreads()-1?dat->sim->numobjs():0));
	delete dat;
	return NULL;
};
#endif

void POGEL::PHYSICS::SIMULATION::addpulls() {
	#ifdef THREADSOK
	if(threads > 1) {
		if(threads > numobjs()) threads = numobjs();
		POGEL::THREAD* tharr = new POGEL::THREAD[threads];
		unsigned int nth = numobjs()/threads;
		for(unsigned int i = 0; i < threads; i++) {
			tharr[i].setThread(pullrun);
			tharr[i].setData(new thdat(this, i, nth));
			tharr[i].startThread();
		}
		for(unsigned int i = 0; i < threads; i++) {
			tharr[i].joinThread();
		}
		delete[] tharr;
	}
	else
	#endif
		addpulls(0, numobjects);
};

inline bool objectIntersectionProcessing(POGEL::PHYSICS::SIMULATION* sim, unsigned long a, unsigned long b) {
	POGEL::PHYSICS::SOLID * obja = sim->objs(a);
	POGEL::PHYSICS::SOLID * objb = sim->objs(b);
	if( a!=b && boundingcheck(obja, objb) ) {
		bool ret = false;
		if( sim->processcollision(obja, objb)) {
			if(obja->callback != NULL) {
				char* n = new char[strlen(objb->getname())+1];
				memset(n, '\0', strlen(objb->getname())+1);
				strcpy(n, objb->getname());
				obja->callback(obja, n);
				delete[] n;
			}
			if(objb->callback != NULL) {
				char* n = new char[strlen(obja->getname())+1];
				memset(n, '\0', strlen(obja->getname())+1);
				strcpy(n, obja->getname());
				objb->callback(objb, n);
				delete[] n;
			}
			if(obja->napping()) obja->wake();
			if(objb->napping()) objb->wake();

			ret = true;
		}

		if(POGEL::hasproperty(POGEL_PAIRS) && b > a) {
			if(obja->hasOption(PHYSICS_SOLID_CONCAVE) && obja->hasOption(PHYSICS_SOLID_SPHERE)) {
				POGEL::VECTOR vr(obja->position, objb->position);
				vr.normalize();
				vr *= obja->bounding.maxdistance;
				vr += obja->position;
				POGEL::LINE(vr.topoint(),objb->position,1,POGEL::COLOR(1,.75,.75,1)).draw();
			}
			else if(objb->hasOption(PHYSICS_SOLID_CONCAVE) && objb->hasOption(PHYSICS_SOLID_SPHERE)) {
				POGEL::VECTOR vr(objb->position, obja->position);
				vr.normalize();
				vr *= objb->bounding.maxdistance;
				vr += objb->position;
				POGEL::LINE(obja->position,vr.topoint(),1,POGEL::COLOR(1,.75,.75,1)).draw();
			}
			else if(obja->hasOption(PHYSICS_SOLID_CONCAVE)) {

			}
			else if(objb->hasOption(PHYSICS_SOLID_CONCAVE)) {

			}
			else {
				POGEL::LINE(obja->position,objb->position,1,POGEL::COLOR(1,.75,.75,1)).draw();
			}
		}

		return ret;
	}
	return false;
};

inline void checkcollision(POGEL::PHYSICS::SIMULATION* sim, unsigned long s, unsigned long e, unsigned long o, unsigned long recnum) {
	if(recnum >= sim->getCollItters())
		return;
	unsigned long sim_numobjs = sim->numobjs();
	for( unsigned long a = s; a < e && a < sim_numobjs; a++ ) {
		POGEL::PHYSICS::SOLID* obj_a = sim->objs(a);
		if(!obj_a->napping() || obj_a->hasOption(PHYSICS_SOLID_STATIONARY)) {
			HASHLIST<unsigned int> *objs = sim->getotree()->releventIndicies(obj_a->bounding);
			if(obj_a->hasOption(PHYSICS_SOLID_CONCAVE)) {
				for( unsigned long b = 0; b < sim_numobjs; b++ )
					if(o!=a&&o!=b && objectIntersectionProcessing(sim, a, b) && !sim->objs(b)->hasOption(PHYSICS_SOLID_STATIONARY)) {
						obj_a->makebounding();
						checkcollision(sim,b,b+1,a,recnum+1);
					}
				if(objs != NULL)
					delete objs;
			}
			else if(objs != NULL) {
				unsigned int objs_length = objs->length();
				for( unsigned long b = 0; b < objs_length; b++ ) {
					unsigned int obj_b = objs->get(b);
					if( o!=a&&o!=obj_b && obj_b < sim_numobjs && objectIntersectionProcessing(sim, a, obj_b) && !sim->objs(obj_b)->hasOption(PHYSICS_SOLID_STATIONARY)) {
						sim->objs(obj_b)->makebounding();
						checkcollision(sim,obj_b,obj_b+1,a,recnum+1);
					}
				}
				delete objs;
			}
		}
	}
};

inline void checkcollision(POGEL::PHYSICS::SIMULATION* sim) { checkcollision(sim, 0, sim->numobjs(),sim->numobjs(),0); };

#ifdef THREADSOK
THREADTYPE collrun(THREADARGS data) {
	thdat *dat = (thdat*)data;
	//printf("calculating: %u to %u\n", dat->itt*dat->nth, (dat->itt+1)*dat->nth);
	checkcollision(dat->sim, dat->itt*dat->nth, (dat->itt+1)*dat->nth + (dat->itt==dat->sim->numThreads()-1?dat->sim->numobjs():0),dat->sim->numobjs(),0);
	delete dat;
	return NULL;
};
#endif

void POGEL::PHYSICS::SIMULATION::checkcollisions() {
	#ifdef THREADSOK
	if(threads > 1) {
		if(threads > numobjs()) threads = numobjs();
		POGEL::THREAD* tharr = new POGEL::THREAD[threads];
		unsigned int nth = numobjs()/threads;
		for(unsigned int i = 0; i < threads; i++) {
			tharr[i].setThread(collrun);
			tharr[i].setData(new thdat(this, i, nth));
			tharr[i].startThread();
		}
		for(unsigned int i = 0; i < threads; i++)
			tharr[i].joinThread();
		delete[] tharr;
	}
	else
	#endif
		checkcollision(this);
};

void POGEL::PHYSICS::SIMULATION::stepobjs() {
	unsigned long l = objects.length();
	for(unsigned long a=0;a<l;a++) {
		if(!objects[a]->napping())
			objects[a]->step();
		else if(objects[a]->function)
			objects[a]->function(objects[a]);
		if(objects.length() < l) { l--; a--; }
	}
};

void POGEL::PHYSICS::SIMULATION::collincrement() {
	//for(int g = 0; g < collitters; g++)
		checkcollisions();
};

void POGEL::PHYSICS::SIMULATION::increment() {
	destroyot();
	buildot();

	addpulls();
	collincrement();
	stepobjs();
	stepstaken++;
};

