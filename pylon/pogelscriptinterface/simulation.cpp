#include "simulation.h"
#include "../pogel/pogel.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* sim_new(Object* self, Object* args)
    {
        char* simname;
        int col;
        if(!PyArg_ParseTuple(args, "si:sim_new", &simname, &col))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim != NULL)
            return Py_BuildValue("i", -1);
        Renderer::Physics::addSimulation(std::string(simname), (bool)col);
        return Py_BuildValue("i", 0);
    }

    Object* sim_toggle(Object* self, Object* args)
    {
        char* simname;
        int col;
        if(!PyArg_ParseTuple(args, "si:sim_toggle", &simname, &col))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        sim->setinc((bool)col);
        return Py_BuildValue("i", 0);
    }

    Object* sim_halt(Object* self, Object* args)
    {
        char* simname;
        if(!PyArg_ParseTuple(args, "s:sim_halt", &simname))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        sim->setinc( false );
        sim->setdraw( false );
        return Py_BuildValue("i", 0);
    }

    Object* sim_visibility(Object* self, Object* args)
    {
        char* simname;
        int vis;
        if(!PyArg_ParseTuple(args, "si:sim_visibility", &simname, &vis))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        sim->setdraw( (bool)vis );
        return Py_BuildValue("i", 0);
    }

    Object* sim_weight(Object* self, Object* args)
    {
        char* simname;
        int col;
        if(!PyArg_ParseTuple(args, "si:sim_weight", &simname, &col))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
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
        return Py_BuildValue("i", 0);
    }

    Object* sim_clear(Object* self, Object* args)
    {
        char* simname;
        if(!PyArg_ParseTuple(args, "s:sim_clear", &simname))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        if(sim->RequestToClearObjects())
            return Py_BuildValue("i", 0);
        else
            return Py_BuildValue("i", -2);
    }

    Object* sim_set_gravity_3f(Object* self, Object* args)
    {
        char* simname;
        POGEL::VECTOR dir;
        if(!PyArg_ParseTuple(args, "sfff:sim_set_gravity_3f", &simname, &dir.x, &dir.y, &dir.z))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        if(sim->isdyn())
            static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->gravity = dir;
        else
            static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->gravity = dir;
        return Py_BuildValue("i", 0);
    }

    Object* sim_get_gravity_3f(Object* self, Object* args)
    {
        char* simname;
        if(!PyArg_ParseTuple(args, "s:sim_get_gravity_3f", &simname))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            Py_RETURN_NONE;
        POGEL::VECTOR grav;
        if(sim->isdyn())
            grav = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->gravity;
        else
            grav = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->gravity;
        return Py_BuildValue("[fff]", grav.x, grav.y, grav.z );
    }

    Object* sim_set_itter(Object* self, Object* args)
    {
        char* simname;
        int collitters;
        if(!PyArg_ParseTuple(args, "si:sim_set_itter", &simname, &collitters))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        if(!sim->isdyn())
            static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->setCollItters(char(collitters));
        else
            return Py_BuildValue("i", -2);
        return Py_BuildValue("i", 0);
    }

    Object* sim_get_itter(Object* self, Object* args)
    {
        char* simname;
        if(!PyArg_ParseTuple(args, "s:sim_get_itter", &simname))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            Py_RETURN_NONE;
        unsigned char collitters = 1;
        if(!sim->isdyn())
            collitters = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getCollItters();
        else
            Py_RETURN_NONE;
        return Py_BuildValue("i", int(collitters));
    }

    Object* sim_add_object_s(Object* self, Object* args)
    {
        char* data;
        char* simname;
        if(!PyArg_ParseTuple(args, "ss:sim_add_object_s", &simname, &data))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        POGEL::PHYSICS::SOLID* obj = new POGEL::PHYSICS::SOLID(std::string(data));
        if(sim->isdyn())
            static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->addSolid(obj);
        else
            static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->addSolid(obj);
        return Py_BuildValue("i", 0);
    }
}
