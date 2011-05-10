#ifndef _OBJECT_CLASS_H
#define _OBJECT_CLASS_H

#include <stdlib.h>
#include <string.h>

namespace POGEL {
class OBJECT;
}

#include "point_class.h"
#include "triangle_class.h"
#include "matrix_class.h"
#include "../pogel_internals.h"
#include "physics/physics.h"

#define			OBJECT_DEBUG				1
#define			OBJECT_DRAW_DISPLAYLIST		2
#define			OBJECT_DRAW_COLORED_STRIP	4
#define			OBJECT_DRAW_CHILDREN		8
#define			OBJECT_ROTATE_XYZ			16
//#define			OBJECT_ROTATE_ZYX			32
#define			OBJECT_SORT_TRIANGLES		64
#define			OBJECT_ROTATE_TOCAMERA		128

#define			OBJECT_USE_OPNEGL_MATRIX_RECURSION

#define			OBJECT_TRIAGLE_ALLOCATION_SKIP	1000

namespace POGEL {
class OBJECT {
	private:
		unsigned int properties; // the mushed options
	protected:
		POGEL::TRIANGLE *face; // the array of triangle faces
		unsigned long numfaces; // the number of triangles in the triangle array
		POGEL::OBJECT **children; // the array of pointers to child objects
		POGEL::OBJECT *parent; // the parent of this object if it is a child object
		unsigned long numchildren; // the number of children objects
		char* name; // the name of the object, used for identification in the tree of children objects
		
		unsigned long triangle_allocation_total;
	public:
		POGEL::POINT position; // the center position of the object
		POGEL::POINT rotation; // the rotation arround the center of the object
		POGEL::VECTOR direction; // the movement vector
		POGEL::VECTOR spin; // the spin vector
		unsigned int base; // the pointer ot the compiled display list
		POGEL::MATRIX matrix;
		bool visable;
		
		OBJECT();
		OBJECT(unsigned int);
		OBJECT(POGEL::TRIANGLE*,unsigned long,unsigned int);
		OBJECT(POGEL::TRIANGLE*,unsigned long,unsigned int,POGEL::POINT,POGEL::POINT);
		
		OBJECT(const char*);
		OBJECT(const char*,unsigned int);
		OBJECT(const char*,POGEL::TRIANGLE*,unsigned long,unsigned int);
		OBJECT(const char*,POGEL::TRIANGLE*,unsigned long,unsigned int,POGEL::POINT,POGEL::POINT);
		
		OBJECT(POGEL::OBJECT* obj) {
			face=obj->face;
			numfaces=obj->numfaces;
			triangle_allocation_total=obj->triangle_allocation_total;
			children=obj->children;
			parent=obj->parent;
			numchildren=obj->numchildren;
			name=obj->name;
			properties=obj->properties;
			position=obj->position;
			rotation=obj->rotation;
			base=obj->base;
			matrix=obj->matrix;
			visable=obj->visable;
		}
		
		~OBJECT();
		void killchildren();
		
		PROPERTIES_METHODS;
		
		void setname(const char *n) { 
			if(name!=NULL) delete[] name;
			name = new char[strlen(n)];
			strcpy(name, n);
			//name=(char*)n;
		}
		char* getname() {return name;}
		std::string getsname() {return std::string(name);}
		unsigned long getchildslot();
		
		void translate(POGEL::VECTOR);
		void translate(POGEL::VECTOR,float);
		void moveto(POGEL::POINT p) {position=p;}

		void rotate(POGEL::VECTOR);
		void rotate(POGEL::VECTOR,float);
		void turnto(POGEL::POINT r) {rotation=r;}
		
		unsigned long addtriangle(POGEL::TRIANGLE);
		void addtriangles(POGEL::TRIANGLE*,unsigned long);
		void addtrianglespace(unsigned long);
		
		void cleartriangles();
		
		unsigned long addobject(POGEL::OBJECT*);
		void addobjects(POGEL::OBJECT**,unsigned long);
		
		void scroll_all_tex_values(float,float);
		
		POGEL::OBJECT* getchild(const char*);
		POGEL::OBJECT* getdecendant(const char*,bool);
		POGEL::OBJECT* getdecendant(const char*);
		
		POGEL::OBJECT* getancestor(const char*);
		POGEL::OBJECT* getprogenitor();
		char *getancestory();
		char *getancestoryhash();
		
		POGEL::MATRIX getancestorialmatrix();
		
		unsigned long getnumfaces() {
			return numfaces;
		}
		
		POGEL::TRIANGLE gettriangle(unsigned long i) {
			return face[i];
		}
		
		POGEL::TRIANGLE* gettrianglelist() {
			return face;
		}
		
		void copytriangles(POGEL::OBJECT* o) {
			this->addtriangles(o->gettrianglelist(), o->getnumfaces());
		}
		
		void referencetriangles(POGEL::OBJECT* o) {
			cleartriangles();
			face = o->gettrianglelist();
			numfaces = o->getnumfaces();
			triangle_allocation_total = o->triangle_allocation_total;
		}
		
		void settriangle(unsigned long i, POGEL::TRIANGLE t) {
			face[i] = t;
		}
		
		void increment() {
			rotate(spin);
			translate(direction);
		}
		
		virtual void build();
		virtual void draw();
		
		virtual void stepFunc() {}
		
		virtual void step() {
			increment();
			stepFunc();
		}
		
		virtual void create() {}
		virtual void destroy() {}
		
		//virtual void grow() {}
		
		friend bool POGEL::PHYSICS::solid_collision(POGEL::PHYSICS::SOLID*,POGEL::PHYSICS::SOLID*,POGEL::POINT*,POGEL::VECTOR*,POGEL::VECTOR*,float*);
};
}

#endif /* _OBJECT_CLASS_H */
