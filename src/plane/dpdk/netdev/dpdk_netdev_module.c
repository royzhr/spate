/*
 * Rodzhang
 *
 */

#include "dpdk_netdev_module.h"
#include "dpdk_netdev_mgr.h"
#include "dpdk_netdev_cfg_ops.h"



static int _dpdk_netdev_module_init(void)
{
    if (dpdk_netdev_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _dpdk_netdev_module_setting(void)
{
    if (dpdk_netdev_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _dpdk_netdev_module_exit(void)
{

    dpdk_netdev_mgr_exit();
}

const module_class_t c_dpdk_netdev_module = {
    .module_name    = "dpdk_netdev",
    .cfg_ops        = &c_dpdk_netdev_cfg_ops,
    .module_init    = _dpdk_netdev_module_init,
    .module_setting = _dpdk_netdev_module_setting,
    .module_exit    = _dpdk_netdev_module_exit,
};


