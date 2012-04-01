#include "subrender.h"
#include "../pogel/pogel.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* subrender_new(Object* self, Object* args)
    {
        char *name;
        float aspectratio;
        if( !PyArg_ParseTuple( args, "sf:subrender_new", &name, &aspectratio) )
        {
            return NULL;
        }
        POGEL::IMAGE* subrend = new Renderer::SubRenderer(std::string(name), aspectratio);
        POGEL::addImage(subrend);
        return Py_BuildValue("s", subrend->toString().c_str());
    }

    Object* subrender_bind_sim(Object* self, Object* args)
    {
        char *name;
        char *simname;
        if( !PyArg_ParseTuple( args, "ss:subrender_bind_sim", &name, &simname) )
        {
            return NULL;
        }
        Renderer::SubRenderer* subrend = Renderer::requestSubRenderer(std::string(name));
        if(subrend == NULL)
            return Py_BuildValue("i",-4);
        int ret = subrend->addSimulationBinding(std::string(simname));
        return Py_BuildValue("i", ret);
    }

    Object* subrender_release_sim(Object* self, Object* args)
    {
        char *name;
        char *simname;
        if( !PyArg_ParseTuple( args, "ss:subrender_release_sim", &name, &simname) )
        {
            return NULL;
        }
        Renderer::SubRenderer* subrend = Renderer::requestSubRenderer(std::string(name));
        if(subrend == NULL)
            return Py_BuildValue("i",-4);
        int ret = subrend->removeSimulationBinding(std::string(simname));
        return Py_BuildValue("i", ret);
    }

    Object* subrender_release_all(Object* self, Object* args)
    {
        char *name;
        if( !PyArg_ParseTuple( args, "s:subrender_release_all", &name) )
        {
            return NULL;
        }
        Renderer::SubRenderer* subrend = Renderer::requestSubRenderer(std::string(name));
        if(subrend == NULL)
            return Py_BuildValue("i",-4);
        int ret = subrend->removeAllSimulationBindings();
        return Py_BuildValue("i", ret);
    }

    Object* subrender_set_light(Object* self, Object* args)
    {
        char *name;
        int ltn;
        POGEL::POINT pos;
        char *amb;
        char *dif;
        char *spc;
        int op;
        if( !PyArg_ParseTuple( args, "sifffsssi:subrender_set_light", &name, &ltn, &pos.x,&pos.y,&pos.z, &amb, &dif, &spc, &op) )
        {
            return NULL;
        }
        Renderer::SubRenderer* subrend = Renderer::requestSubRenderer(std::string(name));
        if(subrend == NULL)
            return Py_BuildValue("i",-4);
        POGEL::COLOR ambient = POGEL::COLOR(std::string(amb));
        POGEL::COLOR diffuse = POGEL::COLOR(std::string(dif));
        POGEL::COLOR speculr = POGEL::COLOR(std::string(spc));
        subrend->setLight(Renderer::Lighting::Light(pos,ambient,diffuse,speculr,(bool)op),ltn);
        return Py_BuildValue("i",0);
    }

    Object* subrender_set_cam(Object* self, Object* args)
    {
        char *name;
        POGEL::POINT pos;
        POGEL::POINT rot;
        if( !PyArg_ParseTuple( args, "sffffff:subrender_set_cam", &name, &pos.x,&pos.y,&pos.z, &rot.x,&rot.y,&rot.z) )
        {
            return NULL;
        }
        Renderer::SubRenderer* subrend = Renderer::requestSubRenderer(std::string(name));
        if(subrend == NULL)
            return Py_BuildValue("i",-4);
        subrend->camera.position = pos;
        subrend->camera.rotation = rot;
        return Py_BuildValue("i",0);
    }

    Object* subrender_set_ratio(Object* self, Object* args)
    {
        char *name;
        float ratio;
        if( !PyArg_ParseTuple( args, "sf:subrender_set_ratio", &name, &ratio) )
        {
            return NULL;
        }
        Renderer::SubRenderer* subrend = Renderer::requestSubRenderer(std::string(name));
        if(subrend == NULL)
            return Py_BuildValue("i",-4);
        subrend->setaspectratio(ratio);
        return Py_BuildValue("i",0);
    }
}
