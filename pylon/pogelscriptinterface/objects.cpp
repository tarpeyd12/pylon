#include "objects.h"
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
        Renderer::Physics::addSimulation(simname, (bool)col);
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
        //obj->build();
        if(sim->isdyn())
            static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->addSolid(obj);
        else
            static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->addSolid(obj);
        return Py_BuildValue("s", "added object.");
    }

    Object* object_move_s(Object* self, Object* args)
    {
        char* name;
        char* newpos;
        char* simname;
        if(!PyArg_ParseTuple(args, "sss:object_move_s", &simname, &name, &newpos))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->position = POGEL::POINT(std::string(newpos));
        return Py_BuildValue("s", obj->position.toString().c_str());
    }

    Object* object_move_3f(Object* self, Object* args)
    {
        char* name;
        char* simname;
        POGEL::POINT newpos;
        if(!PyArg_ParseTuple(args, "ssfff:object_move_3f", &simname, &name, &newpos.x, &newpos.y, &newpos.z))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->position = newpos;
        return Py_BuildValue("s", obj->position.toString().c_str());
    }

    Object* object_set_dir_3f(Object* self, Object* args)
    {
        char* name;
        char* simname;
        POGEL::VECTOR newdir;
        if(!PyArg_ParseTuple(args, "ssfff:object_set_dir_3f", &simname, &name, &newdir.x, &newdir.y, &newdir.z))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->direction = newdir;
        return Py_BuildValue("s", obj->direction.toString().c_str());
    }

    Object* object_set_pos_3f(Object* self, Object* args)
    {
        char* name;
        char* simname;
        POGEL::POINT newdir;
        if(!PyArg_ParseTuple(args, "ssfff:object_set_pos_3f", &simname, &name, &newdir.x, &newdir.y, &newdir.z))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->position = newdir;
        return Py_BuildValue("s", obj->position.toString().c_str());
    }

    Object* object_set_rot_3f(Object* self, Object* args)
    {
        char* name;
        char* simname;
        POGEL::POINT newdir;
        if(!PyArg_ParseTuple(args, "ssfff:object_set_rot_3f", &simname, &name, &newdir.x, &newdir.y, &newdir.z))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->rotation = newdir;
        return Py_BuildValue("s", obj->rotation.toString().c_str());
    }

    Object* object_set_spin_3f(Object* self, Object* args)
    {
        char* name;
        char* simname;
        POGEL::VECTOR newdir;
        if(!PyArg_ParseTuple(args, "ssfff:object_set_spin_3f", &simname, &name, &newdir.x, &newdir.y, &newdir.z))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->spin = newdir;
        return Py_BuildValue("s", obj->spin.toString().c_str());
    }

    Object* object_get_dir_s(Object* self, Object* args)
    {
        char* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "ss:object_get_dir_s", &simname, &name))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        return Py_BuildValue("s", obj->direction.toString().c_str());
    }

    Object* object_get_pos_s(Object* self, Object* args)
    {
        char* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "ss:object_get_pos_s", &simname, &name))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        return Py_BuildValue("s", obj->position.toString().c_str());
    }

    Object* object_get_rot_s(Object* self, Object* args)
    {
        char* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "ss:object_get_rot_s", &simname, &name))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        return Py_BuildValue("s", obj->rotation.toString().c_str());
    }

    Object* object_get_spin_s(Object* self, Object* args)
    {
        char* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "ss:object_get_spin_s", &simname, &name))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        return Py_BuildValue("s", obj->spin.toString().c_str());
    }

    Object* object_set_dir_s(Object* self, Object* args)
    {
        char* name;
        char* newdir;
        char* simname;
        if(!PyArg_ParseTuple(args, "sss:object_set_dir_s", &simname, &name, &newdir))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->direction = POGEL::VECTOR(std::string(newdir));
        return Py_BuildValue("s", obj->direction.toString().c_str());
    }

    Object* object_set_pos_s(Object* self, Object* args)
    {
        char* name;
        char* newdir;
        char* simname;
        if(!PyArg_ParseTuple(args, "sss:object_set_pos_s", &simname, &name, &newdir))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->position = POGEL::POINT(std::string(newdir));
        return Py_BuildValue("s", obj->position.toString().c_str());
    }

    Object* object_set_rot_s(Object* self, Object* args)
    {
        char* name;
        char* newdir;
        char* simname;
        if(!PyArg_ParseTuple(args, "sss:object_set_rot_s", &simname, &name, &newdir))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->rotation = POGEL::POINT(std::string(newdir));
        return Py_BuildValue("s", obj->rotation.toString().c_str());
    }

    Object* object_set_spin_s(Object* self, Object* args)
    {
        char* name;
        char* newdir;
        char* simname;
        if(!PyArg_ParseTuple(args, "sss:object_set_spin_s", &simname, &name, &newdir))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->spin = POGEL::VECTOR(std::string(newdir));
        return Py_BuildValue("s", obj->spin.toString().c_str());
    }
}