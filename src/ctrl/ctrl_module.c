/*
 * Rodzhang
 *
 */

#include "ctrl_module.h"
#include "ctrl_mgr.h"

static int _ctrl_module_init(void)
{
    if (ctrl_mgr_init() < 0) {
        return 0;
    }

    return 0;
}

static int _ctrl_module_setting(void)
{
    if (ctrl_mgr_setting() < 0) {
        return 0;
    }

    return 0;
}

static void _ctrl_module_exit(void)
{
    ctrl_mgr_exit();
}


const module_class_t c_ctrl_module = {
    .module_name    = "ctrl",
    .cfg_ops        = NULL,
    .module_init    = _ctrl_module_init,
    .module_setting = _ctrl_module_setting,
    .module_exit    = _ctrl_module_exit,
};

