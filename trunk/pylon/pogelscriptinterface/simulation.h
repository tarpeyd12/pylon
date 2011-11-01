#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

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
    Object* setsimulationgravity_3f(Object*,Object*);

    Object* setsimulationcollitters(Object*,Object*);
    Object* getsimulationcollitters(Object*,Object*);

    Object* addobject(Object*,Object*);
}

#endif // SIMULATION_H_INCLUDED
