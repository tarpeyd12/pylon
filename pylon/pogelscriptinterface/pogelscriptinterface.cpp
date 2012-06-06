#include "pogelscriptinterface.h"

namespace pogelInterface
{
    Object* fps( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":fps"))
            return NULL;
        return Py_BuildValue("f", POGEL::GetFps());
    }

    Object* getruntime( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":getruntime"))
            return NULL;
        return Py_BuildValue("f", POGEL::GetTimePassed());
    }

    Object* getproperties( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":getproperties"))
            return NULL;
        return Py_BuildValue("i", (int)POGEL::getproperties());
    }

    Object* setproperties( Object* self, Object* args )
    {
        int p;
        if(!PyArg_ParseTuple(args, "i:setproperties", &p))
            return NULL;
        POGEL::setproperties((unsigned int)p);
        POGEL::removeproperty(POGEL_LOGTOFILE);
        return Py_BuildValue("i", POGEL::getproperties());
    }

    Object* hasproperty( Object* self, Object* args )
    {
        int p;
        if(!PyArg_ParseTuple(args, "i:hasproperty", &p))
            return NULL;
        return Py_BuildValue("i", (int)POGEL::hasproperty((unsigned int)p));
    }

    Object* addproperty( Object* self, Object* args )
    {
        int p;
        if(!PyArg_ParseTuple(args, "i:addproperty", &p))
            return NULL;
        POGEL::addproperty(p);
        return Py_BuildValue("i", (int)POGEL::getproperties());
    }

    Object* removeproperty( Object* self, Object* args )
    {
        int p;
        if(!PyArg_ParseTuple(args, "i:removeproperty", &p))
            return NULL;
        POGEL::removeproperty(p);
        return Py_BuildValue("i", (int)POGEL::getproperties());
    }

    Object* key_ispressed( Object* self, Object* args )
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_ispressed", &checkedKey))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Key::keys[(unsigned int)checkedKey]);
    }

    Object* key_when_pressed( Object* self, Object* args )
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_when_pressed", &checkedKey))
            return NULL;
        return Py_BuildValue("f", Renderer::Key::lastpressed[(unsigned int)checkedKey]);
    }

    Object* key_when_released( Object* self, Object* args )
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_when_released", &checkedKey))
            return NULL;
        return Py_BuildValue("f", Renderer::Key::lastreleased[(unsigned int)checkedKey]);
    }

    Object* key_pos_press_2i( Object* self, Object* args )
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_pos_press_2i", &checkedKey))
            return NULL;
        return Py_BuildValue("(ii)", Renderer::Key::mousepospress[(unsigned int)checkedKey][0], Renderer::Key::mousepospress[(unsigned int)checkedKey][1] );
    }

    Object* key_pos_release_2i( Object* self, Object* args )
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_pos_release_2i", &checkedKey))
            return NULL;
        return Py_BuildValue("(ii)", Renderer::Key::mouseposrelease[(unsigned int)checkedKey][0], Renderer::Key::mouseposrelease[(unsigned int)checkedKey][1] );
    }

    Object* key_last(Object* self, Object* args)
    {
        if(!PyArg_ParseTuple(args, ":key_last"))
            return NULL;
        return Py_BuildValue("c", (char)Renderer::Key::last);
    }

    Object* mouse_ispressed( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_ispressed"))
            return NULL;
        return Py_BuildValue("i", (int)(Renderer::Mouse::state == GLUT_DOWN));
    }

    Object* mouse_getbutton( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_getbutton"))
            return NULL;
        return Py_BuildValue("i", (int)(Renderer::Mouse::button));
    }

    Object* mouse_pos_x( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_x"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::X);
    }

    Object* mouse_pos_y( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_y"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::Y);
    }

    Object* mouse_pos_sx( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_sx"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::static_x);
    }

    Object* mouse_pos_sy( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_sy"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::static_y);
    }

    Object* camera_set_pos_s( Object* self, Object* args )
    {
        char* newpos;
        if(!PyArg_ParseTuple(args, "s:camera_set_pos_s", &newpos))
            return NULL;
        Renderer::Camera::campos = POGEL::POINT(std::string(newpos));
        return Py_BuildValue("s", Renderer::Camera::campos.toString().c_str());
    }

    Object* camera_set_pos_3f( Object* self, Object* args )
    {
        float x, y, z;
        if(!PyArg_ParseTuple(args, "fff:camera_set_pos_3f", &x, &y, &z))
            return NULL;
        Renderer::Camera::campos = POGEL::POINT(x,y,z);
        return Py_BuildValue("s", Renderer::Camera::campos.toString().c_str());
    }

    Object* camera_set_rot_s( Object* self, Object* args )
    {
        char* newpos;
        if(!PyArg_ParseTuple(args, "s:camera_set_rot_s", &newpos))
            return NULL;
        Renderer::Camera::camrot = POGEL::POINT(std::string(newpos));
        return Py_BuildValue("s", Renderer::Camera::camrot.toString().c_str());
    }

    Object* camera_set_rot_3f( Object* self, Object* args )
    {
        float x, y, z;
        if(!PyArg_ParseTuple(args, "fff:camera_set_rot_3f", &x, &y, &z))
            return NULL;
        Renderer::Camera::camrot = POGEL::POINT(x,y,z);
        return Py_BuildValue("s", Renderer::Camera::camrot.toString().c_str());
    }

    Object* window_height( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":window_height"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Window::Size::height);
    }

    Object* window_width( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":window_width"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Window::Size::width);
    }

    Object* getline( Object* self, Object* args )
    {
        char* filename;
        int line;
        if(!PyArg_ParseTuple(args, "si:getline", &filename, &line))
            return NULL;
        return Py_BuildValue("s", FileLoader::getline(std::string(filename),line).c_str());
    }

    Object* requestfile_ar( Object* self, Object* args )
    {
        char* filename;
        char* archive;
        if(!PyArg_ParseTuple(args, "ss:requestfile_ar", &filename, &archive))
            return NULL;
        int ret = FileLoader::extractfile(std::string(archive),std::string(filename),true,false,"",false,"");
        if(ret == 0)
            return Py_BuildValue("s", std::string("Sucessful file retrival from resource pylon, "+std::string(filename)).c_str());
        else if(ret == -1234)
            return Py_BuildValue("s", "Sucessful file retrival from resource directory");
        else
            return Py_BuildValue("s", std::string("File retrival from resource pylon unsucessful, "+std::string(filename)).c_str());
    }

    Object* requestfile( Object* self, Object* args )
    {
        char* filename;
        if(!PyArg_ParseTuple(args, "s:requestfile", &filename))
            return NULL;
        int ret = FileLoader::ArchiveHandler::extractKnownFile(std::string(filename));
        if(ret == 0)
            return Py_BuildValue("s", std::string("Sucessful file retrival from resource pylon, "+std::string(filename)).c_str());
        else if(ret == -1234)
            return Py_BuildValue("s", "Sucessful file retrival from resource directory");
        else
            return Py_BuildValue("s", std::string("File retrival from resource pylon unsucessful, "+std::string(filename)).c_str());
    }

}
