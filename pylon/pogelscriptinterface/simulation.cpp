#include "simulation.h"
#include "../pogel/pogel.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* addsimulation(Object* self, Object* args)
    {
        char* simname;
        int col;
        if(!PyArg_ParseTuple(args, "si:addsimulation", &simname, &col))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim != NULL)
            return Py_BuildValue("s", "Simulation already exists.");
        Renderer::Physics::addSimulation(std::string(simname), (bool)col);
        return Py_BuildValue("s", "Added simulation.");
    }

    Object* togglesimulation(Object* self, Object* args)
    {
        char* simname;
        int col;
        if(!PyArg_ParseTuple(args, "si:togglesimulation", &simname, &col))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation does not exists.");
        sim->setinc((bool)col);
        return Py_BuildValue("s", "Toggled simulation.");
    }

    Object* togglesimweight(Object* self, Object* args)
    {
        char* simname;
        int col;
        if(!PyArg_ParseTuple(args, "si:togglesimweight", &simname, &col))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation does not exists.");
        if(sim->isdyn())
        {
            POGEL::PHYSICS::DYNAMICS* dyn = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim());
            if(!bool(col) && !dyn->hasproperty(DYNAMICS_LIGHTWEIGHT_ONLY))
                dyn->addproperty(DYNAMICS_LIGHTWEIGHT_ONLY);
            else if(dyn->hasproperty(DYNAMICS_LIGHTWEIGHT_ONLY))
                dyn->removeproperty(DYNAMICS_LIGHTWEIGHT_ONLY);
        }
        else
        {
            POGEL::PHYSICS::SIMULATION* dyn = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim());
            if(!bool(col) && !dyn->hasproperty(DYNAMICS_LIGHTWEIGHT_ONLY))
                dyn->addproperty(SIMULATION_LIGHTWEIGHT_ONLY);
            else if(dyn->hasproperty(DYNAMICS_LIGHTWEIGHT_ONLY))
                dyn->removeproperty(SIMULATION_LIGHTWEIGHT_ONLY);
        }
        return Py_BuildValue("s", (std::string("Toggled simulation weight: ")+std::string(!bool(col)?"Off ":"On ")+std::string(simname)).c_str() );
    }

    Object* clearsimulation(Object* self, Object* args)
    {
        char* simname;
        if(!PyArg_ParseTuple(args, "s:clearsimulation", &simname))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation does not exists.");
        if(sim->isdyn())
            static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->clearAllSolids();
        else
            static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->clearAllSolids();
        return Py_BuildValue("s", "Cleared simulation.");
    }

    Object* setsimulationgravity_3f(Object* self, Object* args)
    {
        char* simname;
        POGEL::VECTOR dir;
        if(!PyArg_ParseTuple(args, "sfff:setsimulationgravity_3f", &simname, &dir.x, &dir.y, &dir.z))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation does not exists.");
        if(sim->isdyn())
            static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->gravity = dir;
        else
            static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->gravity = dir;
        return Py_BuildValue("s", "set simulation gravity.");
    }

    Object* setsimulationcollitters(Object* self, Object* args)
    {
        char* simname;
        int collitters;
        if(!PyArg_ParseTuple(args, "si:setsimulationcollitters", &simname, &collitters))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation does not exists.");
        if(!sim->isdyn())
            static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->setCollItters(char(collitters));
        else
            return Py_BuildValue("s", "Cannot set simulation collision itterations, wrong type of simulation.");
        return Py_BuildValue("s", "Set simulation collision itterations.");
    }

    Object* getsimulationcollitters(Object* self, Object* args)
    {
        char* simname;
        if(!PyArg_ParseTuple(args, "s:getsimulationcollitters", &simname))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation does not exists.");
        unsigned char collitters = 1;
        if(!sim->isdyn())
            collitters = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getCollItters();
        else
            return Py_BuildValue("s", "Cannot get simulation collision itterations, wrong type of simulation.");
        return Py_BuildValue("i", int(collitters));
    }

    Object* addobject(Object* self, Object* args)
    {
        char* data;
        char* simname;
        if(!PyArg_ParseTuple(args, "ss:addobject", &simname, &data))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        POGEL::PHYSICS::SOLID* obj = new POGEL::PHYSICS::SOLID(std::string(data));
        if(sim->isdyn())
            static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->addSolid(obj);
        else
            static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->addSolid(obj);
        return Py_BuildValue("s", std::string("Added object: "+obj->getsname()).c_str());
    }
}
