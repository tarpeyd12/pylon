#ifndef SCRIPTCALLBACKS_H_INCLUDED
#define SCRIPTCALLBACKS_H_INCLUDED

#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#include "pogelscriptinterface.h"
#endif // POGELSCRIPTINTERFACE_H_INCLUDED

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    class CollisionFunction : public SOLID_CALLBACK, public ScriptEngine::InterpreterThread
    {
        private:
            std::string simulationName;
        public:
            CollisionFunction();
            CollisionFunction(std::string,std::string,std::string);
            CollisionFunction(std::string,std::string,std::string,bool);
            ~CollisionFunction();
            void operator()( POGEL::PHYSICS::SOLID *, const char * );
    };

    Object* callback_set_collfunc(Object*,Object*);
    Object* callback_set_collfunc_s(Object*,Object*);

    class StepFunction : public SOLID_FUNCTION, public ScriptEngine::InterpreterThread
    {
        private:
            std::string simulationName;
        public:
            StepFunction();
            StepFunction(std::string,std::string,std::string);
            StepFunction(std::string,std::string,std::string,bool);
            ~StepFunction();
            void operator()( POGEL::PHYSICS::SOLID * );
    };

    Object* callback_set_stepfunc(Object*,Object*);
    Object* callback_set_stepfunc_s(Object*,Object*);

    class HitFilterFunction : public SOLID_HITFILTER, public ScriptEngine::InterpreterThread
    {
        private:
            std::string simulationName;
        public:
            HitFilterFunction();
            HitFilterFunction(std::string,std::string,std::string);
            HitFilterFunction(std::string,std::string,std::string,bool);
            ~HitFilterFunction();
            bool operator()( POGEL::PHYSICS::SOLID *, POGEL::PHYSICS::SOLID * );
    };

    Object* callback_set_hitfilter(Object*,Object*);
    Object* callback_set_hitfilter_s(Object*,Object*);
}

#endif // SCRIPTCALLBACKS_H_INCLUDED
