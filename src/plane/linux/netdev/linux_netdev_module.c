/*
 * Rodzhang
 *
 */

#include "linux_netdev_module.h"
#include "linux_netdev_mgr.h"
#include "linux_netdev_cfg_ops.h"



static int _linux_netdev_module_init(void)
{
    if (linux_netdev_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _linux_netdev_module_setting(void)
{
    if (linux_netdev_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _linux_netdev_module_exit(void)
{

    linux_netdev_mgr_exit();
}

const module_class_t c_linux_netdev_module = {
    .module_name    = "linux_netdev",
    .cfg_ops        = &c_linux_netdev_cfg_ops,
    .module_init    = _linux_netdev_module_init,
    .module_setting = _linux_netdev_module_setting,
    .module_exit    = _linux_netdev_module_exit,
};


