#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#include "pogelscriptinterface.h"
#endif // POGELSCRIPTINTERFACE_H_INCLUDED

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* object_add_sphere(Object*,Object*);
    Object* object_add_sphere_mat(Object*,Object*);

    Object* object_add_disk(Object*,Object*);
    Object* object_add_disk_mat(Object*,Object*);

    Object* object_add_cylinder(Object*,Object*);
    Object* object_add_cylinder_mat(Object*,Object*);

    Object* object_add_cube(Object*,Object*);
    Object* object_add_cube_mat(Object*,Object*);
}

#endif // SHAPES_H_INCLUDED
