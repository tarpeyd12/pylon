#ifndef SUBRENDER_H_INCLUDED
#define SUBRENDER_H_INCLUDED

#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#include "pogelscriptinterface.h"
#endif // POGELSCRIPTINTERFACE_H_INCLUDED

#include "../renderer/renderer.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* subrender_new(Object*,Object*);
    Object* subrender_bind_sim(Object*,Object*);
    Object* subrender_release_sim(Object*,Object*);
    Object* subrender_release_all(Object*,Object*);
    Object* subrender_set_light(Object*,Object*);
    Object* subrender_set_cam(Object*,Object*);
    Object* subrender_set_ratio(Object*,Object*);
}

#endif // SUBRENDER_H_INCLUDED
