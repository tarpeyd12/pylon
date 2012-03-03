#ifndef SCRIPT_HUD_H_INCLUDED
#define SCRIPT_HUD_H_INCLUDED

#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#include "pogelscriptinterface.h"
#endif // POGELSCRIPTINTERFACE_H_INCLUDED

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* addquadi(Object*,Object*);
    Object* addquadf(Object*,Object*);
    Object* updatequadi(Object*,Object*);
    Object* updatequadf(Object*,Object*);
    Object* removequad(Object*,Object*);
    Object* clearquads(Object*,Object*);
    Object* maxquads(Object*,Object*);
    Object* checkquad(Object*,Object*);
}

#endif // SCRIPT_HUD_H_INCLUDED
