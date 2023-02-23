/*
 * Rodzhang
 *
 */

#include "plane_linux_module_class.h"
#include "plane_linux_cfg_ops.h"
#include "plane_linux_sub_modules.h"


static int _plane_linux_module_init(void)
{
    if (spate_modules_init(c_linux_sub_modules) < 0) {
        LOGE("plane linux module init error");
        return -1;
    }

    return 0;
}

static int _plane_linux_module_setting(void)
{
    if (spate_modules_setting(c_linux_sub_modules) < 0) {
        LOGE("plane linux module setting error");
        return -1;
    }
    
    return 0;
}

static void _plane_linux_module_exit(void)
{

    spate_modules_exit(c_linux_sub_modules);
}

const module_class_t c_plane_linux_module = {
    .module_name    = "plane_linux",
    .cfg_ops        = &c_plane_linux_cfg_ops,
    .module_init    = _plane_linux_module_init,
    .module_setting = _plane_linux_module_setting,
    .module_exit    = _plane_linux_module_exit,
};

