#include "shapes.h"
#include "../pogel/pogel.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* object_add_sphere(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float radius;
        float hdiv, wdiv;
        float hsc=1.0, wsc=1.0;
        char* img;
        int triprop;
        if( !PyArg_ParseTuple( args, "sOfffsffi:object_add_sphere",
                &simname, &name,
                &radius, &wdiv, &hdiv,
                &img, &wsc, &hsc, &triprop) )
        {
            return NULL;
        }
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found.");

        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        addSphere(obj, wdiv, hdiv, radius, image, wsc, hsc, (unsigned int)triprop);
        return Py_BuildValue("s", "Added sphere to object.");
    }

    Object* object_add_sphere_mat(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float radius;
        float hdiv, wdiv;
        float hsc=1.0, wsc=1.0;
        char* img;
        int triprop;
        float px,py,pz, rx,ry,rz;
        if( !PyArg_ParseTuple( args, "sOfffsffiffffff:object_add_sphere_mat",
                &simname, &name,
                &radius, &wdiv, &hdiv,
                &img, &wsc, &hsc, &triprop,
                &px,&py,&pz, &rx,&ry,&rz) )
        {
            return NULL;
        }
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found.");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        POGEL::MATRIX mat(POGEL::POINT(px,py,pz),POGEL::POINT(rx,ry,rz));
        addSphere(obj, wdiv, hdiv, radius, image, wsc, hsc, (unsigned int)triprop, mat);
        return Py_BuildValue("s", "Added sphere to object.");
    }

    Object* object_add_disk(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float irad, orad;
        float div, rings;
        float wsc=1.0, hsc=1.0;
        char* img;
        int triprop;
        int rtex;
        if( !PyArg_ParseTuple( args, "sOffffsffii:object_add_disk",
                &simname, &name,
                &div, &rings,
                &orad, &irad,
                &img, &wsc, &hsc, &triprop, &rtex) )
        {
            return NULL;
        }
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found.");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        addDisk(obj, div, rings, orad, irad, image, wsc, hsc, (unsigned int)triprop, bool(rtex), POGEL::MATRIX());
        return Py_BuildValue("s", "Added disk to object.");
    }

    Object* object_add_disk_mat(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float irad, orad;
        float div, rings;
        float wsc=1.0, hsc=1.0;
        char* img;
        int triprop;
        int rtex;
        float px,py,pz, rx,ry,rz;
        if( !PyArg_ParseTuple( args, "sOffffsffiiffffff:object_add_disk_mat",
                &simname, &name,
                &div, &rings,
                &orad, &irad,
                &img, &wsc, &hsc, &triprop, &rtex,
                &px,&py,&pz, &rx,&ry,&rz) )
        {
            return NULL;
        }
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found.");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        POGEL::MATRIX mat(POGEL::POINT(px,py,pz),POGEL::POINT(rx,ry,rz));
        addDisk(obj, div, rings, orad, irad, image, wsc, hsc, (unsigned int)triprop, bool(rtex), mat);
        return Py_BuildValue("s", "Added disk to object.");
    }

    Object* object_add_cylinder(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float lrad, urad;
        float height;
        float div, rings;
        float wsc=1.0, hsc=1.0;
        char* img;
        int triprop;
        if( !PyArg_ParseTuple( args, "sOfffffsffi:object_add_cylinder",
                &simname, &name,
                &div, &rings,
                &height, &lrad, &urad,
                &img, &wsc, &hsc, &triprop) )
        {
            return NULL;
        }
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found.");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        addCylinder(obj, div, rings, height, lrad, urad, image, wsc, hsc, (unsigned int)triprop, POGEL::MATRIX());
        return Py_BuildValue("s", "Added cylinder to object.");
    }

    Object* object_add_cylinder_mat(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float lrad, urad;
        float height;
        float div, rings;
        float wsc=1.0, hsc=1.0;
        char* img;
        int triprop;
        float px,py,pz, rx,ry,rz;
        if( !PyArg_ParseTuple( args, "sOfffffsffiffffff:object_add_cylinder_mat",
                &simname, &name,
                &div, &rings,
                &height, &lrad, &urad,
                &img, &wsc, &hsc, &triprop,
                &px,&py,&pz, &rx,&ry,&rz) )
        {
            return NULL;
        }
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found.");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        POGEL::MATRIX mat(POGEL::POINT(px,py,pz),POGEL::POINT(rx,ry,rz));
        addCylinder(obj, div, rings, height, lrad, urad, image, wsc, hsc, (unsigned int)triprop, mat);
        return Py_BuildValue("s", "Added cylinder to object.");
    }

    Object* object_add_cube(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float h, w, d;
        float hsc=1.0, wsc=1.0;
        char* img;
        int triprop;
        if( !PyArg_ParseTuple( args, "sOfffsffi:object_add_cube",
                &simname, &name,
                &h, &w, &d,
                &img, &wsc, &hsc, &triprop) )
        {
            return NULL;
        }
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found.");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        addCube(obj, h, w, d, image, wsc, hsc, (unsigned int)triprop, POGEL::MATRIX());
        return Py_BuildValue("s", "Added cube to object.");
    }

    Object* object_add_cube_mat(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        float h, w, d;
        float hsc=1.0, wsc=1.0;
        char* img;
        int triprop;
        float px,py,pz, rx,ry,rz;
        if( !PyArg_ParseTuple( args, "sOfffsffiffffff:object_add_cube_mat",
                &simname, &name,
                &h, &w, &d,
                &img, &wsc, &hsc, &triprop,
                &px,&py,&pz, &rx,&ry,&rz) )
        {
            return NULL;
        }
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found.");
        POGEL::IMAGE* image = Renderer::requestImage(std::string(img));
        POGEL::MATRIX mat(POGEL::POINT(px,py,pz),POGEL::POINT(rx,ry,rz));
        addCube(obj, h, w, d, image, wsc, hsc, (unsigned int)triprop, mat);
        return Py_BuildValue("s", "Added cube to object.");
    }

    Object* object_add_triangle(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        char* img;
        POGEL::TRIANGLE tri;
        int prop;
        if( !PyArg_ParseTuple(
                args,
                "sOs"

                "fff"
                "ff"
                "fff"
                "ffff"

                "fff"
                "ff"
                "fff"
                "ffff"

                "fff"
                "ff"
                "fff"
                "ffff"

                "i"

                ":object_add_triangle",
                &simname, &name, &img,

                &tri.vertex[0].x, &tri.vertex[0].y, &tri.vertex[0].z,
                &tri.vertex[0].u, &tri.vertex[0].v,
                &tri.vertex[0].normal.x, &tri.vertex[0].normal.y, &tri.vertex[0].normal.z,
                &tri.vertex[0].color.r, &tri.vertex[0].color.g, &tri.vertex[0].color.b, &tri.vertex[0].color.a,

                &tri.vertex[1].x, &tri.vertex[1].y, &tri.vertex[1].z,
                &tri.vertex[1].u, &tri.vertex[1].v,
                &tri.vertex[1].normal.x, &tri.vertex[1].normal.y, &tri.vertex[1].normal.z,
                &tri.vertex[1].color.r, &tri.vertex[1].color.g, &tri.vertex[1].color.b, &tri.vertex[1].color.a,

                &tri.vertex[2].x, &tri.vertex[2].y, &tri.vertex[2].z,
                &tri.vertex[2].u, &tri.vertex[2].v,
                &tri.vertex[2].normal.x, &tri.vertex[2].normal.y, &tri.vertex[2].normal.z,
                &tri.vertex[2].color.r, &tri.vertex[2].color.g, &tri.vertex[2].color.b, &tri.vertex[2].color.a,

                &prop
                ) )
        {
            return NULL;
        }
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found.");

        tri.texture = Renderer::requestImage(std::string(img));
        tri.setproperties((unsigned int)prop);

        tri.updateVert();
        obj->addtriangle(tri);

        return Py_BuildValue("s", "Added triangle to object.");
    }

    Object* object_add_triangle2(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        char* img;
        POGEL::TRIANGLE tri;
        int prop;
        int ind[3];
        Object* verts;
        if( !PyArg_ParseTuple(
                args,
                "sOsi"
                "O"
                "((ff)(ff)(ff))"
                "|((fff)(fff)(fff))"
                "|((ffff)(ffff)(ffff))"
                ":object_add_triangle2",
                &simname, &name, &img, &prop,
                &verts,
                &tri.vertex[0].u, &tri.vertex[0].v,
                &tri.vertex[1].u, &tri.vertex[1].v,
                &tri.vertex[2].u, &tri.vertex[2].v,
                &tri.vertex[0].normal.x, &tri.vertex[0].normal.y, &tri.vertex[0].normal.z,
                &tri.vertex[1].normal.x, &tri.vertex[1].normal.y, &tri.vertex[1].normal.z,
                &tri.vertex[2].normal.x, &tri.vertex[2].normal.y, &tri.vertex[2].normal.z,
                &tri.vertex[0].color.r, &tri.vertex[0].color.g, &tri.vertex[0].color.b, &tri.vertex[0].color.a,
                &tri.vertex[1].color.r, &tri.vertex[1].color.g, &tri.vertex[1].color.b, &tri.vertex[1].color.a,
                &tri.vertex[2].color.r, &tri.vertex[2].color.g, &tri.vertex[2].color.b, &tri.vertex[2].color.a
                ) )
        {
            return NULL;
        }
        if( !PyTuple_CheckExact(verts) || PyTuple_Size(verts) != 3 )
        {
            return NULL;
        }

        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            return Py_BuildValue("s", "Object not found.");

        Object * triprp[] = { PyTuple_GetItem(verts,0), PyTuple_GetItem(verts,1), PyTuple_GetItem(verts,2) };

        bool type1 = false, type2 = false;

        for( unsigned int i = 0; i < 3; ++i )
        {
            if( PyTuple_CheckExact(triprp[i]) && PyTuple_Size(triprp[i]) == 3 )
            {
                bool settype1 = true;
                for( unsigned int p = 0; p < 3; ++p )
                {
                    if( !PyFloat_CheckExact( PyTuple_GetItem( triprp[i], p ) ) )
                    {
                        settype1 = false;
                        break;
                    }
                }
                if( settype1 )
                {
                    type1 = true;
                }
            }
            if( !type2 && PyInt_Check( triprp[i] ) )
            {
                type2 = true;
            }
        }

        if( type1 && !type2 )
        {
            for( unsigned int i = 0; i < 3; ++i )
            {
                tri.vertex[i].x = PyFloat_AsDouble( PyTuple_GetItem(triprp[i],0) );
                tri.vertex[i].y = PyFloat_AsDouble( PyTuple_GetItem(triprp[i],1) );
                tri.vertex[i].z = PyFloat_AsDouble( PyTuple_GetItem(triprp[i],2) );
            }
        }
        else if( type2 && !type1 )
        {
            ind[0] = PyInt_AsLong( triprp[0] );
            ind[1] = PyInt_AsLong( triprp[1] );
            ind[2] = PyInt_AsLong( triprp[2] );

            POGEL::TRIANGLE tri2( obj->getVertexListAddress(), obj->getNumVerticies(), ind[0], ind[1], ind[2], NULL, 0 );
            for( int a = 0; a < 3; ++a )
            {
                tri2.vertex[a].u = tri.vertex[a].u;
                tri2.vertex[a].v = tri.vertex[a].v;
                tri2.vertex[a].color = tri.vertex[a].color;

                tri2.vertex[a].normal = tri.vertex[a].normal;
                tri2.vertnormals[a] = tri.vertex[a].normal;
            }
            tri = tri2;
        }
        else
        {
            return NULL;
        }

        tri.texture = Renderer::requestImage(std::string(img));
        tri.setproperties((unsigned int)prop);

        tri.updateVert();
        obj->addtriangle(tri);

        return Py_BuildValue("s", "Added triangle to object.");
    }

    Object* object_add_vertex(Object* self, Object* args)
    {
        Object* name;
        char* simname;
        POGEL::VERTEX vert;
        int weights[3];
        if( !PyArg_ParseTuple( args,
            "sO(fff)(ff)|(fff)|(ffff)|(iiii)(iii):object_add_vertex",
            &simname, &name,
            &vert.x, &vert.y, &vert.z,
            &vert.u, &vert.v,
            &vert.normal.x, &vert.normal.y, &vert.normal.z,
            &vert.color.r, &vert.color.g, &vert.color.b, &vert.color.a,
            &vert.boneID, &vert.boneIDs[0], &vert.boneIDs[1], &vert.boneIDs[2],
            &weights[0], &weights[1], &weights[2]
            ) )
        {
            return NULL;
        }
        vert.weights[0] = (unsigned char)weights[0];
        vert.weights[1] = (unsigned char)weights[1];
        vert.weights[2] = (unsigned char)weights[2];
        Py_XINCREF(name);
        POGEL::OBJECT * obj = pogelInterface::GetObject( std::string(simname), name );
        Py_XDECREF(name);
        if(obj == NULL)
            Py_BuildValue("i", -1);
        ;
        unsigned int ret = obj->addVertex(vert);
        return Py_BuildValue("i", ret);
    }
}
