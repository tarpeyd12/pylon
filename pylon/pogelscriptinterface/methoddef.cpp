#include "pogelscriptinterface.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    static MethodDef pogelMethods[] = {
        // pogel
        { "get_fps",             (CFunction)fps,               VarArgs, NULL },
        { "get_runtime",         (CFunction)getruntime,        VarArgs, NULL },
        { "get_properties",      (CFunction)getproperties,     VarArgs, NULL },
        { "set_properties",      (CFunction)setproperties,     VarArgs, NULL },
        { "has_property",        (CFunction)hasproperty,       VarArgs, NULL },
        { "add_property",        (CFunction)addproperty,       VarArgs, NULL },
        { "remove_property",     (CFunction)removeproperty,    VarArgs, NULL },
        // wait functions
        { "wait_sec_f",          (CFunction)wait_sec_f,        VarArgs, NULL },
        { "wait_usec_i",         (CFunction)wait_usec_i,       VarArgs, NULL },
        // pogel simulations
        { "sim_new",            (CFunction)sim_new,            VarArgs, NULL },
        { "sim_toggle",         (CFunction)sim_toggle,         VarArgs, NULL },
        { "sim_halt",           (CFunction)sim_halt,           VarArgs, NULL },
        { "sim_visibility",     (CFunction)sim_visibility,     VarArgs, NULL },
        { "sim_weight",         (CFunction)sim_weight,         VarArgs, NULL },
        { "sim_set_gravity_3f", (CFunction)sim_set_gravity_3f, VarArgs, NULL },
        { "sim_get_gravity_3f", (CFunction)sim_get_gravity_3f, VarArgs, NULL },
        { "sim_set_itter",      (CFunction)sim_set_itter,      VarArgs, NULL },
        { "sim_get_itter",      (CFunction)sim_get_itter,      VarArgs, NULL },
        { "sim_add_object_s",   (CFunction)sim_add_object_s,   VarArgs, NULL },
        { "sim_clear",          (CFunction)sim_clear,          VarArgs, NULL },
        // object controll
        { "object_new",            (CFunction)object_new,            VarArgs, NULL },
        { "object_new_fromfile",   (CFunction)object_new_fromfile,   VarArgs, NULL },
        { "object_new_child",      (CFunction)object_new_child,      VarArgs, NULL },
        { "object_get_type_s",     (CFunction)object_get_type_s,     VarArgs, NULL },
        { "object_get_type_i",     (CFunction)object_get_type_i,     VarArgs, NULL },
        { "object_check",          (CFunction)object_check,          VarArgs, NULL },
        { "object_set_visibility", (CFunction)object_set_visibility, VarArgs, NULL },
        { "object_get_visibility", (CFunction)object_get_visibility, VarArgs, NULL },
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
        { "object_get_dir_3f",     (CFunction)object_get_dir_3f,     VarArgs, NULL },
        { "object_get_pos_3f",     (CFunction)object_get_pos_3f,     VarArgs, NULL },
        { "object_get_rot_3f",     (CFunction)object_get_rot_3f,     VarArgs, NULL },
        { "object_get_spin_3f",    (CFunction)object_get_spin_3f,    VarArgs, NULL },
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
        { "object_get_steps",      (CFunction)object_get_steps,      VarArgs, NULL },
        { "object_add_key",        (CFunction)object_add_key,        VarArgs, NULL },
        { "object_add_animation",  (CFunction)object_add_animation,  VarArgs, NULL },
        { "object_set_animation",  (CFunction)object_set_animation,  VarArgs, NULL },
        { "object_get_animation",  (CFunction)object_get_animation,  VarArgs, NULL },
        { "object_has_animation",  (CFunction)object_has_animation,  VarArgs, NULL },
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
        { "object_add_triangle2",    (CFunction)object_add_triangle2,    VarArgs, NULL },
        { "object_add_vertex",       (CFunction)object_add_vertex,       VarArgs, NULL },
        // object callback controll
        { "object_callback_set_collfunc",    (CFunction)object_callback_set_collfunc,    VarArgs, NULL },
        { "object_callback_set_stepfunc",    (CFunction)object_callback_set_stepfunc,    VarArgs, NULL },
        { "object_callback_set_hitfilter",   (CFunction)object_callback_set_hitfilter,   VarArgs, NULL },
        // keyboard interface
        { "key_ispressed",      (CFunction)key_ispressed,      VarArgs, NULL },
        { "key_when_pressed",   (CFunction)key_when_pressed,   VarArgs, NULL },
        { "key_when_released",  (CFunction)key_when_released,  VarArgs, NULL },
        { "key_pos_press_2i",   (CFunction)key_pos_press_2i,   VarArgs, NULL },
        { "key_pos_release_2i", (CFunction)key_pos_release_2i, VarArgs, NULL },
        { "key_last",           (CFunction)key_last,           VarArgs, NULL },
        // key callback controll
        { "key_callback_add_downfunc",    (CFunction)key_callback_add_downfunc,    VarArgs, NULL },
        { "key_callback_add_objdownfunc", (CFunction)key_callback_add_objdownfunc, VarArgs, NULL },
        { "key_callback_add_downfilters", (CFunction)key_callback_add_downfilters, VarArgs, NULL },
        { "key_callback_remove_downfunc", (CFunction)key_callback_remove_downfunc, VarArgs, NULL },
        { "key_callback_add_upfunc",      (CFunction)key_callback_add_upfunc,      VarArgs, NULL },
        { "key_callback_add_objupfunc",   (CFunction)key_callback_add_objupfunc,   VarArgs, NULL },
        { "key_callback_add_upfilters",   (CFunction)key_callback_add_upfilters,   VarArgs, NULL },
        { "key_callback_remove_upfunc",   (CFunction)key_callback_remove_upfunc,   VarArgs, NULL },
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
        { "camera_get_pos_3f",  (CFunction)camera_get_pos_3f, VarArgs, NULL },
        { "camera_get_rot_3f",  (CFunction)camera_get_rot_3f, VarArgs, NULL },
        // window properties
        { "window_height",      (CFunction)window_height,     VarArgs, NULL },
        { "window_width",       (CFunction)window_width,      VarArgs, NULL },
        // archive/file handeling
        { "getline",            (CFunction)getline,           VarArgs, NULL },
        { "requestfile_ar",     (CFunction)requestfile_ar,    VarArgs, NULL },
        { "requestfile",        (CFunction)requestfile,       VarArgs, NULL },
        // HUD controll
        { "quad_add_4i",      (CFunction)addquadi,          VarArgs, NULL },
        { "quad_add_4f",      (CFunction)addquadf,          VarArgs, NULL },
        { "quad_update_4i",   (CFunction)updatequadi,       VarArgs, NULL },
        { "quad_update_4f",   (CFunction)updatequadf,       VarArgs, NULL },
        { "quad_remove",      (CFunction)removequad,        VarArgs, NULL },
        { "quad_clear_all",   (CFunction)clearquads,        VarArgs, NULL },
        { "quad_max_num",     (CFunction)maxquads,          VarArgs, NULL },
        { "quad_check",       (CFunction)checkquad,         VarArgs, NULL },
        { "quad_get_vis",     (CFunction)quadgetvis,        VarArgs, NULL },
        { "quad_set_vis",     (CFunction)quadsetvis,        VarArgs, NULL },
        // SubRender controll
        { "subrender_new",         (CFunction)subrender_new,         VarArgs, NULL },
        { "subrender_bind_sim",    (CFunction)subrender_bind_sim,    VarArgs, NULL },
        { "subrender_release_sim", (CFunction)subrender_release_sim, VarArgs, NULL },
        { "subrender_release_all", (CFunction)subrender_release_all, VarArgs, NULL },
        { "subrender_set_light",   (CFunction)subrender_set_light,   VarArgs, NULL },
        { "subrender_set_cam",     (CFunction)subrender_set_cam,     VarArgs, NULL },
        { "subrender_set_ratio",   (CFunction)subrender_set_ratio,   VarArgs, NULL },


        // legacy function names

        // pogel stuff
        { "fps",                (CFunction)fps,               VarArgs, NULL },
        { "getruntime",         (CFunction)getruntime,        VarArgs, NULL },
        { "getproperties",      (CFunction)getproperties,     VarArgs, NULL },
        { "setproperties",      (CFunction)setproperties,     VarArgs, NULL },
        { "hasproperty",        (CFunction)hasproperty,       VarArgs, NULL },
        { "addproperty",        (CFunction)addproperty,       VarArgs, NULL },
        { "removeproperty",     (CFunction)removeproperty,    VarArgs, NULL },
        // simulation stuff
        { "addsimulation",           (CFunction)sim_new,            VarArgs, NULL },
        { "togglesim",               (CFunction)sim_toggle,         VarArgs, NULL },
        { "togglesimweight",         (CFunction)sim_weight,         VarArgs, NULL },
        { "setsimulationgravity_3f", (CFunction)sim_set_gravity_3f, VarArgs, NULL },
        { "getsimulationgravity_3f", (CFunction)sim_get_gravity_3f, VarArgs, NULL },
        { "setsimulationcollitters", (CFunction)sim_set_itter,      VarArgs, NULL },
        { "getsimulationcollitters", (CFunction)sim_get_itter,      VarArgs, NULL },
        { "addobject",               (CFunction)sim_add_object_s,   VarArgs, NULL },
        { "clearsimulation",         (CFunction)sim_clear,          VarArgs, NULL },
        // hud stuff
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
        // callback controll
        { "callback_set_collfunc",    (CFunction)object_callback_set_collfunc,    VarArgs, NULL },
        { "callback_set_stepfunc",    (CFunction)object_callback_set_stepfunc,    VarArgs, NULL },
        { "callback_set_hitfilter",   (CFunction)object_callback_set_hitfilter,   VarArgs, NULL },


        { NULL }
    };

    void Init()
    {
        Add( "pylon", pogelMethods, "The main python interface for the Pylon game engine" );

        ScriptEngine::MethodInterface::__Module * pylonModule = ScriptEngine::MethodInterface::__GetModule( "pylon" );

        pylonModule->addIntConstant( "pylon_debug", POGEL_DEBUG );
        pylonModule->addIntConstant( "pylon_wireframe", POGEL_WIREFRAME );
        pylonModule->addIntConstant( "pylon_bounding", POGEL_BOUNDING );
        pylonModule->addIntConstant( "pylon_trails", POGEL_TRAILS );
        pylonModule->addIntConstant( "pylon_collisions", POGEL_COLLISIONS );
        pylonModule->addIntConstant( "pylon_ancestory", POGEL_ANCESTORY );
        pylonModule->addIntConstant( "pylon_pairs", POGEL_PAIRS );
        pylonModule->addIntConstant( "pylon_label", POGEL_LABEL );

        pylonModule->addIntConstant( "triangle_lit", TRIANGLE_LIT );
        pylonModule->addIntConstant( "triangle_colored", TRIANGLE_COLORED );
        pylonModule->addIntConstant( "triangle_vertex_normals", TRIANGLE_VERTEX_NORMALS );
        pylonModule->addIntConstant( "triangle_invert_normals", TRIANGLE_INVERT_NORMALS );
        pylonModule->addIntConstant( "triangle_transparent", TRIANGLE_TRANSPARENT );
        pylonModule->addIntConstant( "triangle_doublesided", TRIANGLE_DOUBLESIDED );

        pylonModule->addIntConstant( "object_debug", OBJECT_DEBUG );
        pylonModule->addIntConstant( "object_draw_displaylist", OBJECT_DRAW_DISPLAYLIST );
        //pylonModule->addIntConstant( "object_draw_colored_strip", OBJECT_DRAW_COLORED_STRIP );
        pylonModule->addIntConstant( "object_draw_children", OBJECT_DRAW_CHILDREN );
        pylonModule->addIntConstant( "object_rotate_xyz", OBJECT_ROTATE_XYZ );
        pylonModule->addIntConstant( "object_rotate_zyx", OBJECT_ROTATE_ZYX );
        pylonModule->addIntConstant( "object_sort_triangles", OBJECT_SORT_TRIANGLES );
        pylonModule->addIntConstant( "object_rotate_tocamera", OBJECT_ROTATE_TOCAMERA );
        pylonModule->addIntConstant( "object_draw_nofaces", OBJECT_DRAW_NOFACES );

        pylonModule->addIntConstant( "solid_stationary", PHYSICS_SOLID_STATIONARY );
        pylonModule->addIntConstant( "solid_volatile", PHYSICS_SOLID_VOLITAL );
        pylonModule->addIntConstant( "solid_convex", PHYSICS_SOLID_CONVEX );
        pylonModule->addIntConstant( "solid_concave", PHYSICS_SOLID_CONCAVE );
        pylonModule->addIntConstant( "solid_sphere", PHYSICS_SOLID_SPHERE );

        pylonModule->addIntConstant( "object_type_object", POGEL_TYPE_OBJECT );
        pylonModule->addIntConstant( "object_type_fractal", POGEL_TYPE_FRACTAL );
        pylonModule->addIntConstant( "object_type_sprite", POGEL_TYPE_SPRITE );
        pylonModule->addIntConstant( "object_type_solid", POGEL_TYPE_SOLID );
        pylonModule->addIntConstant( "object_type_fountain", POGEL_TYPE_FOUNTAIN );
        pylonModule->addIntConstant( "object_type_microcosm", POGEL_TYPE_MICROCOSOM );

        //ScriptEngine::Execute("import pylon\n");
    }
}
