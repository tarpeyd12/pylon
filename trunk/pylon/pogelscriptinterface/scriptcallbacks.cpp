#include "scriptcallbacks.h"
#include "../pogel/pogel.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{

    CollisionFunction::CollisionFunction()
    {

    }

    CollisionFunction::CollisionFunction(std::string simname, std::string inst, std::string func)
    {
        simulationName = simname;
        std::string args[2] = { "str:", "str:" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,2);
    }

    CollisionFunction::~CollisionFunction()
    {

    }

    void CollisionFunction::operator()( POGEL::PHYSICS::SOLID * obj, const char * obj2name )
    {
        std::string args[3] = { "str:"+simulationName, "str:"+obj->getsname(), "str:"+std::string(obj2name) };
        getInstructions()->setArgs(args,3);
        this->Execute();
    }

    Object* callback_set_collfunc(Object* self, Object* args)
    {
        char* simname;
        char* objname;
        char* inst;
        char* func;
        if(!PyArg_ParseTuple(args, "ssss:callback_set_collfunc", &simname, &objname, &inst, &func))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        POGEL::PHYSICS::SOLID* obj = sim->getObject(std::string(objname));
        if(obj==NULL)
            return Py_BuildValue("i", -2);
        if(obj->callback!=NULL)
            return Py_BuildValue("i", -3);
        obj->setCallback(new CollisionFunction(std::string(simname),std::string(inst),std::string(func)));
        return Py_BuildValue("i", 0);
    }


    StepFunction::StepFunction()
    {

    }

    StepFunction::StepFunction(std::string simname, std::string inst, std::string func)
    {
        simulationName = simname;
        std::string args[2] = { "str:", "str:" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,2);
    }

    StepFunction::~StepFunction()
    {

    }

    void StepFunction::operator()( POGEL::PHYSICS::SOLID * obj )
    {
        std::string args[2] = { "str:"+simulationName, "str:"+obj->getsname() };
        getInstructions()->setArgs(args,2);
        this->Execute();
    }

    Object* callback_set_stepfunc(Object* self, Object* args)
    {
        char* simname;
        char* objname;
        char* inst;
        char* func;
        if(!PyArg_ParseTuple(args, "ssss:callback_set_stepfunc", &simname, &objname, &inst, &func))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        POGEL::PHYSICS::SOLID* obj = sim->getObject(std::string(objname));
        if(obj==NULL)
            return Py_BuildValue("i", -2);
        if(obj->function!=NULL)
            return Py_BuildValue("i", -3);
        obj->setStepFunc(new StepFunction(std::string(simname),std::string(inst),std::string(func)));
        return Py_BuildValue("i", 0);
    }

    HitFilterFunction::HitFilterFunction()
    {

    }

    HitFilterFunction::HitFilterFunction(std::string simname, std::string inst, std::string func)
    {
        simulationName = simname;
        std::string args[3] = { "str:", "str:", "str:" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,3);
    }

    HitFilterFunction::~HitFilterFunction()
    {

    }

    bool HitFilterFunction::operator()( POGEL::PHYSICS::SOLID * obj1, POGEL::PHYSICS::SOLID * obj2 )
    {
        std::string args[3] = { "str:"+simulationName, "str:"+obj1->getsname(), "str:"+obj2->getsname() };
        getInstructions()->setArgs(args,3);
        this->Execute();
        std::string result = getInstructions()->getResult();
        if( !result.compare("bool:True") ) return true;
        if( !result.compare("bool:False") ) return false;
        return true;
    }

    Object* callback_set_hitfilter(Object* self, Object* args)
    {
        char* simname;
        char* objname;
        char* inst;
        char* func;
        if(!PyArg_ParseTuple(args, "ssss:callback_set_hitfilter", &simname, &objname, &inst, &func))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        POGEL::PHYSICS::SOLID* obj = sim->getObject(std::string(objname));
        if(obj==NULL)
            return Py_BuildValue("i", -2);
        if(obj->hitfilter!=NULL)
            return Py_BuildValue("i", -3);
        obj->setHitFilter(new HitFilterFunction(std::string(simname),std::string(inst),std::string(func)));
        return Py_BuildValue("i", 0);
    }
}
