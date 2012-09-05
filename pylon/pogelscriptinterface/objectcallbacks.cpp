#include "objectcallbacks.h"
#include "../pogel/pogel.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{

    Object* object_callback_set_collfunc(Object* self, Object* args)
    {
        char* simname;
        Object* objname;
        char* inst;
        char* func;
        if(!PyArg_ParseTuple(args, "sOss:object_callback_set_collfunc", &simname, &objname, &inst, &func))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);

        POGEL::OBJECT* obj = pogelInterface::GetObject(std::string(simname),objname);
        if(obj==NULL)
            return Py_BuildValue("i", -2);
        if(obj->GetType() != POGEL_TYPE_SOLID)
            return Py_BuildValue("i", -3);
        if(((POGEL::PHYSICS::SOLID*)obj)->callback!=NULL)
            return Py_BuildValue("i", -4);

        ((POGEL::PHYSICS::SOLID*)obj)->setCallback(new CollisionFunction(std::string(simname),std::string(inst),std::string(func)));
        return Py_BuildValue("i", 0);
    }

    Object* object_callback_set_stepfunc(Object* self, Object* args)
    {
        char* simname;
        Object* objname;
        char* inst;
        char* func;
        if(!PyArg_ParseTuple(args, "sOss:object_callback_set_stepfunc", &simname, &objname, &inst, &func))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);

        POGEL::OBJECT* obj = pogelInterface::GetObject(std::string(simname),objname);
        if(obj==NULL)
            return Py_BuildValue("i", -2);
        if(obj->GetType() != POGEL_TYPE_SOLID)
            return Py_BuildValue("i", -3);
        if(((POGEL::PHYSICS::SOLID*)obj)->function!=NULL)
            return Py_BuildValue("i", -4);

        ((POGEL::PHYSICS::SOLID*)obj)->setStepFunc(new StepFunction(std::string(simname),std::string(inst),std::string(func)));
        return Py_BuildValue("i", 0);
    }

    Object* object_callback_set_hitfilter(Object* self, Object* args)
    {
        char* simname;
        Object* objname;
        char* inst;
        char* func;
        if(!PyArg_ParseTuple(args, "sOss:object_callback_set_hitfilter", &simname, &objname, &inst, &func))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);

        POGEL::OBJECT* obj = pogelInterface::GetObject(std::string(simname),objname);
        if(obj==NULL)
            return Py_BuildValue("i", -2);
        if(obj->GetType() != POGEL_TYPE_SOLID)
            return Py_BuildValue("i", -3);
        if(((POGEL::PHYSICS::SOLID*)obj)->hitfilter!=NULL)
            return Py_BuildValue("i", -4);

        ((POGEL::PHYSICS::SOLID*)obj)->setHitFilter(new HitFilterFunction(std::string(simname),std::string(inst),std::string(func)));
        return Py_BuildValue("i", 0);
    }



    CollisionFunction::CollisionFunction()
    {

    }

    CollisionFunction::CollisionFunction(std::string simname, std::string inst, std::string func)
    {
        simulationName = simname;
        std::string args[3] = { "str:", "str:", "str:" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,3);
    }

    CollisionFunction::CollisionFunction(std::string simname, std::string inst, std::string func, bool out)
    {
        simulationName = simname;
        std::string args[3] = { "str:", "str:", "str:" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,3,out);
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


    StepFunction::StepFunction()
    {

    }

    StepFunction::StepFunction(std::string simname, std::string inst, std::string func)
    {
        simulationName = simname;
        std::string args[3] = { "str:", "str:", "int:" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,3);
    }

    StepFunction::StepFunction(std::string simname, std::string inst, std::string func, bool out)
    {
        simulationName = simname;
        std::string args[3] = { "str:", "str:", "int:" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,3,out);
    }

    StepFunction::~StepFunction()
    {

    }

    void StepFunction::operator()( POGEL::PHYSICS::SOLID * obj )
    {
        char * pzstepstaken = POGEL::string("%u");
        std::string stepstaken(pzstepstaken);
        delete [] pzstepstaken;
        std::string args[3] = { "str:"+simulationName, "str:"+obj->getsname(), "int:"+stepstaken };
        getInstructions()->setArgs(args,3);
        this->Execute();
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

    HitFilterFunction::HitFilterFunction(std::string simname, std::string inst, std::string func, bool out)
    {
        simulationName = simname;
        std::string args[3] = { "str:", "str:", "str:" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,3,out);
    }

    HitFilterFunction::~HitFilterFunction()
    {

    }

    bool HitFilterFunction::operator()( POGEL::PHYSICS::SOLID * obj1, POGEL::PHYSICS::SOLID * obj2 )
    {
        if( !obj1 || !obj2 )
        {
            throw -1;
            return false;
        }
        std::string args[3] = { "str:"+simulationName, "str:"+obj1->getsname(), "str:"+obj2->getsname() };
        getInstructions()->setArgs(args,3);
        this->Execute();
        std::string result = getInstructions()->getResult();
        if( !result.compare("bool:True") ) return true;
        if( !result.compare("bool:False") ) return false;
        return true;
    }
}
