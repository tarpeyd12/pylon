#include "pogelscriptinterface.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    static MethodDef pogelMethods[] = {
        // pogel
        { "fps",                (CFunction)fps,               VarArgs, NULL },
        { "getproperties",      (CFunction)getproperties,     VarArgs, NULL },
        { "setproperties",      (CFunction)setproperties,     VarArgs, NULL },
        { "hasproperty",        (CFunction)hasproperty,       VarArgs, NULL },
        { "addproperty",        (CFunction)addproperty,       VarArgs, NULL },
        { "removeproperty",     (CFunction)removeproperty,    VarArgs, NULL },
        // pogel simulations
        { "addsimulation",           (CFunction)addsimulation,           VarArgs, NULL },
        { "togglesim",               (CFunction)togglesimulation,        VarArgs, NULL },
        { "togglesimweight",         (CFunction)togglesimweight,         VarArgs, NULL },
        { "setsimulationgravity_3f", (CFunction)setsimulationgravity_3f, VarArgs, NULL },
        { "clearsimulation",         (CFunction)clearsimulation,         VarArgs, NULL },
        // object controll
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
        { "object_build",       (CFunction)object_build,      VarArgs, NULL },
        // object shapes
        { "object_add_sphere",       (CFunction)object_add_sphere,       VarArgs, NULL },
        { "object_add_sphere_mat",   (CFunction)object_add_sphere_mat,   VarArgs, NULL },
        { "object_add_disk",         (CFunction)object_add_disk,         VarArgs, NULL },
        { "object_add_disk_mat",     (CFunction)object_add_disk_mat,     VarArgs, NULL },
        { "object_add_cylinder",     (CFunction)object_add_cylinder,     VarArgs, NULL },
        { "object_add_cylinder_mat", (CFunction)object_add_cylinder_mat, VarArgs, NULL },
        { "object_add_cube",         (CFunction)object_add_cube,         VarArgs, NULL },
        { "object_add_cube_mat",     (CFunction)object_add_cube_mat,     VarArgs, NULL },
        // keyboard interface
        { "key_ispressed",      (CFunction)key_ispressed,     VarArgs, NULL },
        { "key_last",           (CFunction)key_last,          VarArgs, NULL },
        // mouse interface
        { "mouse_ispressed",    (CFunction)mouse_ispressed,   VarArgs, NULL },
        { "mouse_getbutton",    (CFunction)mouse_getbutton,   VarArgs, NULL },
        { "mouse_pos_x",        (CFunction)mouse_pos_x,       VarArgs, NULL },
        { "mouse_pos_y",        (CFunction)mouse_pos_y,       VarArgs, NULL },
        { "mouse_pos_sx",       (CFunction)mouse_pos_sx,      VarArgs, NULL },
        { "mouse_pos_sy",       (CFunction)mouse_pos_sy,      VarArgs, NULL },
        // camera controll
        { "camera_set_pos_s",   (CFunction)camera_set_pos_s,  VarArgs, NULL },
        { "camera_set_pos_3f",  (CFunction)camera_set_pos_3f, VarArgs, NULL },
        { "camera_set_rot_s",   (CFunction)camera_set_rot_s,  VarArgs, NULL },
        { "camera_set_rot_3f",  (CFunction)camera_set_rot_3f, VarArgs, NULL },
        // window properties
        { "window_height",      (CFunction)window_height,     VarArgs, NULL },
        { "window_width",       (CFunction)window_width,      VarArgs, NULL },
        // archive/file handeling
        { "getline",            (CFunction)getline,           VarArgs, NULL },
        { "requestfile_ar",     (CFunction)requestfile_ar,    VarArgs, NULL },
        { "requestfile",        (CFunction)requestfile,       VarArgs, NULL },
        // HUD controll
        { "addquad",            (CFunction)addquad,           VarArgs, NULL },
        { "updatequad",         (CFunction)updatequad,        VarArgs, NULL },
        { "removequad",         (CFunction)removequad,        VarArgs, NULL },
        { "clearquads",         (CFunction)clearquads,        VarArgs, NULL },
        { "maxquads",           (CFunction)maxquads,          VarArgs, NULL },
        { "checkquad",          (CFunction)checkquad,         VarArgs, NULL },
        { NULL }
    };

    void Init()
    {
        Add("pylon", pogelMethods);
        //ScriptEngine::Execute("import pogel\n");
    }
}
