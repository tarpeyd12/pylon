#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#include "pogelscriptinterface.h"
#endif // POGELSCRIPTINTERFACE_H_INCLUDED

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* object_new(Object*,Object*);
    Object* object_new_fromfile(Object*,Object*);
    Object* object_new_child(Object*,Object*);

    Object* object_set_visibility(Object*,Object*);

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

    Object* object_options(Object*,Object*);

    Object* object_set_mass(Object*,Object*);
    Object* object_get_mass(Object*,Object*);

    Object* object_set_bounce(Object*,Object*);
    Object* object_get_bounce(Object*,Object*);

    Object* object_set_friction(Object*,Object*);
    Object* object_get_friction(Object*,Object*);

    Object* object_add_key(Object*,Object*);

    Object* object_add_animation(Object*,Object*);
    Object* object_set_animation(Object*,Object*);
    Object* object_get_animation(Object*,Object*);
    Object* object_set_animtime(Object*,Object*);
    Object* object_get_animlen(Object*,Object*);
    Object* object_get_animsince(Object*,Object*);

    Object* object_build(Object*,Object*);
}

#endif // OBJECTS_H_INCLUDED
