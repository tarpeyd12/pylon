#include "pogelscriptinterface.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    static MethodDef pogelMethods[] = {
        { "fps",                (CFunction)fps,               VarArgs, NULL },
        { "getproperties",      (CFunction)getproperties,     VarArgs, NULL },
        { "setproperties",      (CFunction)setproperties,     VarArgs, NULL },
        { "hasproperty",        (CFunction)hasproperty,       VarArgs, NULL },
        { "addsimulation",      (CFunction)addsimulation,     VarArgs, NULL },
        { "togglesim",          (CFunction)togglesimulation,  VarArgs, NULL },
        { "addobject",          (CFunction)addobject,         VarArgs, NULL },
        { "object_move_s",      (CFunction)object_move_s,     VarArgs, NULL },
        { "object_move_3f",     (CFunction)object_move_3f,    VarArgs, NULL },
        { "object_set_dir_s",   (CFunction)object_set_dir_s,  VarArgs, NULL },
        { "object_set_pos_s",   (CFunction)object_set_pos_s,  VarArgs, NULL },
        { "object_set_rot_s",   (CFunction)object_set_rot_s,  VarArgs, NULL },
        { "object_set_spin_s",  (CFunction)object_set_spin_s, VarArgs, NULL },
        { "object_set_dir_3f",  (CFunction)object_set_dir_3f, VarArgs, NULL },
        { "object_set_pos_3f",  (CFunction)object_set_pos_3f, VarArgs, NULL },
        { "object_set_rot_3f",  (CFunction)object_set_rot_3f, VarArgs, NULL },
        { "object_set_spin_3f", (CFunction)object_set_spin_3f,VarArgs, NULL },
        { "object_get_pos_s",   (CFunction)object_get_pos_s,  VarArgs, NULL },
        { "object_get_rot_s",   (CFunction)object_get_rot_s,  VarArgs, NULL },
        { "object_get_dir_s",   (CFunction)object_get_dir_s,  VarArgs, NULL },
        { "object_get_spin_s",  (CFunction)object_get_spin_s, VarArgs, NULL },
        { "key_ispressed",      (CFunction)key_ispressed,     VarArgs, NULL },
        { "key_last",           (CFunction)key_last,          VarArgs, NULL },
        { "mouse_ispressed",    (CFunction)mouse_ispressed,   VarArgs, NULL },
        { "mouse_getbutton",    (CFunction)mouse_getbutton,   VarArgs, NULL },
        { "mouse_pos_x",        (CFunction)mouse_pos_x,       VarArgs, NULL },
        { "mouse_pos_y",        (CFunction)mouse_pos_y,       VarArgs, NULL },
        { "mouse_pos_sx",       (CFunction)mouse_pos_sx,      VarArgs, NULL },
        { "mouse_pos_sy",       (CFunction)mouse_pos_sy,      VarArgs, NULL },
        { "camera_set_pos_s",   (CFunction)camera_set_pos_s,  VarArgs, NULL },
        { "camera_set_pos_3f",  (CFunction)camera_set_pos_3f, VarArgs, NULL },
        { "camera_set_rot_s",   (CFunction)camera_set_rot_s,  VarArgs, NULL },
        { "camera_set_rot_3f",  (CFunction)camera_set_rot_3f, VarArgs, NULL },
        { "window_height",      (CFunction)window_height,     VarArgs, NULL },
        { "window_width",       (CFunction)window_width,      VarArgs, NULL },
        { "getline",            (CFunction)getline,           VarArgs, NULL },
        { "requestfile_ar",     (CFunction)requestfile_ar,    VarArgs, NULL },
        { "requestfile",        (CFunction)requestfile,       VarArgs, NULL },
        { NULL }
    };

    void Init()
    {
        Add("pylon", pogelMethods);
        //ScriptEngine::Execute("import pogel\n");
    }
}
