#include "simulation_class.h"

/* Just remember, in here, there is usualy no method to the madenss. */

// TODO: clean up this file, and comment the FUCK out of it.

inline void unocupyobjs(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2, POGEL::VECTOR v, float d) {
	v.normalize();
	float p1 = 1;//obj2->bounding.maxdistance/(obj1->bounding.maxdistance + obj2->bounding.maxdistance);
	float p2 = 1;//obj1->bounding.maxdistance/(obj1->bounding.maxdistance + obj2->bounding.maxdistance);
	if(!obj1->hasOption(PHYSICS_SOLID_STATIONARY) && !obj2->hasOption(PHYSICS_SOLID_STATIONARY)) {
		obj1->force += (v * d/2*p1);
		obj2->force += (v *-d/2*p2);
		obj1->translate(v * d/2*p1);
		obj2->translate(v *-d/2*p2);
	}
	else if(!obj1->hasOption(PHYSICS_SOLID_STATIONARY) && obj2->hasOption(PHYSICS_SOLID_STATIONARY)) {
		obj1->force += (v * d/1*p1);
		obj1->translate(v * d/1*p1);
	}
	else if(obj1->hasOption(PHYSICS_SOLID_STATIONARY) && !obj2->hasOption(PHYSICS_SOLID_STATIONARY)) {
		obj2->force += (v *-d/1*p2);
		obj2->translate(v *-d/1*p2);
	}
};


bool POGEL::PHYSICS::SIMULATION::processcollision(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2) {
	// if both are stationary do nothing
	if(obj1 == obj2 || (obj1->hasOption(PHYSICS_SOLID_STATIONARY) && obj2->hasOption(PHYSICS_SOLID_STATIONARY)))
		return false;
	
	// if either are concave do the concave checking
	if(obj1->hasOption(PHYSICS_SOLID_CONCAVE) || obj2->hasOption(PHYSICS_SOLID_CONCAVE)) {
		// concave general shape vs. assumed convex sphere
		if(
			(obj1->hasOption(PHYSICS_SOLID_CONCAVE) && !obj1->hasOption(PHYSICS_SOLID_SPHERE) && obj2->hasOption(PHYSICS_SOLID_SPHERE)) ||
			(obj2->hasOption(PHYSICS_SOLID_CONCAVE) && !obj2->hasOption(PHYSICS_SOLID_SPHERE) && obj1->hasOption(PHYSICS_SOLID_SPHERE))
		)
			return processSPHERE_CONCAVEGENERAL(obj1, obj2);
		// concave sphere vs. assumed convex sphere
		if(
			(obj1->hasOption(PHYSICS_SOLID_SPHERE|PHYSICS_SOLID_CONCAVE) && obj2->hasOption(PHYSICS_SOLID_SPHERE)) || 
			(obj2->hasOption(PHYSICS_SOLID_SPHERE|PHYSICS_SOLID_CONCAVE) && obj1->hasOption(PHYSICS_SOLID_SPHERE))
		)
			return processCONCAVESPHERE_SPHERE(obj1, obj2);
		// concave sphere vs. actual convex general shape
		if(
			(obj1->hasOption(PHYSICS_SOLID_SPHERE|PHYSICS_SOLID_CONCAVE) && 
			obj2->hasOption(PHYSICS_SOLID_CONVEX) && !obj2->hasOption(PHYSICS_SOLID_SPHERE)) ||
			(obj2->hasOption(PHYSICS_SOLID_SPHERE|PHYSICS_SOLID_CONCAVE) && 
			obj1->hasOption(PHYSICS_SOLID_CONVEX) && !obj1->hasOption(PHYSICS_SOLID_SPHERE))
		)
			return processCONCAVESPHERE_CONVEXGENERAL(obj1, obj2);
		// concave sphere vs. assumed convex general shape
		if(
			(obj1->hasOption(PHYSICS_SOLID_SPHERE|PHYSICS_SOLID_CONCAVE)) || 
			(obj2->hasOption(PHYSICS_SOLID_SPHERE|PHYSICS_SOLID_CONCAVE))
		)
			return processCONCAVESPHERE_GENERAL(obj1, obj2);
	}
	
	// convex sphere vs. convex general shape
	if(
		(obj1->hasOption(PHYSICS_SOLID_SPHERE) && !obj2->hasOption(PHYSICS_SOLID_SPHERE) && obj2->hasOption(PHYSICS_SOLID_CONVEX)) || 
		(obj2->hasOption(PHYSICS_SOLID_SPHERE) && !obj1->hasOption(PHYSICS_SOLID_SPHERE) && obj1->hasOption(PHYSICS_SOLID_CONVEX))
	)
		return processSPHERE_CONVEXGENERAL(obj1, obj2);
	
	// convex sphere vs. general shape
	else if(
		(obj1->hasOption(PHYSICS_SOLID_SPHERE) && !obj2->hasOption(PHYSICS_SOLID_SPHERE)) || 
		(obj2->hasOption(PHYSICS_SOLID_SPHERE) && !obj1->hasOption(PHYSICS_SOLID_SPHERE))
	)
		return processSPHERE_GENERAL(obj1, obj2);
	
	// convex sphere vs. convex sphere
	else if(obj1->hasOption(PHYSICS_SOLID_SPHERE) && obj2->hasOption(PHYSICS_SOLID_SPHERE))
		return processSPHERE_SPHERE(obj1, obj2);
	
	// convex general vs. convex general
	if(obj1->hasOption(PHYSICS_SOLID_CONVEX) && obj2->hasOption(PHYSICS_SOLID_CONVEX))
		return processCONVEX_CONVEX(obj1, obj2);
	/*if(obj1->hasOption(PHYSICS_SOLID_CONCAVE) && obj2->hasOption(PHYSICS_SOLID_CONCAVE))
		return processCONCAVE_CONCAVE(obj1, obj2);*/
		
	// unknown general vs. unknown general
	return processGENERAL_GENERAL(obj1, obj2);
};

// TODO: maek this work:
/* *************************** Does not work ******************************** */
bool POGEL::PHYSICS::SIMULATION::processCONVEX_CONVEX(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2) {
	POGEL::POINT p1, p2, tmp, tmp1, tmp2, obj1_ep, obj2_ep;
	POGEL::TRIANGLE t1, t2, tri;
	obj1->closest(obj2, &p1, &p2, &t1, &t2);
	
	/*obj1->closest(p2, &tmp1, &tri);
	if(tmp1 == obj1->position)
		POGEL::message("hello 1\n");
	obj2->closest(p1, &tmp2, &tri);
	if(tmp2 == obj2->position)
		POGEL::message("hello 2\n");*/
	
	//p1.draw();
	//p2.draw();
	//p1.drawto(p2);
	//tmp1.drawto(tmp2);
	
	POGEL::PHYSICS::solid_line_collision(PHYSICS_LINESOLID_COLLISION_GREATEST, obj1, obj1->position, p1, &tri, &tmp, &obj1_ep);
	//obj1_ep.draw();
	float dst1 = tmp.z;
	
	POGEL::PHYSICS::solid_line_collision(PHYSICS_LINESOLID_COLLISION_GREATEST, obj2, obj2->position, p2, &tri, &tmp, &obj2_ep);
	//obj2_ep.draw();
	float dst2 = tmp.z;

	//POGEL::message("hello %f, %f\n", (obj1_ep.distance(obj2_ep) + dst1+dst2), obj1->position.distance(obj2->position));
	
	//if( (obj1_ep.distance(obj2_ep) + dst1+dst2) > obj1->position.distance(obj2->position)  ) {
	if(obj1->position.distance(obj2->position) < (dst1+dst2)) {
		POGEL::VECTOR v(p1,p2);
		//if(p1 != obj1->position && p2 != obj2->position && p1 != obj2->position && p2 != obj1->position) {
		//if(p1 != p2) {
		unocupyobjs(obj1,obj2,v,-p1.distance(p2));
			//obj1->translate(v.normal() * p1.distance(p2)*-.5);
			//obj2->translate(v.normal() * p1.distance(p2)*.5);
		//}
		reactcollision(obj1, obj2, (v.normal()+t1.normal).normal(), t2.normal, (p1+p2)/2.0f);
	
		//if(p1 == obj1->position || p2 == obj2->position)
		return true;
	}
	return false;
};



bool POGEL::PHYSICS::SIMULATION::processGENERAL_GENERAL(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2) {
	POGEL::VECTOR vct1, vct2;
	float area;
	POGEL::POINT col;
	if(obj1->bounding.checkbounding(obj2->bounding) && POGEL::PHYSICS::solid_collision(obj1, obj2, &col, &vct1, &vct2, &area)) {
		reactcollision(obj1, obj2, vct1, vct2, col);
		return true;
	}
	
	return false;
};

bool POGEL::PHYSICS::SIMULATION::processSPHERE_SPHERE(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2) {
	
	if(obj1->position.distance(obj2->position) < (obj1->bounding.maxdistance + obj2->bounding.maxdistance)) {
		POGEL::VECTOR v(obj1->position, obj2->position);
		POGEL::POINT p = obj1->position + (v.normal() * obj1->bounding.maxdistance).topoint();
		
		if(POGEL::hasproperty(POGEL_COLLISIONS))
			p.draw();
		
		float d = obj1->position.distance(obj2->position) - (obj1->bounding.maxdistance + obj2->bounding.maxdistance);
		
		unocupyobjs(obj1,obj2,v,d);
		
		reactcollision(obj1, obj2, POGEL::VECTOR(obj1->position, obj2->position).normal(), POGEL::VECTOR(obj2->position, obj1->position).normal(), p);
		return true;
	}
	
	return false;
};

bool POGEL::PHYSICS::SIMULATION::processSPHERE_GENERAL(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2) {
	// make object 1 the sphere
	if(obj2->hasOption(PHYSICS_SOLID_SPHERE) && !obj1->hasOption(PHYSICS_SOLID_SPHERE))
		return processSPHERE_GENERAL(obj2, obj1);
	
	POGEL::POINT tmp_1, tmp_2;
	POGEL::TRIANGLE tmptri;
	
	obj2->closest(obj1->position, &tmp_2, &tmptri);
	if(obj1->position.distance(tmp_2) <= (obj1->bounding.maxdistance)) {
		if(POGEL::hasproperty(POGEL_COLLISIONS))
			tmp_2.draw();
		POGEL::VECTOR v = tmptri.normal * (tmptri.isinfront(obj1->position) ? 1 : -1);
		reactcollision(obj1, obj2, POGEL::VECTOR(tmp_2, obj2->position).normal()*1, v.normal()*-1, tmp_2);
		return true;
	}
	
	return false;
};

bool POGEL::PHYSICS::SIMULATION::processSPHERE_CONVEXGENERAL(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2) {
	// make object 1 the sphere
	if(obj2->hasOption(PHYSICS_SOLID_SPHERE) && !obj1->hasOption(PHYSICS_SOLID_SPHERE))
		return processSPHERE_CONVEXGENERAL(obj2, obj1);
	
	float radius = obj1->bounding.maxdistance;
	
	POGEL::POINT disttest, linetest;
	POGEL::TRIANGLE tmptri_dist, tmptri_line;
	POGEL::POINT c2d;
	
	/*obj2->closest(
		POGEL::VECTOR(obj1->position,obj2->position).normal()*50+obj1->position, 
		&disttest, &tmptri_dist
	);*/
	//bool lc = 
	POGEL::PHYSICS::solid_line_collision(
		PHYSICS_LINESOLID_COLLISION_GREATEST, 
		obj2, obj2->position, obj1->position, 
		&tmptri_line, &c2d, &linetest
	);
	
	POGEL::VECTOR v;
	float d;
	
	bool inside = false;
	if(obj2->position.distance(linetest) > obj2->position.distance(obj1->position))//-obj1->bounding.maxdistance)
	if(linetest == obj2->position || tmptri_line.isinfront(obj2->position) == tmptri_line.isinfront(obj1->position)) {
		//POGEL::PHYSICS::solid_line_collision(PHYSICS_LINESOLID_COLLISION_GREATEST, obj2, obj2->position, obj1->position, &tmptri_line, &c2d, &linetest);
		v = obj1->direction.normal() - obj2->direction.normal();
		if(v.getdistance() == 0.0f) v = POGEL::VECTOR(obj2->position, linetest);//obj1->position-obj2->position;
		d = (obj1->bounding.maxdistance + linetest.distance(obj2->position)) - obj1->position.distance(obj2->position);
		unocupyobjs(obj1,obj2,v,d);
		//obj2->closest(obj1->position, &disttest, &tmptri_dist);
		inside = true;
	}
	obj2->closest(obj1->position, &disttest, &tmptri_dist);
	if(
		//inside || 
		obj1->position.distance(disttest) < radius || 
		obj1->position.distance(linetest) < radius //||
		//tmptri_line.isinfront(obj1->position) != tmptri_line.isinfront(obj2->position) ||
		//tmptri_dist.isinfront(obj1->position) != tmptri_dist.isinfront(obj2->position)
	) {
		if(POGEL::hasproperty(POGEL_COLLISIONS))
			(/*lc?linetest:*/disttest).draw();
		v = POGEL::VECTOR(obj1->position, (/*lc?linetest:*/disttest));
		d = obj1->position.distance(/*lc?linetest:*/disttest) - radius;
		unocupyobjs(obj1,obj2,v,d);
		POGEL::POINT p = disttest;
		if(obj2->hasOption(PHYSICS_SOLID_STATIONARY))
			v = POGEL::VECTOR(obj1->position,obj2->position).normal()*0 + (/*lc?tmptri_line:*/tmptri_dist).normal*1;
		v.normalize();
		reactcollision(obj1, obj2, v*-1, v, p);
		return true;
	}
	
	return false;
};

bool POGEL::PHYSICS::SIMULATION::processSPHERE_CONCAVEGENERAL(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2) {
	// make object 1 the sphere
	if(obj2->hasOption(PHYSICS_SOLID_SPHERE) && !obj1->hasOption(PHYSICS_SOLID_SPHERE))
		return processSPHERE_CONCAVEGENERAL(obj2, obj1);
	
	POGEL::POINT tmp_1, tmp_2;
	POGEL::TRIANGLE tmptri;
	
	POGEL::POINT c3d, c2d;
	
	POGEL::PHYSICS::solid_line_collision(PHYSICS_LINESOLID_COLLISION_LEAST, obj2, obj1->position, obj1->position+POGEL::VECTOR(obj2->position,obj1->position), &tmptri, &c2d, &tmp_2);
	if(tmp_2 == obj2->position) return false;//obj2->closest(obj1->position, &tmp_2, &tmptri);
	POGEL::VECTOR v;
	float d;
	bool outside = false;
	
	if(
		tmptri.isinfront(obj2->position) != tmptri.isinfront(obj1->position) 
		|| 
		obj1->position.distance(obj2->position)+obj1->bounding.maxdistance > obj2->position.distance(tmp_2) 
	) {
		v = obj1->position - obj2->position;
		//d = obj1->position.distance(obj2->position) - (obj1->bounding.maxdistance + tmp_2.distance(obj2->position));
		d = obj1->bounding.maxdistance - obj1->position.distance(tmp_2);
		// TODO: find out why:
		if(obj1->position.distance(obj2->position)+obj1->bounding.maxdistance >= obj2->position.distance(tmp_2))
			unocupyobjs(obj1,obj2,v*0-obj1->direction,d); // this sometimes causes a wierd error, cant figure out why
		outside = true;
	}
	obj2->closest(obj1->position, &tmp_2, &tmptri);
	
	if((obj1->position.distance(tmp_2) < obj1->bounding.maxdistance && tmptri.isinfront(obj1->position) == tmptri.isinfront(obj2->position) && tmp_2 != obj2->position) || outside) {
		if(POGEL::hasproperty(POGEL_COLLISIONS))
			tmp_2.draw();
		v = POGEL::VECTOR(obj1->position, tmp_2);
		d = obj1->position.distance(tmp_2);
		
		unocupyobjs(obj1,obj2,v,d);
		
		if(tmptri.isinfront(v.normal()+tmptri.middle()) != tmptri.isinfront(obj2->position))
			unocupyobjs(obj1, obj2, v, -obj1->bounding.maxdistance);
		else
			unocupyobjs(obj1, obj2, v,  obj1->bounding.maxdistance);
			
		v = POGEL::VECTOR(obj1->position,obj2->position).normal()*0 + tmptri.normal*1;
		v.normalize();
		reactcollision(obj1, obj2, v, v * -1, tmp_2);
		return true;
	}
	
	return false;
};

bool POGEL::PHYSICS::SIMULATION::processCONCAVESPHERE_SPHERE(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2) {
	
	if(obj2->hasOption(PHYSICS_SOLID_CONCAVE) && !obj1->hasOption(PHYSICS_SOLID_CONCAVE))
		return processCONCAVESPHERE_SPHERE(obj2, obj1);
	
	if(obj1->position.distance(obj2->position) > fabs(obj2->bounding.maxdistance - obj1->bounding.maxdistance)) {
		POGEL::VECTOR v(obj1->position, obj2->position);
		POGEL::POINT p = obj1->position + (v.normal() * obj1->bounding.maxdistance).topoint();		
		
		if(POGEL::hasproperty(POGEL_COLLISIONS))
			p.draw();
		
		float d = obj1->position.distance(obj2->position) - fabs(obj2->bounding.maxdistance - obj1->bounding.maxdistance);
		
		//if((obj2->position + obj2->direction.normal().topoint()).distance(obj1->position) < obj1->position.distance(obj2->position))
			//obj2->translate(v.normal() * d  );
		//else if((obj2->position - obj2->direction.normal().topoint()).distance(obj1->position) < obj1->position.distance(obj2->position))
		unocupyobjs(obj1,obj2,v,d);
		
		reactcollision(obj1, obj2, POGEL::VECTOR(obj1->position, p).normal()*1, POGEL::VECTOR(obj2->position, p).normal()*1, p);
		return true;
	}
	
	return false;
};

bool POGEL::PHYSICS::SIMULATION::processCONCAVESPHERE_GENERAL(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2) {
	
	if(obj2->hasOption(PHYSICS_SOLID_CONCAVE) && !obj1->hasOption(PHYSICS_SOLID_CONCAVE))
		return processCONCAVESPHERE_GENERAL(obj2, obj1);
	
	POGEL::VECTOR v(obj1->position, obj2->position);
	v.normalize();
	v *= obj1->bounding.maxdistance*2;
	POGEL::POINT p = obj1->position + v;
	
	POGEL::POINT tmp;
	POGEL::TRIANGLE tmptri;
	
	obj2->closest(p, &tmp, &tmptri);
	
	if(obj1->position.distance(tmp) >= obj1->bounding.maxdistance) {
		if(POGEL::hasproperty(POGEL_COLLISIONS))
			p.draw();
		POGEL::VECTOR c = tmptri.normal * (tmptri.isinfront(obj1->position) ? 1 : -1);
		
		float d = obj2->position.distance(tmp)/2;
		v = POGEL::VECTOR(obj2->position,p);
		unocupyobjs(obj1,obj2,v,d);
		
		reactcollision(obj1, obj2, (v+c).normal(), (v+c).normal(), p);
		return true;
	}
	
	return false;
};

bool POGEL::PHYSICS::SIMULATION::processCONCAVESPHERE_CONVEXGENERAL(POGEL::PHYSICS::SOLID* obj1, POGEL::PHYSICS::SOLID* obj2) {
	
	if(obj2->hasOption(PHYSICS_SOLID_CONCAVE) && !obj1->hasOption(PHYSICS_SOLID_CONCAVE))
		return processCONCAVESPHERE_CONVEXGENERAL(obj2, obj1);
	if(obj2->hasOption(PHYSICS_SOLID_SPHERE) && !obj1->hasOption(PHYSICS_SOLID_SPHERE))
		return processCONCAVESPHERE_CONVEXGENERAL(obj2, obj1);
	
	POGEL::VECTOR v(obj1->position, obj2->position);
	v.normalize();
	v *= obj1->bounding.maxdistance*5;
	POGEL::POINT p = obj1->position + v;
	
	POGEL::POINT tmp;
	POGEL::TRIANGLE tmptri;
	
	obj2->closest(p, &tmp, &tmptri);
	
	POGEL::POINT psph = POGEL::VECTOR(obj1->position, tmp).normal()*obj1->bounding.maxdistance;
	
	if(obj1->position.distance(tmp) > obj1->bounding.maxdistance) {
		if(POGEL::hasproperty(POGEL_COLLISIONS)) {
			tmp.draw(); psph.draw();
		}
		POGEL::VECTOR c = tmptri.normal * (tmptri.isinfront(obj1->position) ? 1 : -1);
		c.normalize();
		float d = obj1->position.distance(tmp) - obj1->bounding.maxdistance;
		v = POGEL::VECTOR(obj1->position,tmp);
		unocupyobjs(obj1,obj2,v,d);
		//v.normalize();
		reactcollision(obj1, obj2, (v).normal(), (v).normal(), psph);
		return true;
	}
	
	return false;
};

