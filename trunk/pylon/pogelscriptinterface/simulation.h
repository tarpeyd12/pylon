#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#include "pogelscriptinterface.h"
#endif // POGELSCRIPTINTERFACE_H_INCLUDED

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* sim_new(Object*,Object*);
    Object* sim_toggle(Object*,Object*);
    Object* sim_halt(Object*,Object*);
    Object* sim_visibility(Object*,Object*);
    Object* sim_weight(Object*,Object*);
    Object* sim_clear(Object*,Object*);
    Object* sim_set_gravity_3f(Object*,Object*);
    Object* sim_get_gravity_3f(Object*,Object*);

    Object* sim_set_itter(Object*,Object*);
    Object* sim_get_itter(Object*,Object*);

    Object* sim_num_objects(Object*,Object*);
    Object* sim_get_object(Object*,Object*);

    Object* sim_remove_object(Object*,Object*);

    Object* sim_add_object_s(Object*,Object*);
}

#endif // SIMULATION_H_INCLUDED
