#include "objects.h"
#include "../pogel/pogel.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* object_new(Object* self, Object* args)
    {
        char* simname;
        Object* objname;
        if(!PyArg_ParseTuple(args, "sO:object_new", &simname, &objname))
            return NULL;
        Renderer::Physics::Simulation * sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("i", -1);
        //char *nm = new char[strlen(objname)];
        //POGEL::PHYSICS::SOLID* obj = new POGEL::PHYSICS::SOLID(strcpy(nm,objname));
        Py_XINCREF(objname);
        POGEL::PHYSICS::SOLID* obj = new POGEL::PHYSICS::SOLID((char*)pogelInterface::GetObjectName(objname).c_str());
        Py_XDECREF(objname);
        if(sim->isdyn())
            static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->addSolid(obj);
        else
            static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->addSolid(obj);
        //delete nm;
        return Py_BuildValue("i", 0);
    }

    Object* object_new_fromfile(Object* self, Object* args)
    {
        char* simname;
        Object* objname;
        char* filename;
        char* filetype;
        if(!PyArg_ParseTuple(args, "sOss:object_new_fromfile", &simname, &objname, &filename, &filetype))
            return NULL;
        Py_XINCREF(objname);
        POGEL::OBJECT * oobj = pogelInterface::GetObject( std::string(simname), objname );
         if( oobj != NULL && oobj->GetType() != POGEL_TYPE_SOLID)
        {
            Py_XDECREF(objname);
            return Py_BuildValue("i", -1);
        }
        POGEL::PHYSICS::SOLID * obj = (POGEL::PHYSICS::SOLID*)oobj;
        char* objname2 = (char*)pogelInterface::GetObjectName(objname).c_str();
        Py_XDECREF(objname);
        char *nm = strcpy(new char[strlen(objname2)],objname2);
        if(!obj)
        {
            Renderer::Physics::Simulation * sim = NULL;
            sim = Renderer::Physics::getSimulation(std::string(simname));
            if( sim == NULL )
            {
                //delete [] nm;
                return Py_BuildValue("i", -3);
            }
            obj = new POGEL::PHYSICS::SOLID(nm);
            if(sim->isdyn())
                static_cast<POGEL::PHYSICS::DYNAMICS*>(sim->getSim())->addSolid(obj);
            else
                static_cast<POGEL::PHYSICS::SIMULATION*>(sim->getSim())->addSolid(obj);
        }
        POGEL::OBJECT * animobj = ObjectLoader::newFromFile( filename, filetype, nm, obj, std::string(simname) );
        //delete [] nm;
        if( animobj == NULL)
            return Py_BuildValue("i", -2);
        return Py_BuildValue("i", 0);
    }

    Object* object_new_child(Object* self, Object* args)
    {
        char* simname;
        char* objname;
        char* decendant;
        char* childname;
        if(!PyArg_ParseTuple(args, "ssss:object_new_child", &simname, &objname, &decendant, &childname))
            return NULL;
        Renderer::Physics::Simulation * sim = NULL;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if( sim == NULL )
            return Py_BuildValue("i", -1);
        POGEL::PHYSICS::SOLID * obj = NULL;
        obj = sim->getObject(std::string(objname));
        if( obj == NULL )
            return Py_BuildValue("i", -2);
        POGEL::OBJECT * dec = NULL;
        dec = obj->getdecendant(decendant);
        if( dec == NULL )
            return Py_BuildValue("i", -3);
        POGEL::OBJECT * child = NULL;
        child = new POGEL::OBJECT( strcpy(new char[strlen(childname)],childname) );
        dec->addobject( child );
        return Py_BuildValue("i", 0);
    }

    Object* object_get_type_s(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_type_s", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found");

        switch( obj->GetType() )
        {
            case POGEL_TYPE_OBJECT: return Py_BuildValue("s", "Object");
            case POGEL_TYPE_SPRITE: return Py_BuildValue("s", "Sprite");
            case POGEL_TYPE_FRACTAL: return Py_BuildValue("s", "Fractal");
            case POGEL_TYPE_SOLID: return Py_BuildValue("s", "Solid");
            case POGEL_TYPE_FOUNTAIN: return Py_BuildValue("s", "Fountain");
            case POGEL_TYPE_MICROCOSOM: return Py_BuildValue("s", "Microcosm");
        }
        return Py_BuildValue("s", "Unknown");
    }

    Object* object_get_type_i(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_type_i", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -1);
        return Py_BuildValue("i", obj->GetType());
    }

    Object* object_check(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_check", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", int(false));
        return Py_BuildValue("i", int(true));
    }

    Object* object_set_visibility(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        int visable;
        if(!PyArg_ParseTuple(args, "sOi:object_set_visibility", &simname, &name, &visable))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);

        obj->visable = bool(visable);
        return Py_BuildValue("i", 0);
    }

    Object* object_get_visibility(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_visibility", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;

        return Py_BuildValue("i", int(obj->visable));
    }

    Object* object_move_s(Object* self, Object* args)
    {
        Object* name;
        char* newpos;
        char* simname;
        if(!PyArg_ParseTuple(args, "sOs:object_move_s", &simname, &name, &newpos))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        obj->position = POGEL::POINT(std::string(newpos));
        return Py_BuildValue("s", obj->position.toString().c_str());
    }

    Object* object_move_3f(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        POGEL::POINT newpos;
        if(!PyArg_ParseTuple(args, "sOfff:object_move_3f", &simname, &name, &newpos.x, &newpos.y, &newpos.z))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        obj->position = newpos;
        return Py_BuildValue("s", obj->position.toString().c_str());
    }

    Object* object_set_dir_3f(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        POGEL::VECTOR newdir;
        if(!PyArg_ParseTuple(args, "sOfff:object_set_dir_3f", &simname, &name, &newdir.x, &newdir.y, &newdir.z))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        obj->direction = newdir;
        return Py_BuildValue("s", obj->direction.toString().c_str());
    }

    Object* object_set_pos_3f(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        POGEL::POINT newdir;
        if(!PyArg_ParseTuple(args, "sOfff:object_set_pos_3f", &simname, &name, &newdir.x, &newdir.y, &newdir.z))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        obj->position = newdir;
        return Py_BuildValue("s", obj->position.toString().c_str());
    }

    Object* object_set_rot_3f(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        POGEL::POINT newdir;
        if(!PyArg_ParseTuple(args, "sOfff:object_set_rot_3f", &simname, &name, &newdir.x, &newdir.y, &newdir.z))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        obj->rotation = newdir;
        return Py_BuildValue("s", obj->rotation.toString().c_str());
    }

    Object* object_set_spin_3f(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        POGEL::VECTOR newdir;
        if(!PyArg_ParseTuple(args, "sOfff:object_set_spin_3f", &simname, &name, &newdir.x, &newdir.y, &newdir.z))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        obj->spin = newdir;
        return Py_BuildValue("s", obj->spin.toString().c_str());
    }

    Object* object_get_dir_3f(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_dir_3f", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("[fff]", obj->direction.x, obj->direction.y, obj->direction.z);
    }

    Object* object_get_pos_3f(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_pos_3f", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("[fff]", obj->position.x, obj->position.y, obj->position.z);
    }

    Object* object_get_rot_3f(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_rot_3f", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("[fff]", obj->rotation.x, obj->rotation.y, obj->rotation.z);
    }

    Object* object_get_spin_3f(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_spin_3f", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("[fff]", obj->spin.x, obj->spin.y, obj->spin.z);
    }

    Object* object_get_dir_s(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_dir_s", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("s", obj->direction.toString().c_str());
    }

    Object* object_get_pos_s(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_pos_s", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("s", obj->position.toString().c_str());
    }

    Object* object_get_rot_s(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_rot_s", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("s", obj->rotation.toString().c_str());
    }

    Object* object_get_spin_s(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if(!PyArg_ParseTuple(args, "sO:object_get_spin_s", &simname, &name))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("s", obj->spin.toString().c_str());
    }

    Object* object_set_dir_s(Object* self, Object* args)
    {
        Object* name;
        char* newdir;
        char* simname;
        if(!PyArg_ParseTuple(args, "sOs:object_set_dir_s", &simname, &name, &newdir))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        obj->direction = POGEL::VECTOR(std::string(newdir));
        return Py_BuildValue("i", 0);
    }

    Object* object_set_pos_s(Object* self, Object* args)
    {
        Object* name;
        char* newdir;
        char* simname;
        if(!PyArg_ParseTuple(args, "sOs:object_set_pos_s", &simname, &name, &newdir))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        obj->position = POGEL::POINT(std::string(newdir));
        return Py_BuildValue("i", 0);
    }

    Object* object_set_rot_s(Object* self, Object* args)
    {
        Object* name;
        char* newdir;
        char* simname;
        if(!PyArg_ParseTuple(args, "sOs:object_set_rot_s", &simname, &name, &newdir))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        obj->rotation = POGEL::POINT(std::string(newdir));
        return Py_BuildValue("i", 0);
    }

    Object* object_set_spin_s(Object* self, Object* args)
    {
        Object* name;
        char* newdir;
        char* simname;
        if(!PyArg_ParseTuple(args, "sOs:object_set_spin_s", &simname, &name, &newdir))
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        obj->spin = POGEL::VECTOR(std::string(newdir));
        return Py_BuildValue("i", 0);
    }

    Object* object_options(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        char* inst;
        int prop;
        if( !PyArg_ParseTuple( args, "sOsi:object_options", &simname, &name, &inst, &prop) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        std::string instructions(inst);
        if(!instructions.length())
            return Py_BuildValue("i", -3);
        int ret = 0;
        if( obj->GetType() == POGEL_TYPE_SOLID )
        {
            if( !instructions.compare("get options") || !instructions.compare("get option") )
            {
                ret = (int)((POGEL::PHYSICS::SOLID*)obj)->getOptions();
            }
            else
            if( !instructions.compare("set options") || !instructions.compare("set option") )
            {
                ((POGEL::PHYSICS::SOLID*)obj)->setOptions((unsigned int)prop);
                ret = (int)((POGEL::PHYSICS::SOLID*)obj)->getOptions();
            }
            else
            if( !instructions.compare("add options") || !instructions.compare("add option") )
            {
                ((POGEL::PHYSICS::SOLID*)obj)->addOption((unsigned int)prop);
                ret = (int)((POGEL::PHYSICS::SOLID*)obj)->getOptions();
            }
            else
            if(
               !instructions.compare("remove options") || !instructions.compare("remove option") ||
               !instructions.compare("rm options")  || !instructions.compare("rm option")
            )
            {
                ((POGEL::PHYSICS::SOLID*)obj)->removeOption((unsigned int)prop);
                ret = (int)((POGEL::PHYSICS::SOLID*)obj)->getOptions();
            }
            else
            if( !instructions.compare("has options") || !instructions.compare("has option") )
            {
                ret = (int)((POGEL::PHYSICS::SOLID*)obj)->hasOption((unsigned int)prop);
            }
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
        Object* name;
        char* simname;
        float property;
        if( !PyArg_ParseTuple( args, "sOf:object_set_mass", &simname, &name, &property) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if( obj->GetType() != POGEL_TYPE_SOLID )
            return Py_BuildValue("i", -1);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        ((POGEL::PHYSICS::SOLID*)obj)->behavior.mass = property;
        return Py_BuildValue("i", 0);
    }

    Object* object_get_mass(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "sO:object_get_mass", &simname, &name) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL || obj->GetType() != POGEL_TYPE_SOLID)
            Py_RETURN_NONE;
        return Py_BuildValue("f", ((POGEL::PHYSICS::SOLID*)obj)->behavior.mass);
    }

    Object* object_set_bounce(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float property;
        if( !PyArg_ParseTuple( args, "sOf:object_set_bounce", &simname, &name, &property) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if( obj->GetType() != POGEL_TYPE_SOLID )
            return Py_BuildValue("i", -1);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        ((POGEL::PHYSICS::SOLID*)obj)->behavior.bounce = property;
        return Py_BuildValue("i", 0);
    }

    Object* object_get_bounce(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "sO:object_get_bounce", &simname, &name) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL || obj->GetType() != POGEL_TYPE_SOLID)
            Py_RETURN_NONE;
        return Py_BuildValue("f", ((POGEL::PHYSICS::SOLID*)obj)->behavior.bounce);
    }

    Object* object_set_friction(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float property;
        if( !PyArg_ParseTuple( args, "sOf:object_set_friction", &simname, &name, &property) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if( obj->GetType() != POGEL_TYPE_SOLID )
            return Py_BuildValue("i", -1);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        ((POGEL::PHYSICS::SOLID*)obj)->behavior.friction = property;
        return Py_BuildValue("i", 0);
    }

    Object* object_get_friction(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "sO:object_get_friction", &simname, &name) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL || obj->GetType() != POGEL_TYPE_SOLID)
            Py_RETURN_NONE;
        return Py_BuildValue("f", ((POGEL::PHYSICS::SOLID*)obj)->behavior.friction);
    }

    Object* object_get_steps(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "sO:object_get_steps", &simname, &name) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL || obj->GetType() != POGEL_TYPE_SOLID)
            Py_RETURN_NONE;
        return Py_BuildValue("i", (int)((POGEL::PHYSICS::SOLID*)obj)->getstepstaken());
    }

    Object* object_add_key(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        char* keytype;
        POGEL::KEY key;
        if( !PyArg_ParseTuple( args, "sOsffff:object_add_key", &simname, &name, &keytype, &key.x, &key.y, &key.z, &key.time) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        std::string skeytype(keytype);
        if( !skeytype.length() )
        {
            return Py_BuildValue("i", -3);
        }
        else if( !skeytype.compare("pos") )
        {
            obj->addPosKey(key);
        }
        else if( !skeytype.compare("rot") )
        {
            obj->addRotKey(key);
        }
        else if( !skeytype.compare("scale") )
        {
            obj->addScaleKey(key);
        }
        else
        {
            return Py_BuildValue("i", -4);
        }
        return Py_BuildValue("i", 0);
    }

    Object* object_add_animation(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float start;
        float stop;
        char* animname;
        if( !PyArg_ParseTuple( args, "sOffs:object_add_animation", &simname, &name, &start, &stop, &animname) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        int ret = obj->addAnimationLoop( POGEL::ANIMATIONLOOP(start,stop,std::string(animname)), "");
        return Py_BuildValue("i", ret);
    }

    Object* object_set_animation(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        char* animname;
        if( !PyArg_ParseTuple( args, "sOs:object_set_animation", &simname, &name, &animname) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        int ret = obj->setAnimationLoop( std::string(animname) );
        return Py_BuildValue("i", ret);
    }

    Object* object_get_animation(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "sO:object_get_animation", &simname, &name) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("s", obj->getCurrentAnimation().c_str());
    }


    Object* object_has_animation(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        char* animname;
        if( !PyArg_ParseTuple( args, "sOs:object_has_animation", &simname, &name, &animname) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        if( obj->hasAnimationLoop( std::string(animname) ) )
        {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    Object* object_set_animtime(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "sO:object_set_animtime", &simname, &name) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        obj->setAnimationLoopStartTime( POGEL::GetTimePassed() );
        return Py_BuildValue("i", 0);
    }

    Object* object_get_animlen(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        char* animname;
        if( !PyArg_ParseTuple( args, "sOs:object_get_animlen", &simname, &name, &animname) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("f", obj->getAnimationLength(std::string(animname)));
    }

    Object* object_get_animsince(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "sO:object_get_animsince", &simname, &name) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_RETURN_NONE;
        return Py_BuildValue("f", obj->getTimeSinceAnimationStart());
    }

    Object* object_build(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        if( !PyArg_ParseTuple( args, "sO:object_build", &simname, &name) )
            return NULL;
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("i", -2);
        obj->getprogenitor()->build();
        //obj->build();
        return Py_BuildValue("i", 0);
    }
}
