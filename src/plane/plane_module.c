/*
 * Rodzhang
 *
 */

#include "plane.h"
#include "plane_module.h"
#include "plane_cfg_ops.h"


static int _plane_module_init(void)
{
    return g_plane->module_class->module_init();
}

static int _plane_module_setting(void)
{
    return g_plane->module_class->module_setting();
}

static void _plane_module_exit(void)
{
    g_plane->module_class->module_exit();
}

const module_class_t c_plane_module = {
    .module_name    = "plane",
    .cfg_ops        = &c_plane_cfg_ops,
    .module_init    = _plane_module_init,
    .module_setting = _plane_module_setting,
    .module_exit    = _plane_module_exit,
};

