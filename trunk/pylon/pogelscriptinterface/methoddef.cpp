#include "pogelscriptinterface.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    static MethodDef pogelMethods[] = {
        // pogel
        { "fps",                (CFunction)fps,               VarArgs, NULL },
        { "getruntime",         (CFunction)getruntime,        VarArgs, NULL },
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
        { "setsimulationcollitters", (CFunction)setsimulationcollitters, VarArgs, NULL },
        { "getsimulationcollitters", (CFunction)getsimulationcollitters, VarArgs, NULL },
        { "addobject",               (CFunction)addobject,               VarArgs, NULL },
        { "clearsimulation",         (CFunction)clearsimulation,         VarArgs, NULL },
        // object controll
        { "object_new",            (CFunction)object_new,            VarArgs, NULL },
        { "object_new_fromfile",   (CFunction)object_new_fromfile,   VarArgs, NULL },
        { "object_new_child",      (CFunction)object_new_child,      VarArgs, NULL },
        { "object_set_visibility", (CFunction)object_set_visibility, VarArgs, NULL },
        { "object_move_s",         (CFunction)object_move_s,         VarArgs, NULL },
        { "object_move_3f",        (CFunction)object_move_3f,        VarArgs, NULL },
        { "object_set_dir_s",      (CFunction)object_set_dir_s,      VarArgs, NULL },
        { "object_set_pos_s",      (CFunction)object_set_pos_s,      VarArgs, NULL },
        { "object_set_rot_s",      (CFunction)object_set_rot_s,      VarArgs, NULL },
        { "object_set_spin_s",     (CFunction)object_set_spin_s,     VarArgs, NULL },
        { "object_set_dir_3f",     (CFunction)object_set_dir_3f,     VarArgs, NULL },
        { "object_set_pos_3f",     (CFunction)object_set_pos_3f,     VarArgs, NULL },
        { "object_set_rot_3f",     (CFunction)object_set_rot_3f,     VarArgs, NULL },
        { "object_set_spin_3f",    (CFunction)object_set_spin_3f,    VarArgs, NULL },
        { "object_get_pos_s",      (CFunction)object_get_pos_s,      VarArgs, NULL },
        { "object_get_rot_s",      (CFunction)object_get_rot_s,      VarArgs, NULL },
        { "object_get_dir_s",      (CFunction)object_get_dir_s,      VarArgs, NULL },
        { "object_get_spin_s",     (CFunction)object_get_spin_s,     VarArgs, NULL },
        { "object_options",        (CFunction)object_options,        VarArgs, NULL },
        { "object_set_mass",       (CFunction)object_set_mass,       VarArgs, NULL },
        { "object_get_mass",       (CFunction)object_get_mass,       VarArgs, NULL },
        { "object_set_bounce",     (CFunction)object_set_bounce,     VarArgs, NULL },
        { "object_get_bounce",     (CFunction)object_get_bounce,     VarArgs, NULL },
        { "object_set_friction",   (CFunction)object_set_friction,   VarArgs, NULL },
        { "object_get_friction",   (CFunction)object_get_friction,   VarArgs, NULL },
        { "object_add_key",        (CFunction)object_add_key,        VarArgs, NULL },
        { "object_add_animation",  (CFunction)object_add_animation,  VarArgs, NULL },
        { "object_set_animation",  (CFunction)object_set_animation,  VarArgs, NULL },
        { "object_get_animation",  (CFunction)object_get_animation,  VarArgs, NULL },
        { "object_set_animtime",   (CFunction)object_set_animtime,   VarArgs, NULL },
        { "object_get_animlen",    (CFunction)object_get_animlen,    VarArgs, NULL },
        { "object_get_animsince",  (CFunction)object_get_animsince,  VarArgs, NULL },
        { "object_build",          (CFunction)object_build,          VarArgs, NULL },
        // object shapes
        { "object_add_sphere",       (CFunction)object_add_sphere,       VarArgs, NULL },
        { "object_add_sphere_mat",   (CFunction)object_add_sphere_mat,   VarArgs, NULL },
        { "object_add_disk",         (CFunction)object_add_disk,         VarArgs, NULL },
        { "object_add_disk_mat",     (CFunction)object_add_disk_mat,     VarArgs, NULL },
        { "object_add_cylinder",     (CFunction)object_add_cylinder,     VarArgs, NULL },
        { "object_add_cylinder_mat", (CFunction)object_add_cylinder_mat, VarArgs, NULL },
        { "object_add_cube",         (CFunction)object_add_cube,         VarArgs, NULL },
        { "object_add_cube_mat",     (CFunction)object_add_cube_mat,     VarArgs, NULL },
        { "object_add_triangle",     (CFunction)object_add_triangle,     VarArgs, NULL },
        // keyboard interface
        { "key_ispressed",      (CFunction)key_ispressed,      VarArgs, NULL },
        { "key_when_pressed",   (CFunction)key_when_pressed,   VarArgs, NULL },
        { "key_when_released",  (CFunction)key_when_released,  VarArgs, NULL },
        { "key_pos_press_2i",   (CFunction)key_pos_press_2i,   VarArgs, NULL },
        { "key_pos_release_2i", (CFunction)key_pos_release_2i, VarArgs, NULL },
        { "key_last",           (CFunction)key_last,           VarArgs, NULL },
        // mouse interface
        { "mouse_ispressed",    (CFunction)mouse_ispressed,   VarArgs, NULL },
        { "mouse_getbutton",    (CFunction)mouse_getbutton,   VarArgs, NULL },
        { "mouse_pos_x",        (CFunction)mouse_pos_x,       VarArgs, NULL },
        { "mouse_pos_y",        (CFunction)mouse_pos_y,       VarArgs, NULL },
        { "mouse_pos_sx",       (CFunction)mouse_pos_sx,      VarArgs, NULL },
        { "mouse_pos_sy",       (CFunction)mouse_pos_sy,      VarArgs, NULL },
        // selection interface
        { "select_isgood",       (CFunction)select_isgood,      VarArgs, NULL },
        { "select_get_sim",      (CFunction)select_get_sim,     VarArgs, NULL },
        { "select_get_obj",      (CFunction)select_get_obj,     VarArgs, NULL },
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
        { "addquadi",           (CFunction)addquadi,          VarArgs, NULL },
        { "addquadf",           (CFunction)addquadf,          VarArgs, NULL },
        { "updatequadi",        (CFunction)updatequadi,       VarArgs, NULL },
        { "updatequadf",        (CFunction)updatequadf,       VarArgs, NULL },
        { "removequad",         (CFunction)removequad,        VarArgs, NULL },
        { "clearquads",         (CFunction)clearquads,        VarArgs, NULL },
        { "maxquads",           (CFunction)maxquads,          VarArgs, NULL },
        { "checkquad",          (CFunction)checkquad,         VarArgs, NULL },
        { "quadgetvis",         (CFunction)quadgetvis,        VarArgs, NULL },
        { "quadsetvis",         (CFunction)quadsetvis,        VarArgs, NULL },
        // SubRender controll
        { "subrender_new",         (CFunction)subrender_new,         VarArgs, NULL },
        { "subrender_bind_sim",    (CFunction)subrender_bind_sim,    VarArgs, NULL },
        { "subrender_release_sim", (CFunction)subrender_release_sim, VarArgs, NULL },
        { "subrender_release_all", (CFunction)subrender_release_all, VarArgs, NULL },
        { "subrender_set_light",   (CFunction)subrender_set_light,   VarArgs, NULL },
        { "subrender_set_cam",     (CFunction)subrender_set_cam,     VarArgs, NULL },
        { "subrender_set_ratio",   (CFunction)subrender_set_ratio,   VarArgs, NULL },
        // callback controll
        { "callback_set_collfunc",    (CFunction)callback_set_collfunc,    VarArgs, NULL },
        { "callback_set_stepfunc",    (CFunction)callback_set_stepfunc,    VarArgs, NULL },
        { "callback_set_hitfilter",   (CFunction)callback_set_hitfilter,   VarArgs, NULL },
        /*{ "callback_set_collfunc_s",  (CFunction)callback_set_collfunc_s,  VarArgs, NULL },
        { "callback_set_stepfunc_s",  (CFunction)callback_set_stepfunc_s,  VarArgs, NULL },
        { "callback_set_hitfilter_s", (CFunction)callback_set_hitfilter_s, VarArgs, NULL },*/
        { NULL }
    };

    void Init()
    {
        Add("pylon", pogelMethods);
        //ScriptEngine::Execute("import pylon\n");
    }
}
