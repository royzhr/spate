/*
 * Rodzhang
 *
 */

#include "hook_module.h"
#include "hook_cfg_ops.h"
#include "hook_mgr.h"

static int _hook_module_init(void)
{
    if (hook_mgr_init() < 0) {
        return 0;
    }

    return 0;
}

static int _hook_module_setting(void)
{
    if (hook_mgr_setting() < 0) {
        return 0;
    }

    return 0;
}

static void _hook_module_exit(void)
{
    hook_mgr_exit();
}


const module_class_t c_hook_module = {
    .module_name    = "hook",
    .cfg_ops        = &c_hook_cfg_ops,
    .module_init    = _hook_module_init,
    .module_setting = _hook_module_setting,
    .module_exit    = _hook_module_exit,
};
