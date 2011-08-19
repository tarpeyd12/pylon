#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#include "pogelscriptinterface.h"
#endif // POGELSCRIPTINTERFACE_H_INCLUDED

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* addsimulation(Object*,Object*);
    Object* togglesimulation(Object*,Object*);
    Object* togglesimweight(Object*,Object*);
    Object* clearsimulation(Object*,Object*);
    Object* addobject(Object*,Object*);

    Object* object_move_s(Object*,Object*);
    Object* object_move_3f(Object*,Object*);

    Object* object_set_dir_3f(Object*,Object*);
    Object* object_set_pos_3f(Object*,Object*);
    Object* object_set_rot_3f(Object*,Object*);
    Object* object_set_spin_3f(Object*,Object*);

    Object* object_get_dir_s(Object*,Object*);
    Object* object_get_pos_s(Object*,Object*);
    Object* object_get_rot_s(Object*,Object*);
    Object* object_get_spin_s(Object*,Object*);

    Object* object_set_dir_s(Object*,Object*);
    Object* object_set_pos_s(Object*,Object*);
    Object* object_set_rot_s(Object*,Object*);
    Object* object_set_spin_s(Object*,Object*);
}

#endif // OBJECTS_H_INCLUDED
