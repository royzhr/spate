/*
 * Rodzhang
 *
 */


#include "host_module.h"
#include "host_cfg_ops.h"
#include "host_mgr.h"

static int _host_module_init(void)
{
    if (host_mgr_init() < 0) {
        return 0;
    }

    return 0;
}

static int _host_module_setting(void)
{
    if (host_mgr_setting() < 0) {
        return 0;
    }

    return 0;
}

static void _host_module_exit(void)
{
    host_mgr_exit();
}


const module_class_t c_host_module = {
    .module_name    = "host",
    .cfg_ops        = &c_host_cfg_ops,
    .module_init    = _host_module_init,
    .module_setting = _host_module_setting,
    .module_exit    = _host_module_exit,
};

