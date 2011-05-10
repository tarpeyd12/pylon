#include "pogelscriptinterface.h"

namespace pogelInterface
{
    ScriptEngine::MethodInterface::Object*
    fps(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        if(!PyArg_ParseTuple(args, ":fps"))
            return NULL;
        return Py_BuildValue("f", POGEL::GetFps());
    }

    ScriptEngine::MethodInterface::Object*
    getproperties(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        if(!PyArg_ParseTuple(args, ":getproperties"))
            return NULL;
        return Py_BuildValue("i", (int)POGEL::getproperties());
    }

    ScriptEngine::MethodInterface::Object*
    setproperties(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        int p;
        if(!PyArg_ParseTuple(args, "i:setproperties", &p))
            return NULL;
        POGEL::setproperties((unsigned int)p);
        POGEL::removeproperty(POGEL_LOGTOFILE);
        return Py_BuildValue("i", POGEL::getproperties());
    }

    ScriptEngine::MethodInterface::Object*
    hasproperty(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        int p;
        if(!PyArg_ParseTuple(args, "i:hasproperty", &p))
            return NULL;
        return Py_BuildValue("i", (int)POGEL::hasproperty((unsigned int)p));
    }

    ScriptEngine::MethodInterface::Object*
    key_ispressed(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_ispressed", &checkedKey))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Key::keys[(unsigned int)checkedKey]);
    }

    ScriptEngine::MethodInterface::Object*
    mouse_ispressed(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        if(!PyArg_ParseTuple(args, ":mouse_ispressed"))
            return NULL;
        return Py_BuildValue("i", (int)(Renderer::Mouse::state == GLUT_DOWN));
    }

    ScriptEngine::MethodInterface::Object*
    mouse_getbutton(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        if(!PyArg_ParseTuple(args, ":mouse_getbutton"))
            return NULL;
        return Py_BuildValue("i", (int)(Renderer::Mouse::button));
    }

    ScriptEngine::MethodInterface::Object*
    mouse_pos_x(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_x"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::X);
    }

    ScriptEngine::MethodInterface::Object*
    mouse_pos_y(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_y"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::Y);
    }

    ScriptEngine::MethodInterface::Object*
    mouse_pos_sx(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_sx"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::static_x);
    }

    ScriptEngine::MethodInterface::Object*
    mouse_pos_sy(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_sy"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::static_y);
    }

    ScriptEngine::MethodInterface::Object*
    camera_set_pos_s(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        char* newpos;
        if(!PyArg_ParseTuple(args, "s:camera_set_pos_s", &newpos))
            return NULL;
        Renderer::campos = POGEL::POINT(std::string(newpos));
        return Py_BuildValue("s", Renderer::campos.toString().c_str());
    }

    ScriptEngine::MethodInterface::Object*
    camera_set_pos_3f(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        float x, y, z;
        if(!PyArg_ParseTuple(args, "fff:camera_set_pos_3f", &x, &y, &z))
            return NULL;
        Renderer::campos = POGEL::POINT(x,y,z);
        return Py_BuildValue("s", Renderer::campos.toString().c_str());
    }

    ScriptEngine::MethodInterface::Object*
    camera_set_rot_s(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        char* newpos;
        if(!PyArg_ParseTuple(args, "s:camera_set_rot_s", &newpos))
            return NULL;
        Renderer::camrot = POGEL::POINT(std::string(newpos));
        return Py_BuildValue("s", Renderer::camrot.toString().c_str());
    }

    ScriptEngine::MethodInterface::Object*
    camera_set_rot_3f(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        float x, y, z;
        if(!PyArg_ParseTuple(args, "fff:camera_set_rot_3f", &x, &y, &z))
            return NULL;
        Renderer::camrot = POGEL::POINT(x,y,z);
        return Py_BuildValue("s", Renderer::camrot.toString().c_str());
    }

    ScriptEngine::MethodInterface::Object*
    window_height(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        if(!PyArg_ParseTuple(args, ":window_height"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Window::Size::height);
    }

    ScriptEngine::MethodInterface::Object*
    window_width(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        if(!PyArg_ParseTuple(args, ":window_width"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Window::Size::width);
    }

    ScriptEngine::MethodInterface::Object*
    getline(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        char* filename;
        int line;
        if(!PyArg_ParseTuple(args, "si:getline", &filename, &line))
            return NULL;
        return Py_BuildValue("s", FileLoader::getline(std::string(filename),line).c_str());
    }

    ScriptEngine::MethodInterface::Object*
    requestfile_ar(
        ScriptEngine::MethodInterface::Object* self,
        ScriptEngine::MethodInterface::Object* args)
    {
        char* filename;
        char* archive;
        if(!PyArg_ParseTuple(args, "ss:getline", &filename, &archive))
            return NULL;
        int ret = FileLoader::extractfile(std::string(archive),std::string(filename),true,false,"",false,"");
        if(ret == 0)
            return Py_BuildValue("s", "Sucessful file retrival from resource pylon");
        else if(ret == -1234)
            return Py_BuildValue("s", "Sucessful file retrival from resource directory");
        else
            return Py_BuildValue("s", "File retrival from resource pylon unsucessful");
    }

}
