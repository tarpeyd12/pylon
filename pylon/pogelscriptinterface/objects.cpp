#include "objects.h"
#include "../pogel/pogel.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* object_new(Object* self, Object* args)
    {
        char* simname;
        char* objname;
        if(!PyArg_ParseTuple(args, "ss:object_new", &simname, &objname))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        char *nm = new char[strlen(objname)];
        POGEL::PHYSICS::SOLID* obj = new POGEL::PHYSICS::SOLID(strcpy(nm,objname));
        if(sim->isdyn())
            static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->addSolid(obj);
        else
            static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->addSolid(obj);
        return Py_BuildValue("i", 0);
    }

    Object* object_set_visibility(Object* self, Object* args)
    {
        char* name;
        char* simname;
        int visable;
        if(!PyArg_ParseTuple(args, "ssi:object_set_visibility", &simname, &name, &visable))
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        obj->visable = bool(visable);
        return Py_BuildValue("i", 0);
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
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
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->spin = POGEL::VECTOR(std::string(newdir));
        return Py_BuildValue("s", obj->spin.toString().c_str());
    }

    Object* object_options(Object* self, Object* args)
    {
        char* name;
        char* simname;
        char* inst;
        int prop;
        if( !PyArg_ParseTuple( args, "sssi:object_options", &simname, &name, &inst, &prop) )
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        std::string instructions(inst);
        if(!instructions.length())
            return Py_BuildValue("i", -3);
        int ret = 0;
        if( !instructions.compare("get options") || !instructions.compare("get option") )
        {
            ret = (int)obj->getOptions();
        }
        else
        if( !instructions.compare("set options") || !instructions.compare("set option") )
        {
            obj->setOptions((unsigned int)prop);
            ret = (int)obj->getOptions();
        }
        else
        if( !instructions.compare("add options") || !instructions.compare("add option") )
        {
            obj->addOption((unsigned int)prop);
            ret = (int)obj->getOptions();
        }
        else
        if(
           !instructions.compare("remove options") || !instructions.compare("remove option") ||
           !instructions.compare("rm options")  || !instructions.compare("rm option")
        )
        {
            obj->removeOption((unsigned int)prop);
            ret = (int)obj->getOptions();
        }
        else
        if( !instructions.compare("has options") || !instructions.compare("has option") )
        {
            ret = (int)obj->hasOption((unsigned int)prop);
        }
        // **********************************
        if( !instructions.compare("get properties") || !instructions.compare("get property") )
        {
            ret = (int)obj->getproperties();
        }
        else
        if( !instructions.compare("set properties") || !instructions.compare("set property") )
        {
            obj->setproperties((unsigned int)prop);
            ret = (int)obj->getproperties();
        }
        else
        if( !instructions.compare("add properties") || !instructions.compare("add property") )
        {
            obj->addproperty((unsigned int)prop);
            ret = (int)obj->getproperties();
        }
        else
        if(
           !instructions.compare("remove properties") || !instructions.compare("remove property") ||
           !instructions.compare("rm properties")  || !instructions.compare("rm property")
        )
        {
            obj->removeproperty((unsigned int)prop);
            ret = (int)obj->getproperties();
        }
        else
        if( !instructions.compare("has properties") || !instructions.compare("has property") )
        {
            ret = (int)obj->hasproperty((unsigned int)prop);
        }
        else
            { }
        return Py_BuildValue("i", ret);
    }

    Object* object_set_mass(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float property;
        if( !PyArg_ParseTuple( args, "ssf:object_set_mass", &simname, &name, &property) )
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        obj->behavior.mass = property;
        return Py_BuildValue("i", 0);
    }

    Object* object_get_mass(Object* self, Object* args)
    {
        char* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "ss:object_get_mass", &simname, &name) )
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            throw -1;
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            throw -2;
        return Py_BuildValue("f", obj->behavior.mass);
    }

    Object* object_set_bounce(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float property;
        if( !PyArg_ParseTuple( args, "ssf:object_set_bounce", &simname, &name, &property) )
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        obj->behavior.bounce = property;
        return Py_BuildValue("i", 0);
    }

    Object* object_get_bounce(Object* self, Object* args)
    {
        char* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "ss:object_get_bounce", &simname, &name) )
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            throw -1;
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            throw -2;
        return Py_BuildValue("f", obj->behavior.bounce);
    }

    Object* object_set_friction(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float property;
        if( !PyArg_ParseTuple( args, "ssf:object_set_friction", &simname, &name, &property) )
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        obj->behavior.friction = property;
        return Py_BuildValue("i", 0);
    }

    Object* object_get_friction(Object* self, Object* args)
    {
        char* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "ss:object_get_friction", &simname, &name) )
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            throw -1;
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            throw -2;
        return Py_BuildValue("f", obj->behavior.friction);
    }

    Object* object_build(Object* self, Object* args)
    {
        char* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "ss:object_build", &simname, &name) )
            return NULL;
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        obj->build();
        return Py_BuildValue("s", "built object.");
    }
}
