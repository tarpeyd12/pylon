#ifndef _SINGULARITY_CLASS_H
#define _SINGULARITY_CLASS_H

#include <stdlib.h>

namespace POGEL {
namespace PHYSICS {
class SINGULARITY;
class FAN;
class FLOW;
class GRAVITYCLUSTER;
}
}

#include "../../templates/classlist_template.h"
#include "physics.h"
#include "../point_class.h"

//#define			GRAVITYCONSTANT			((float)pow(10.0f, -11.0f)*6.673f)
#define			GRAVITYCONSTANT			0.00000000006673

class POGEL::PHYSICS::SINGULARITY {
	public:
		bool active;
		POGEL::POINT *pcenter;
		float *pintencity;
		POGEL::POINT center;
		float intencity;
		
		bool notpointing;
		
		SINGULARITY() { center=POGEL::POINT(); intencity=0.0f; active=true; notpointing=true; }
		SINGULARITY(POGEL::POINT p, float i) { center=p; intencity=i; active=true; notpointing=true; }
		SINGULARITY(POGEL::POINT *p, float *i) { pcenter=p; pintencity=i; active=true; notpointing=false; }
		SINGULARITY(float x, float y, float z, float i) { center=POGEL::POINT(x,y,z); intencity=i; active=true; notpointing=true; }
		
		//~SINGULARITY() { if(notpointing) { delete pcenter; delete pintencity; } }
		
		POGEL::POINT getCenter() { if(notpointing) return center; return *pcenter; }
		float getIntencity() { if(notpointing) return intencity; return *pintencity; }
		
		POGEL::POINT getposition() { return getCenter(); }
		POGEL::BOUNDING getbounding() {
			return POGEL::BOUNDING( 0,
				getposition().x,getposition().x,
				getposition().y,getposition().y,
				getposition().z,getposition().z);
		}
		
		virtual POGEL::VECTOR getpull(POGEL::POINT p, float mass) {
			if(active) {
				if(p==getCenter()) return POGEL::VECTOR();
				float dist = p.distance(getCenter());
				if(dist*dist > 0.00001 && 1/(dist*dist) > 0.00001) {
					POGEL::VECTOR v (p, getCenter());
					v.normalize();
					v *= getIntencity() * mass * GRAVITYCONSTANT;
					v /= (dist*dist);
					if(mass < 0.0) v*=-1.0;
					return v;
				}
				//return POGEL::VECTOR();
			}
			return POGEL::VECTOR();
		}
};

class POGEL::PHYSICS::FAN : public POGEL::PHYSICS::SINGULARITY {
	public:
		POGEL::VECTOR direction;
		POGEL::VECTOR *pdirection;
		
		FAN() : SINGULARITY() { direction=POGEL::VECTOR(); }
		FAN(POGEL::POINT p, POGEL::VECTOR v, float i) : SINGULARITY(p,i) { direction=v; }
		FAN(float x, float y, float z, POGEL::VECTOR v, float i) : SINGULARITY(x,y,z,i) { direction=v; }
		FAN(POGEL::POINT p, float x, float y, float z, float i) : SINGULARITY(p,i) { direction=POGEL::VECTOR(x,y,z); }
		FAN(float x, float y, float z, float vx, float vy, float vz, float i) : SINGULARITY(x,y,z,i) { direction=POGEL::VECTOR(vx,vy,vz); }
		
		POGEL::VECTOR getDirection() { if(notpointing) return direction; return *pdirection; }
		
		POGEL::VECTOR getpull(POGEL::POINT p, float mass) {
			if(active) return ((getDirection()*getIntencity())/p.distance(getCenter()))/(mass+1.0f);
			return POGEL::VECTOR();
		}
};

class POGEL::PHYSICS::GRAVITYCLUSTER {
		CLASSLIST<POGEL::PHYSICS::SINGULARITY>* singularities;
		unsigned long numsingularities;
	public:
		
		GRAVITYCLUSTER()
			{  numsingularities = 0; singularities = new CLASSLIST<POGEL::PHYSICS::SINGULARITY>(); }
		~GRAVITYCLUSTER()
			{ singularities->clear(); if(singularities) delete singularities; }
		
		unsigned long addsingularity(POGEL::PHYSICS::SINGULARITY);
		void addsingularities(POGEL::PHYSICS::SINGULARITY*,unsigned long);
		
		void remove(unsigned long i) { singularities->remove(i); numsingularities--; }
		
		POGEL::VECTOR getpull(POGEL::POINT p, float mass) {
			if(numsingularities==0) return POGEL::VECTOR();
			POGEL::VECTOR v;
			for(unsigned int i=0;i<numsingularities;i++) v+=singularities->get(i).getpull(p, mass);
			return v;
		}
		
		/*POGEL::VECTOR fgetpull(POGEL::POINT p, float mass, HASHLIST<POGEL::OCTREE<POGEL::PHYSICS::SOLID>*> *otlst) {
			
			if(numsingularities==0) return POGEL::VECTOR();
			POGEL::VECTOR v;
			for(unsigned int i=0;i<numsingularities;i++) v+=singularities[i].getpull(p, mass);
			return v;
		}*/
		
		POGEL::PHYSICS::GRAVITYCLUSTER& operator = (POGEL::PHYSICS::GRAVITYCLUSTER g) {
			singularities->clear();
			if(singularities)
				delete singularities;
			singularities = g.singularities;
			numsingularities = g.numsingularities;
			return *this;
		}
};

class POGEL::PHYSICS::FLOW {
		CLASSLIST<POGEL::PHYSICS::FAN> gusts;
		unsigned long numgusts;
	public:
		
		FLOW() { numgusts = 0; }
		FLOW(POGEL::POINT* waypoints,unsigned long num,bool forwards) {generatecurve(waypoints,num,forwards);}
		~FLOW() { gusts.clear(); }
		
		unsigned long addfan(POGEL::PHYSICS::FAN);
		void addfans(POGEL::PHYSICS::FAN*,unsigned long);
		
		void remove(unsigned long i) { gusts.remove(i); numgusts--; }
		
		void generatecurve(POGEL::POINT*,unsigned long,bool);
		
		POGEL::VECTOR getpull(POGEL::POINT p, float mass) {
			if(numgusts==0) return POGEL::VECTOR();
			POGEL::VECTOR v;
			unsigned int diff=0;
			for(unsigned int i=0;i<numgusts;i++)
				if(gusts[i].active) v=v+gusts[i].getpull(p, mass);
				else diff++;
			if(diff<numgusts) return v/((float)numgusts - (float)diff);
			else return POGEL::VECTOR();
		}
};

#endif /* _SINGULARITY_CLASS_H */

