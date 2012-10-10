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
        Py_XINCREF(objname);
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
        {
            Py_XDECREF(objname);
            return Py_BuildValue("i", -1);
        }

        POGEL::OBJECT* objo = pogelInterface::GetObject(std::string(simname),objname);
        Py_XDECREF(objname);
        if(objo==NULL)
            return Py_BuildValue("i", -2);
        if(objo->GetType() != POGEL_TYPE_SOLID)
            return Py_BuildValue("i", -3);
        POGEL::PHYSICS::SOLID* obj = (POGEL::PHYSICS::SOLID*)objo;
        if(obj->callback!=NULL)
            return Py_BuildValue("i", -4);

        obj->setCallback(new CollisionFunction(std::string(simname),std::string(inst),std::string(func)));
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
        Py_XINCREF(objname);
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
        {
            Py_XDECREF(objname);
            return Py_BuildValue("i", -1);
        }

        POGEL::OBJECT* objo = pogelInterface::GetObject(std::string(simname),objname);
        Py_XDECREF(objname);
        if(objo==NULL)
            return Py_BuildValue("i", -2);
        if(objo->GetType() != POGEL_TYPE_SOLID)
            return Py_BuildValue("i", -3);
        POGEL::PHYSICS::SOLID* obj = (POGEL::PHYSICS::SOLID*)objo;
        if(obj->function!=NULL)
            return Py_BuildValue("i", -4);

        obj->setStepFunc(new StepFunction(std::string(simname),std::string(inst),std::string(func)));
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
        Py_XINCREF(objname);
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);

        POGEL::OBJECT* objo = pogelInterface::GetObject(std::string(simname),objname);
        Py_XDECREF(objname);
        if(objo==NULL)
            return Py_BuildValue("i", -2);
        if(objo->GetType() != POGEL_TYPE_SOLID)
            return Py_BuildValue("i", -3);
        POGEL::PHYSICS::SOLID* obj = (POGEL::PHYSICS::SOLID*)objo;
        if(obj->hitfilter!=NULL)
            return Py_BuildValue("i", -4);

        obj->setHitFilter(new HitFilterFunction(std::string(simname),std::string(inst),std::string(func)));
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
        /*std::string args[3] = { "str:"+simulationName, "str:"+obj->getsname(), "str:"+std::string(obj2name) };
        getInstructions()->setArgs(args,3);*/
        ScriptEngine::Executor * inst = getInstructions();
        if( !inst )
            ThrowError(-3);
        ScriptEngine::InterpreterThread::GetLock();
        inst->setArg( Py_BuildValue("s",simulationName.c_str()), 0 );
        inst->setArg( Py_BuildValue("s",obj->getname()), 1 );
        inst->setArg( Py_BuildValue("s",obj2name), 2 );
        ScriptEngine::InterpreterThread::ReleaseLock();
        this->Execute();
    }


    StepFunction::StepFunction()
    {

    }

    StepFunction::StepFunction(std::string simname, std::string inst, std::string func)
    {
        simulationName = simname;
        std::string args[3] = { "str:"+simulationName, "str:0", "int:-1" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,3);
    }

    StepFunction::StepFunction(std::string simname, std::string inst, std::string func, bool out)
    {
        simulationName = simname;
        std::string args[3] = { "str:"+simulationName, "str:0", "int:-1" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,3,out);
    }

    StepFunction::~StepFunction()
    {

    }

    void StepFunction::operator()( POGEL::PHYSICS::SOLID * obj )
    {
        /*char * pzstepstaken = POGEL::string("%u", obj->getstepstaken());
        std::string stepstaken(pzstepstaken);
        delete [] pzstepstaken;
        std::string args[3] = { "str:"+simulationName, "str:"+obj->getsname(), "int:"+stepstaken };
        getInstructions()->setArgs(args,3);*/
        ScriptEngine::Executor * inst = getInstructions();
        if( !inst )
            ThrowError(-3);
        ScriptEngine::InterpreterThread::GetLock();
        inst->setArg( Py_BuildValue("s",simulationName.c_str()), 0 );
        inst->setArg( Py_BuildValue("s",obj->getname()), 1 );
        inst->setArg( Py_BuildValue("i",obj->getstepstaken()), 2 );
        ScriptEngine::InterpreterThread::ReleaseLock();
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
            ThrowError(-1);
            return false;
        }
        /*std::string args[3] = { "str:"+simulationName, "str:"+obj1->getsname(), "str:"+obj2->getsname() };
        getInstructions()->setArgs(args,3);*/
        ScriptEngine::Executor * inst = getInstructions();
        if( !inst )
        {
            ThrowError(-2);
            return false;
        }
        ScriptEngine::InterpreterThread::GetLock();
        const char * simname = simulationName.c_str();
        inst->setArg( Py_BuildValue("s",simname), 0 );
        inst->setArg( Py_BuildValue("s",obj1->getname()), 1 );
        inst->setArg( Py_BuildValue("s",obj2->getname()), 2 );
        ScriptEngine::InterpreterThread::ReleaseLock();
        this->Execute();

        char resval = inst->getResult().at(5);
        if( resval == 'T' ) return true;
        if( resval == 'F' ) return false;
        ThrowError(-3);
        return true;
    }
}
