#include "shapes.h"
#include "../pogel/pogel.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* object_add_sphere(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float radius;
        float hdiv, wdiv;
        float hsc=1.0, wsc=1.0;
        char* img;
        int triprop;
        if( !PyArg_ParseTuple( args, "ssfffsffi:object_add_sphere",
                &simname, &name,
                &radius, &wdiv, &hdiv,
                &img, &wsc, &hsc, &triprop) )
        {
            return NULL;
        }
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        addSphere(obj, wdiv, hdiv, radius, image, wsc, hsc, (unsigned int)triprop);
        return Py_BuildValue("s", "Added sphere to object.");
    }

    Object* object_add_sphere_mat(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float radius;
        float hdiv, wdiv;
        float hsc=1.0, wsc=1.0;
        char* img;
        int triprop;
        float px,py,pz, rx,ry,rz;
        if( !PyArg_ParseTuple( args, "ssfffsffiffffff:object_add_sphere_mat",
                &simname, &name,
                &radius, &wdiv, &hdiv,
                &img, &wsc, &hsc, &triprop,
                &px,&py,&pz, &rx,&ry,&rz) )
        {
            return NULL;
        }
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        POGEL::MATRIX mat(POGEL::POINT(px,py,pz),POGEL::POINT(rx,ry,rz));
        addSphere(obj, wdiv, hdiv, radius, image, wsc, hsc, (unsigned int)triprop, mat);
        return Py_BuildValue("s", "Added sphere to object.");
    }

    Object* object_add_disk(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float irad, orad;
        float div, rings;
        float wsc=1.0, hsc=1.0;
        char* img;
        int triprop;
        int rtex;
        if( !PyArg_ParseTuple( args, "ssffffsffii:object_add_disk",
                &simname, &name,
                &div, &rings,
                &orad, &irad,
                &img, &wsc, &hsc, &triprop, &rtex) )
        {
            return NULL;
        }
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        addDisk(obj, div, rings, orad, irad, image, wsc, hsc, (unsigned int)triprop, bool(rtex), POGEL::MATRIX());
        return Py_BuildValue("s", "Added disk to object.");
    }

    Object* object_add_disk_mat(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float irad, orad;
        float div, rings;
        float wsc=1.0, hsc=1.0;
        char* img;
        int triprop;
        int rtex;
        float px,py,pz, rx,ry,rz;
        if( !PyArg_ParseTuple( args, "ssffffsffiiffffff:object_add_disk_mat",
                &simname, &name,
                &div, &rings,
                &orad, &irad,
                &img, &wsc, &hsc, &triprop, &rtex,
                &px,&py,&pz, &rx,&ry,&rz) )
        {
            return NULL;
        }
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        POGEL::MATRIX mat(POGEL::POINT(px,py,pz),POGEL::POINT(rx,ry,rz));
        addDisk(obj, div, rings, orad, irad, image, wsc, hsc, (unsigned int)triprop, bool(rtex), mat);
        return Py_BuildValue("s", "Added disk to object.");
    }

    Object* object_add_cylinder(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float lrad, urad;
        float height;
        float div, rings;
        float wsc=1.0, hsc=1.0;
        char* img;
        int triprop;
        if( !PyArg_ParseTuple( args, "ssfffffsffi:object_add_cylinder",
                &simname, &name,
                &div, &rings,
                &height, &lrad, &urad,
                &img, &wsc, &hsc, &triprop) )
        {
            return NULL;
        }
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        addCylinder(obj, div, rings, height, lrad, urad, image, wsc, hsc, (unsigned int)triprop, POGEL::MATRIX());
        return Py_BuildValue("s", "Added cylinder to object.");
    }

    Object* object_add_cylinder_mat(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float lrad, urad;
        float height;
        float div, rings;
        float wsc=1.0, hsc=1.0;
        char* img;
        int triprop;
        float px,py,pz, rx,ry,rz;
        if( !PyArg_ParseTuple( args, "ssfffffsffiffffff:object_add_cylinder_mat",
                &simname, &name,
                &div, &rings,
                &height, &lrad, &urad,
                &img, &wsc, &hsc, &triprop,
                &px,&py,&pz, &rx,&ry,&rz) )
        {
            return NULL;
        }
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        obj = sim->getObject(std::string(name));
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        POGEL::MATRIX mat(POGEL::POINT(px,py,pz),POGEL::POINT(rx,ry,rz));
        addCylinder(obj, div, rings, height, lrad, urad, image, wsc, hsc, (unsigned int)triprop, mat);
        return Py_BuildValue("s", "Added cylinder to object.");
    }

    Object* object_add_cube(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float h, w, d;
        float hsc=1.0, wsc=1.0;
        char* img;
        int triprop;
        if( !PyArg_ParseTuple( args, "ssfffsffi:object_add_cube",
                &simname, &name,
                &h, &w, &d,
                &img, &wsc, &hsc, &triprop) )
        {
            return NULL;
        }
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        void* vsim = sim->getSim();
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(vsim)->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(vsim)->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        addCube(obj, h, w, d, image, wsc, hsc, (unsigned int)triprop, POGEL::MATRIX());
        return Py_BuildValue("s", "Added cube to object.");
    }

    Object* object_add_cube_mat(Object* self, Object* args)
    {
        char* name;
        char* simname;
        float h, w, d;
        float hsc=1.0, wsc=1.0;
        char* img;
        int triprop;
        float px,py,pz, rx,ry,rz;
        if( !PyArg_ParseTuple( args, "ssfffsffiffffff:object_add_cube_mat",
                &simname, &name,
                &h, &w, &d,
                &img, &wsc, &hsc, &triprop,
                &px,&py,&pz, &rx,&ry,&rz) )
        {
            return NULL;
        }
        POGEL::PHYSICS::SOLID* obj;
        Renderer::Physics::Simulation * sim;
        sim = Renderer::Physics::getSimulation(std::string(simname));
        if(sim == NULL)
            return Py_BuildValue("s", "Simulation not found.");
        void* vsim = sim->getSim();
        if(sim->isdyn())
            obj = static_cast<POGEL::PHYSICS::DYNAMICS*>(vsim)->getSolid(name);
        else
            obj = static_cast<POGEL::PHYSICS::SIMULATION*>(vsim)->getSolid(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not in simulation");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        POGEL::MATRIX mat(POGEL::POINT(px,py,pz),POGEL::POINT(rx,ry,rz));
        addCube(obj, h, w, d, image, wsc, hsc, (unsigned int)triprop, mat);
        return Py_BuildValue("s", "Added cube to object.");
    }
}
