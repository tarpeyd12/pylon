#ifndef OBJECTCALLBACKS_H_INCLUDED
#define OBJECTCALLBACKS_H_INCLUDED

#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#include "pogelscriptinterface.h"
#endif // POGELSCRIPTINTERFACE_H_INCLUDED

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* object_callback_set_collfunc(Object*,Object*);
    Object* object_callback_set_stepfunc(Object*,Object*);
    Object* object_callback_set_hitfilter(Object*,Object*);

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
}

#endif // OBJECTCALLBACKS_H_INCLUDED
