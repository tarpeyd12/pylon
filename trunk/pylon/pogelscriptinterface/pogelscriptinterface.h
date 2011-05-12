#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#define POGELSCRIPTINTERFACE_H_INCLUDED

#ifndef Py_PYTHON_H
#include <Python.h>
#endif // Py_PYTHON_H

#include "../pogel/pogel.h"
#include "../scriptengine/scriptengine.h"
#include "../renderer/renderer.h"
#include "../fileloader/fileloader.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    void Init();

    // POGEL specific things

    Object* fps(Object*,Object*);
    Object* getproperties(Object*,Object*);
    Object* setproperties(Object*,Object*);
    Object* hasproperty(Object*,Object*);

    // the mouse and keyboard stuff

    Object* key_ispressed(Object*,Object*);
    Object* key_last(Object*,Object*);
    Object* mouse_ispressed(Object*,Object*);
    Object* mouse_getbutton(Object*,Object*);
    Object* mouse_pos_x(Object*,Object*);
    Object* mouse_pos_y(Object*,Object*);
    Object* mouse_pos_sx(Object*,Object*);
    Object* mouse_pos_sy(Object*,Object*);

    // camera stuff

    Object* camera_set_pos_s(Object*,Object*);
    Object* camera_set_pos_3f(Object*,Object*);
    Object* camera_set_rot_s(Object*,Object*);
    Object* camera_set_rot_3f(Object*,Object*);

    // window stuff

    Object* window_height(Object*,Object*);
    Object* window_width(Object*,Object*);

    // file loading stuff

    Object* getline(Object*,Object*);
    Object* requestfile_ar(Object*,Object*);
}

#include "objects.h"

#endif // POGELSCRIPTINTERFACE_H_INCLUDED
